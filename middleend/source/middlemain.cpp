#include "headers/middle.h"
#include "../../backend/source/headers/backendfuncs.h"

int main(int argc, const char *argv[])
{
    assert(argc == 3);
    assert(argv[1]);
    assert(argv[2]);

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    Logfile = fopen("midlog.htm", "w");
    fflush(Logfile);

    INIT_VAR(DATASIZE);
    INIT_FUNC(DATASIZE);

    Node_t *node = ReadTreeFromFile(input_file, "out.txt", __LINE__);

    node = OptimizeTree(node, NOT_FOUND);
    TreeDump(node, output_file, __LINE__);

    VarTableDtor();
    FuncTableDtor();
    NodeDtor(node);
    fclose(Logfile);
}