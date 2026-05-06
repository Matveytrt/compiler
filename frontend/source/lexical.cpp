#include "headers/lexical.h"

#define INIT_TOK(stk, capacity) TokStackInit(stk, capacity, __LINE__)
#define PUSH_TOK(stk, val)      TokStackPush(stk, val, __LINE__)
#define POP_TOK(stk, val)       TokStackPop(stk, err, __LINE__)
#define DUMP_TOK(stk)           TokStackDump(stk, __LINE__, __FILE__, "token stk")
#define DTOR_TOK(stk)           TokStackDestroy(stk, __LINE__)

#define CUR_STR                 info->str_data[nline].str_ptr
#define CUR_POS                *(CUR_STR)
#define STR_LEN                 info->str_data[nline].str_len

#define _OP_NAME_               Oper_table[index].name
#define _OP_LEN_                Oper_table[index].len
#define _OP_CODE_               Oper_table[index].code

TokStack_t TokStkCtor()
{
    TokStack_t stk = {};

    INIT_TOK(&stk, DATASIZE);

    return stk;
}

void GetTokens(File_Info_t *info, TokStack_t *stk)
{
    assert(stk);

    printf("lines = %d\n", info->nlines);

    for(int nline = 0; nline < info->nlines; nline++)
    {
        char *temp_ptr = CUR_STR;

        while (CUR_POS != '\0')
        {
            SkipSpaces(&CUR_STR);

            if(GetOpToken(&CUR_STR, nline, stk)) continue;

            if(isalpha(CUR_POS))  
            {
                char str[_VAR_STR_SIZE_] = "";

                for (int index = 0; index < _VAR_STR_SIZE_; index++)
                {
                    str[index] = CUR_POS;
                    CUR_STR++;

                    if(!isalnum(CUR_POS)) break;
                }

                SkipSpaces(&CUR_STR);

                if (CUR_POS == '(')
                {
                    int func_index = SearchFuncName(str);

                    if (func_index == NOT_FOUND)
                    {
                        Func_t func = {};
                        func.name = strdup(str);
                        func.len = strlen(str);//+hash

                        func_index = (int) Func_table.size;
                        PUSH_FUNC(func);
                    }

                    Node_t *new_node = CTOR_FUNC(func_index);
                    new_node->info.nline = nline;
                    new_node->info.cur_pos = CUR_STR;
                    PUSH_TOK(stk, new_node);
                }

                else
                {
                    int var_index = SearchVarName(str, FICT_ELEM);

                    if (var_index == NOT_FOUND)
                    {
                        Var_t var = {};
                        var.name = strdup(str);
                        var.len = strlen(str);//+hash

                        var_index = (int) Var_table.size;
                        PUSH_VAR(var);
                    }

                    Node_t *new_node = CTOR_VAR(var_index);
                    new_node->info.nline = nline;
                    new_node->info.cur_pos = CUR_STR;
                    PUSH_TOK(stk, new_node);
                }
            }
            
            else if (isdigit(CUR_POS) || CUR_POS == '-')
            {
                Node_t *new_node = CTOR_NUM((TreeElem_t) strtod(CUR_STR, &CUR_STR));
                new_node->info.nline = nline;
                new_node->info.cur_pos = CUR_STR;
                PUSH_TOK(stk, new_node);
            }
        }
            
        CUR_STR = temp_ptr;
    }
}

void DumpTokens (TokStack_t *stk, int line)
{
    assert(stk);

    FILE *tree_file = fopen("tokens.txt", "w");
    assert(tree_file);

    FILE *graph = fopen("graph.txt", "w");
    assert(graph);

    fprintf(Logfile, "<pre>\n\t<h3>\n\t\tDUMP from %s:%d <font color = red>Tree </font>\n\t</h3>\n", __FILE__, line);
    
    fprintf(graph, "digraph structs\n{\n\tnode[style=filled];\n\trankdir = TB;\n");
    
    for(int index = 0; index < stk->size; index++)
    {
        PrintNode(stk->data[index], graph, tree_file);
    }
    fprintf(graph, "}");

    fclose(graph);
    fclose(tree_file);

    char dot_cmd[REASONSTRSIZE] = "";

    sprintf(dot_cmd, "dot \"graph.txt\" -T png -o frontpng/graph_tokens.png");

    fprintf(Logfile, "\n\n\tImage:\n\t<img src = treepng/graph_tokens.png heigth = 1000px width = 1000px>\n</pre>\n");
    system(dot_cmd);
}

bool GetOpToken (char **buff, int nline, TokStack_t *stk)
{
    assert(stk);
    assert(buff);

    for (int index = 0; index < _OPERDATASIZE_; index++)
    {
        if( strncmp(*buff, _OP_NAME_, _OP_LEN_) == 0)
        {
            Node_t *new_node = CTOR_OP(_OP_CODE_);
            //printf("op - %s\n", _OP_NAME_);
            new_node->info.nline = nline;
            new_node->info.cur_pos = *buff;
            PUSH_TOK(stk, new_node);
            (*buff) += _OP_LEN_;
            return true;
        }
    }

    return false;
}

int SkipSpaces(char **buff)
{
    assert(buff);

    int offset = 0;

    while (**buff == ' ' || **buff == '\n' || **buff == '\r')
    {
        (*buff)++;
        offset++;
    }

    return offset;
}

void TokStkDtor(TokStack_t *stk)
{
    assert(stk);

    for (int index = 0; index < stk->size; index++)
    {
        free(stk->data[index]);
    }
    DTOR_TOK(stk);
}