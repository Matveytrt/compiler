#include "headers/lexical.h"
#include "headers/syntax.h"

int main(int argc, const char *argv[])
{
    assert(argc == 3);
    assert(argv[1]);
    assert(argv[2]);

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    TokStack_t tok_stk = TokStkCtor();
    INIT_VAR(DATASIZE);
    INIT_FUNC(DATASIZE);

    File_Info_t info = {};
    StrArrayCtor(input_file, "r", &info);

    Logfile = fopen("frontlog.htm", "w");
    fflush(Logfile);

    GetTokens(&info, &tok_stk);
    DumpTokens(&tok_stk, __LINE__);

    Node_t *root_node = GetGeneral(&tok_stk);
    TreeDump(root_node, output_file, __LINE__);
    
    TokStkDtor(&tok_stk);
    VarTableDtor();
    FuncTableDtor();
    StrArrayDestroy(&info);
    fclose(Logfile);
}