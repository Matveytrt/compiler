#include "../headers/elf.h"
#include "../headers/section_table.h"
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _EMPTY_QWORD_ 0xDEADBEEF

void Fill_Elf_Ident(unsigned char *e_ident)
{
    assert(e_ident);

    e_ident[0] = 0x7F;
    e_ident[1] = 'E';
    e_ident[2] = 'L';
    e_ident[3] = 'F';
    e_ident[4] = 2;
    e_ident[5] = 1;
    e_ident[6] = 1;
    e_ident[7] = 0;
    for (int i = 8; i < EI_NIDENT; i++) e_ident[i] = 0;
}

StdlibSections_t LoadStdlibSections(void)
{
    StdlibSections_t result = {NULL, 0, NULL, 0};
    
    FILE *f_text = fopen("my_stdlib_text.bin", "rb");

    if (f_text) 
    {
        fseek(f_text, 0, SEEK_END);
        result.text_size = ftell(f_text);
        fseek(f_text, 0, SEEK_SET);
        result.text = (uint8_t*)malloc(result.text_size);
        fread(result.text, 1, result.text_size, f_text);
        fclose(f_text);

        printf("Loaded stdlib.text: %zu bytes\n", result.text_size);
    }
    
    FILE *f_data = fopen("my_stdlib_data.bin", "rb");
    if (f_data) 
    {
        fseek(f_data, 0, SEEK_END);
        result.data_size = ftell(f_data);
        fseek(f_data, 0, SEEK_SET);
        result.data = (uint8_t*)malloc(result.data_size);
        fread(result.data, 1, result.data_size, f_data);
        fclose(f_data);

        printf("Loaded stdlib.data: %zu bytes\n", result.data_size);
    }
    
    return result;
}

static uint8_t* LoadStdlibCode(StdlibSections_t *stdlib)
{
    assert(stdlib);
    
    if (!stdlib->text || stdlib->text_size == 0) {
        return NULL;
    }
    
    uint8_t *code = (uint8_t*)calloc(stdlib->text_size, sizeof(uint8_t));
    assert(code);
    
    memcpy(code, stdlib->text, stdlib->text_size);
    return code;
}

static uint8_t* LoadStdlibData(StdlibSections_t *stdlib)
{
    assert(stdlib);
    
    if (!stdlib->data || stdlib->data_size == 0) {
        return NULL;
    }
    
    uint8_t *data = (uint8_t*)calloc(stdlib->data_size, sizeof(uint8_t));
    assert(data);
    
    memcpy(data, stdlib->data, stdlib->data_size);
    return data;
}

static void ComputeStdlibOffsets(StdlibSections_t *stdlib, size_t code_size_before,
                                  uint32_t *printchar_off, uint32_t *my_scanf_off, uint32_t *print_off)
{
    assert(stdlib);
    assert(printchar_off);
    assert(my_scanf_off);
    assert(print_off);
    
    if (!stdlib->text || stdlib->text_size == 0) {
        *printchar_off = 0;
        *my_scanf_off = 0;
        *print_off = 0;
        return;
    }
    
    *printchar_off = code_size_before + 0;
    *my_scanf_off = code_size_before + 0x25; //fix
    *print_off = code_size_before + 0xB6;
}

static void WriteElfHeader(FILE *out, uint64_t entry, uint64_t phoff, uint16_t phnum)
{
    assert(out);
    
    Elf64_Ehdr ehdr = {0};
    
    Fill_Elf_Ident(ehdr.e_ident);
    ehdr.e_type      = ET_EXEC;
    ehdr.e_machine   = EM_X86_64;
    ehdr.e_version   = EV_CURRENT;
    ehdr.e_entry     = entry;
    ehdr.e_phoff     = phoff;
    ehdr.e_shoff     = 0;
    ehdr.e_flags     = 0;
    ehdr.e_ehsize    = sizeof(Elf64_Ehdr);
    ehdr.e_phentsize = sizeof(Elf64_Phdr);
    ehdr.e_phnum     = phnum;
    ehdr.e_shentsize = 0;
    ehdr.e_shnum     = 0;
    ehdr.e_shstrndx  = 0;
    
    size_t written = fwrite(&ehdr, 1, sizeof(ehdr), out);
    assert(written == sizeof(ehdr));
}

