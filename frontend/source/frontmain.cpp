#include "../headers/lexical.h"
#include "../headers/syntax.h"

int main(int argc, const char *argv[])
{
    const char *input_file = (argc >= 2) ? argv[1] : "my_progs/fact.txt";
    const char *output_file = (argc == 3) ? argv[2] : "ast_trees/front.txt";

    TokStack_t tok_stk = TokStkCtor();
    INIT_VAR(DATASIZE);
    INIT_FUNC(DATASIZE);

    File_Info_t info = {};
    StrArrayCtor(input_file, "r", &info);

    Logfile = fopen("logfiles/frontlog.htm", "w");
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