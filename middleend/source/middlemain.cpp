#include "../headers/middle.h"
#include "../../backend/headers/backendfuncs.h"

int main(int argc, const char *argv[])
{
    const char *input_file = (argc >= 2) ? argv[1] : "ast_trees/front.txt";
    const char *output_file = (argc == 3) ? argv[2] : "ast_trees/mid.txt";

    Logfile = fopen("logfiles/midlog.htm", "w");
    fflush(Logfile);

    INIT_VAR(DATASIZE);
    INIT_FUNC(DATASIZE);

    Node_t *node = ReadTreeFromFile(input_file, "ast_trees/dbg.txt", __LINE__);

    node = OptimizeTree(node, NOT_FOUND);
    TreeDump(node, output_file, __LINE__);

    VarTableDtor();
    FuncTableDtor();
    NodeDtor(node);
    fclose(Logfile);
}