static void WriteProgramHeaders(FILE *out, uint64_t code_offset, uint64_t code_vaddr, size_t code_size)
{
    assert(out);
    
    Elf64_Phdr phdr_code = {0};
    phdr_code.p_type     = PT_LOAD;
    phdr_code.p_flags    = PF_R | PF_X;
    phdr_code.p_offset   = code_offset;
    phdr_code.p_vaddr    = code_vaddr;
    phdr_code.p_paddr    = code_vaddr;
    phdr_code.p_filesz   = code_size;
    phdr_code.p_memsz    = code_size;
    phdr_code.p_align    = 0x1000;
    
    size_t written = fwrite(&phdr_code, 1, sizeof(phdr_code), out);
    assert(written == sizeof(phdr_code));
}

static void WriteSections(FILE *out, uint8_t *code, size_t code_size, uint8_t *data, size_t data_size)
{
    assert(out);
    assert(code || code_size == 0);
    assert(data || data_size == 0);
    
    if (code && code_size > 0) {
        size_t written = fwrite(code, 1, code_size, out);
        assert(written == code_size);
    }
    
    if (data && data_size > 0) {
        size_t written = fwrite(data, 1, data_size, out);
        assert(written == data_size);
    }
}

int Build_Elf(const char *output_filename, StdlibSections_t stdlib)
{
    assert(output_filename);
    
    char filename[STRSIZE] = "";
    sprintf(filename, "binary/%s.bin", output_filename);
    
    FILE *out = fopen(filename, "wb");
    assert(out);
    
    size_t code_size = BIN_SIZE_(TEXT_SEC);
    // size_t data_size = BIN_SIZE_(DATA_SEC);  // ЗАКОММЕНТИРОВАТЬ
    
    size_t code_size_before = code_size;
    
    uint32_t printchar_offset = 0;
    uint32_t my_scanf_offset = 0;
    uint32_t print_offset = 0;
    
    uint8_t *stdlib_code = LoadStdlibCode(&stdlib);
    // uint8_t *stdlib_data = LoadStdlibData(&stdlib);  // ЗАКОММЕНТИРОВАТЬ
    
    if (stdlib_code && stdlib.text_size > 0) {
        size_t new_code_size = code_size + stdlib.text_size;
        BIN_DATA_(TEXT_SEC) = (uint8_t*)realloc(BIN_DATA_(TEXT_SEC), new_code_size);
        assert(BIN_DATA_(TEXT_SEC));
        
        memcpy(BIN_DATA_(TEXT_SEC) + code_size, stdlib_code, stdlib.text_size);
        BIN_SIZE_(TEXT_SEC) = new_code_size;
        
        ComputeStdlibOffsets(&stdlib, code_size_before, &printchar_offset, &my_scanf_offset, &print_offset);
        
        code_size = new_code_size;
    }
    
    assert(code_size > 0);
    
    uint64_t ehdr_size = sizeof(Elf64_Ehdr);
    uint64_t phdr_size = sizeof(Elf64_Phdr);
    
    uint64_t base_addr = 0x400000;
    uint64_t code_offset = ehdr_size + phdr_size;  // 1 PHDR
    // uint64_t data_offset = code_offset + code_size;  // rm
    
    int idx = Binary.label_count++;
    strcpy(Binary.labels[idx].name, "printchar");
    Binary.labels[idx].pos = code_size_before + 0;

    idx = Binary.label_count++;
    strcpy(Binary.labels[idx].name, "my_scanf");
    Binary.labels[idx].pos = code_size_before + 0x25;

    idx = Binary.label_count++;
    strcpy(Binary.labels[idx].name, "print");
    Binary.labels[idx].pos = code_size_before + 0xB6;
    
    ResolveLabels();
    
    PrintLabels();
    
    WriteElfHeader(out, base_addr + code_offset, ehdr_size, 1);  // phnum = 1
    WriteProgramHeaders(out, code_offset, base_addr + code_offset, code_size);  // no data
    WriteSections(out, BIN_DATA_(TEXT_SEC), code_size, NULL, 0);  // no data
    
    fclose(out);
    
    free(stdlib_code);
    // free(stdlib_data);  // rm
    free(stdlib.text);
    // free(stdlib.data);  // rm
    
    return 0;
}

