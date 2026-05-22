#include "../headers/elf.h"
#include "../headers/section_table.h"
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint64_t g_printchar_addr = 0;
uint64_t g_my_scanf_addr = 0;
uint64_t g_print_addr = 0;

StdlibAddr_t g_stdlib_addrs[3];
int g_stdlib_count = 0;

#define _EMPTY_QWORD_ 0xDEADBEEF

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

void Fill_Elf_Ident(unsigned char *e_ident)
{
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
            for (int j = 0; j < g_stdlib_count; j++) {
                if (strcmp(Binary.patches[i].name, g_stdlib_addrs[j].name) == 0) {
                    uint32_t offset = (uint32_t)g_stdlib_addrs[j].addr - (Binary.patches[i].patch_pos + 4);
                    memcpy(Binary.text.bin_data + Binary.patches[i].patch_pos, &offset, 4);
                    Binary.patches[i].target_pos = Binary.labels[j].pos;
                    Binary.patches[i].resolved = 1;
                    found = 1;
                    break;
                }
            }
        }
        
        if (!found) {
            fprintf(stderr, "ERROR: unresolved patch: %s\n", Binary.patches[i].name);
        }
    }
}

int Build_Elf(const char *output_filename, StdlibSections_t stdlib)
{
    assert(output_filename);

    char filename[STRSIZE] = "";
    sprintf(filename, "binary/%s.bin", output_filename);

    FILE *out = fopen(filename, "wb");

    if (!out) 
    {
        fprintf(stderr, "Error: cannot open %s for writing\n", filename);
        return -1;
    }

    size_t code_size = BIN_SIZE_(TEXT_SEC);
    size_t data_size = BIN_SIZE_(DATA_SEC);
    
    uint8_t *code = (uint8_t*)malloc(code_size);
    uint8_t *data = (uint8_t*)malloc(data_size);

    memcpy(code, BIN_DATA_(TEXT_SEC), code_size);
    memcpy(data, BIN_DATA_(DATA_SEC), data_size);

    uint32_t printchar_offset = 0;
    uint32_t my_scanf_offset = 0;
    uint32_t print_offset = 0;

    if (stdlib.text && stdlib.text_size > 0) 
    {
        code = (uint8_t*)realloc(code, code_size + stdlib.text_size);
        memcpy(code + code_size, stdlib.text, stdlib.text_size);
        
        printchar_offset = code_size + 0;
        my_scanf_offset = code_size + 0x25;
        print_offset = code_size + 0xB6;
        
        code_size += stdlib.text_size;
    }
    
    if (stdlib.data && stdlib.data_size > 0) 
    {
        data = (uint8_t*)realloc(data, data_size + stdlib.data_size);
        memcpy(data + data_size, stdlib.data, stdlib.data_size);
        data_size += stdlib.data_size;
    }

    if (code_size == 0) 
    {
        fprintf(stderr, "Error: no code generated\n");
        free(code);
        free(data);
        fclose(out);
        return -1;
    }

    uint64_t ehdr_size = sizeof(Elf64_Ehdr);
    uint64_t phdr_size = sizeof(Elf64_Phdr);
    
    uint64_t base_addr = 0x400000;
    uint64_t code_offset = ehdr_size + phdr_size * 2; 
    uint64_t data_offset = code_offset + code_size;

    g_printchar_addr = base_addr + code_offset + printchar_offset;
    g_my_scanf_addr = base_addr + code_offset + my_scanf_offset;
    g_print_addr = base_addr + code_offset + print_offset;

    AddStdlibAddr("printchar", g_printchar_addr);
    AddStdlibAddr("my_scanf", g_my_scanf_addr);
    AddStdlibAddr("print", g_print_addr);

    ResolveLabels();

    printf("printchar addr: 0x%lX\n", g_printchar_addr);
    printf("my_scanf addr: 0x%lX\n", g_my_scanf_addr);
    printf("print addr: 0x%lX\n", g_print_addr);

    Elf64_Ehdr ehdr = {0};
    Fill_Elf_Ident(ehdr.e_ident);
    ehdr.e_type      = ET_EXEC;
    ehdr.e_machine   = EM_X86_64;
    ehdr.e_version   = EV_CURRENT;
    ehdr.e_entry     = base_addr + code_offset;
    ehdr.e_phoff     = ehdr_size;
    ehdr.e_shoff     = 0;
    ehdr.e_flags     = 0;
    ehdr.e_ehsize    = (uint16_t)ehdr_size;
    ehdr.e_phentsize = (uint16_t)phdr_size;
    ehdr.e_phnum     = 2;  
    ehdr.e_shentsize = 0;
    ehdr.e_shnum     = 0;
    ehdr.e_shstrndx  = 0;

    Elf64_Phdr phdr_code = {0};
    phdr_code.p_type     = PT_LOAD;
    phdr_code.p_flags    = PF_R | PF_X;
    phdr_code.p_offset   = code_offset;
    phdr_code.p_vaddr    = base_addr + code_offset;
    phdr_code.p_paddr    = base_addr + code_offset;
    phdr_code.p_filesz   = code_size;
    phdr_code.p_memsz    = code_size;
    phdr_code.p_align    = 0x1000;

    Elf64_Phdr phdr_data = {0};
    phdr_data.p_type     = PT_LOAD;
    phdr_data.p_flags    = PF_R | PF_W;
    phdr_data.p_offset   = data_offset;
    phdr_data.p_vaddr    = base_addr + data_offset;
    phdr_data.p_paddr    = base_addr + data_offset;
    phdr_data.p_filesz   = data_size;
    phdr_data.p_memsz    = data_size;
    phdr_data.p_align    = 0x1000;

    fwrite(&ehdr, 1, ehdr_size, out);
    fwrite(&phdr_code, 1, phdr_size, out);
    fwrite(&phdr_data, 1, phdr_size, out);
    fwrite(code, 1, code_size, out);
    fwrite(data, 1, data_size, out);

    fclose(out);

    printf("code_size: %zu, data_size: %zu\n", code_size, data_size);
    printf("entry: 0x%lx\n", ehdr.e_entry);

    free(code);
    free(data);
    free(stdlib.text);
    free(stdlib.data);

    return 0;
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

void AddStdlibAddr(const char *name, uint64_t addr)
{
    assert(name);

    strcpy(g_stdlib_addrs[g_stdlib_count].name, name);
    g_stdlib_addrs[g_stdlib_count].addr = addr;
    g_stdlib_count++;
}