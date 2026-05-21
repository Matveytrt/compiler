// #include "../headers/asmcode.h"
#include "../headers/nasmcode.h"

int main(int argc, const char *argv[])
{
    const char *input_file = (argc >= 2) ? argv[1] : "ast_trees/mid.txt";
    const char *output_file = (argc == 3) ? argv[2] : "out";

    Logfile = fopen("logfiles/backlog.htm", "w");
    fflush(Logfile);

    INIT_VAR(DATASIZE);
    INIT_FUNC(DATASIZE);

    Node_t *node = ReadTreeFromFile(input_file, "ast_trees/dbg.txt", __LINE__);
    TreeDump(node, "ast_trees/dbg.txt", __LINE__);
    DumpVarTable();
    DumpFuncTable();

    GenerateCode(node, output_file);

    VarTableDtor();
    FuncTableDtor();
    NodeDtor(node);
    fclose(Logfile);
}