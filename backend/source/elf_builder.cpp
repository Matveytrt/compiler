#include "../headers/elf.h"
#include "../headers/s_oper_funcs.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>

void InitPatches()
{
    memset(Binary.patches, 0, sizeof(Binary.patches));
    Binary.patch_count = 0;
}

static void Fill_Elf_Ident(unsigned char *e_ident)
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

    for (int i = 8; i < EI_NIDENT; i++) {
        e_ident[i] = 0;
    }
}

int Build_Elf(const char *output_filename)
{
    assert(output_filename);

    char filename[STRSIZE] = "";
    sprintf(filename, "binary/%s.bin", output_filename);

    FILE *out = fopen(filename, "wb");
    if (!out) {
        fprintf(stderr, "Error: cannot open %s for writing\n", output_filename);
        return -1;
    }

    size_t code_size = BIN_SIZE_(TEXT_SEC);
    uint8_t *code = BIN_DATA_(TEXT_SEC);

    if (code_size == 0) {
        fprintf(stderr, "Error: no code generated\n");
        fclose(out);
        return -1;
    }

    uint64_t base_addr = 0x400000;
    uint64_t ehdr_size = sizeof(Elf64_Ehdr);
    uint64_t phdr_size = sizeof(Elf64_Phdr);
    uint64_t phdr_offset = ehdr_size;
    uint64_t code_offset = phdr_offset + phdr_size;

    Elf64_Ehdr ehdr = {};
    memset(&ehdr, 0, sizeof(ehdr));

    Fill_Elf_Ident(ehdr.e_ident);
    ehdr.e_type      = ET_EXEC;
    ehdr.e_machine   = EM_X86_64;
    ehdr.e_version   = EV_CURRENT;
    ehdr.e_entry     = base_addr + code_offset;
    ehdr.e_phoff     = phdr_offset;
    ehdr.e_shoff     = 0;
    ehdr.e_flags     = 0;
    ehdr.e_ehsize    = (uint16_t)ehdr_size;
    ehdr.e_phentsize = (uint16_t)phdr_size;
    ehdr.e_phnum     = 1;
    ehdr.e_shentsize = 0;
    ehdr.e_shnum     = 0;
    ehdr.e_shstrndx  = 0;

    Elf64_Phdr phdr = {};
    memset(&phdr, 0, sizeof(phdr));

    phdr.p_type     = PT_LOAD;
    phdr.p_flags    = PF_R | PF_X;
    phdr.p_offset   = 0;
    phdr.p_vaddr    = base_addr;
    phdr.p_paddr    = base_addr;
    phdr.p_filesz   = code_size;
    phdr.p_memsz    = code_size;
    phdr.p_align    = 0x1000;

    fwrite(&ehdr, 1, ehdr_size, out);
    fwrite(&phdr, 1, phdr_size, out);
    fwrite(code, 1, code_size, out);

    fclose(out);

    printf("First 20 bytes: ");
    for (int i = 0; i < 20; i++) {
        printf("%02X ", BIN_DATA_(TEXT_SEC)[i]);
    }
    printf("\n");

    return 0;
}

uint32_t GetCurrentBinPos()
{
    return (uint32_t)BIN_SIZE_(TEXT_SEC);
}

void AddLabel(const char *name)
{
    assert(name);

    uint32_t pos = GetCurrentBinPos();
    
    for (int i = 0; i < Binary.patch_count; i++) 
    {
        if (Binary.patches[i].is_resolved == 0 && 
            strcmp(Binary.patches[i].label_name, name) == 0)
        {
            Binary.patches[i].target_pos = pos;
            Binary.patches[i].is_resolved = 1;
        }
    }
}

void AddPatch(const char *label_name)
{
    assert(label_name);

    int idx = Binary.patch_count++;
    Binary.patches[idx].patch_pos = GetCurrentBinPos();
    Binary.patches[idx].target_pos = 0;
    Binary.patches[idx].is_resolved = 0;
    strncpy(Binary.patches[idx].label_name, label_name, 63);
    Binary.patches[idx].label_name[63] = '\0';
    
    EMIT_DWORD(&Binary.text, 0xAAAAAAAA);
}

#include <string.h>

void ResolveLabels(void)
{
    for (int i = 0; i < Binary.patch_count; i++) {
        if (Binary.patches[i].is_resolved) {
            uint32_t offset = Binary.patches[i].target_pos - 
                              (Binary.patches[i].patch_pos + 4);
            memcpy(Binary.text.bin_data + Binary.patches[i].patch_pos, &offset, 4);
        } 

        else {
            fprintf(stderr, "ERROR: unresolved label: %s\n", 
                    Binary.patches[i].label_name);
        }
    }
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
    
    DATA_("%s dq %lu", name, value);
    EMIT_QWORD(BIN_DATA, value);    
}