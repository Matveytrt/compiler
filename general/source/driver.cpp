#include <cassert>
#include <cstdio>
#include <cstdlib>

int main(int argc, const char *argv[])
{
    const char *input_file = (argc >= 2) ? argv[1] : "fact";
    const char *output_file = (argc == 3) ? argv[2] : "test";

    const char *script_name = "scripts/driver_script";
    
    FILE *script_file = fopen(script_name, "w");
    assert(script_file);

    fprintf(script_file, "./objects/front my_progs/%s.txt ast_trees/%s\n", input_file, "front.txt");
    // fprintf(script_file, "./objects/mid ast_trees/%s ast_trees/%s\n", "front.txt", "mid.txt");
    fprintf(script_file, "./objects/back ast_trees/%s nasm_code/%s.asm\n", "front.txt", output_file);
    // fprintf(script_file, "./objects/rev ast_trees/%s my_progs/%s\n", "mid.txt", "rev.txt");
    // fprintf(script_file, "nasm -f elf64 nasm_code/my_scanf.asm -o my_scanf.o\n");
    fprintf(script_file, "nasm -f elf64 nasm_code/%s.asm -o %s.o\n", output_file, output_file);
    fprintf(script_file, "gcc %s.o my_scanf.o -o %s -fPIE", output_file, output_file);

    fclose(script_file);
    system(script_name);
}