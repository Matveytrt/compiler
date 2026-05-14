#include "../headers/reverse.h"

int main(int argc, const char *argv[])
{
    assert(argc == 3);
    assert(argv[1]);
    assert(argv[2]);

    const char *input_file = (argc >= 2) ? argv[1] : "ast_trees/front.txt";
    const char *output_file = (argc == 3) ? argv[2] : "my_progs/rev.txt";

    Logfile = fopen("logfiles/reverselog.htm", "w");
    fflush(Logfile);

    INIT_VAR(DATASIZE);
    INIT_FUNC(DATASIZE);

    Node_t *node = ReadTreeFromFile(input_file, "ast_trees/dbg.txt", __LINE__);

    PrintReverse(node, output_file);

    VarTableDtor();
    FuncTableDtor();
    NodeDtor(node);
    fclose(Logfile);
}