void EmitDataArray(const char *name, uint64_t value, int count)
{
    assert(name);

    AddLabel(name);
    
    for (int i = 0; i < count; i++) {
        EMIT_BYTE(BIN_DATA, value);
    }
    
    DATA_("%s db %d dup(%lu)", name, count, value);
}

void EmitDataValue(const char *name, uint64_t value)
{
    assert(name);

    AddLabel(name);
    EMIT_QWORD(BIN_DATA, value);    
    
    DATA_("%s dq %lu", name, value);
}

void InitPatches()
{
    memset(Binary.patches, 0, sizeof(Binary.patches));
    Binary.patch_count = 0;
}
uint32_t GetCurrentBinPos(void)
{
    return (uint32_t)BIN_SIZE_(TEXT_SEC);
}

void AddLabel(const char *name)
{
    int idx = Binary.label_count++;
    strcpy(Binary.labels[idx].name, name);
    Binary.labels[idx].pos = GetCurrentBinPos();
}

void AddPatch(const char *name)
{
    int idx = Binary.patch_count++;
    strcpy(Binary.patches[idx].name, name);
    Binary.patches[idx].patch_pos = GetCurrentBinPos();
    Binary.patches[idx].resolved = 0;
    EMIT_DWORD(BIN_TEXT, _EMPTY_QWORD_);
}

void ResolveLabels()
{
    for (int i = 0; i < Binary.patch_count; i++) {
        int found = 0;
        
        for (int j = 0; j < Binary.label_count; j++) {
            if (strcmp(Binary.patches[i].name, Binary.labels[j].name) == 0) {
                uint32_t offset = Binary.labels[j].pos - (Binary.patches[i].patch_pos + 4);
                memcpy(Binary.text.bin_data + Binary.patches[i].patch_pos, &offset, 4);
                Binary.patches[i].target_pos = Binary.labels[j].pos;
                Binary.patches[i].resolved = 1;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            fprintf(stderr, "ERROR: unresolved patch: %s\n", Binary.patches[i].name);
        }
    }
}

void PrintLabels()
{
    printf("\n=== LABELS (%d) ===\n", Binary.label_count);
    printf("| %-3s | %-30s | %-10s |\n", "idx", "name", "pos");
    printf("|-----|--------------------------------|------------|\n");
    
    for (int i = 0; i < Binary.label_count; i++) {
        printf("| %-3d | %-30s | 0x%08X |\n", 
               i, 
               Binary.labels[i].name,
               Binary.labels[i].pos);
    }
    
    printf("\n=== PATCHES (%d) ===\n", Binary.patch_count);
    printf("| %-3s | %-30s | %-10s | %-10s | %s\n", 
           "idx", "name", "patch_pos", "target_pos", "resolved");
    printf("|-----|--------------------------------|------------|------------|----------|\n");
    
    for (int i = 0; i < Binary.patch_count; i++) {
        printf("| %-3d | %-30s | 0x%08X | 0x%08X | %s\n", 
               i,
               Binary.patches[i].name,
               Binary.patches[i].patch_pos,
               Binary.patches[i].target_pos,
               Binary.patches[i].resolved ? "YES" : "NO");
    }
    printf("\n");
}