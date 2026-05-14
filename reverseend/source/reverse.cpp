#include "../headers/reverse.h"

#define _ENDCODE_                                               \
            (*tab_count)--;                                     \
            PrintTabs(*tab_count, file);                        \
            fprintf(file, "%s", Oper_table[CLOSE_SQ_BR].name)

#define _BEGINCODE_                                             \
            PrintTabs(*tab_count, file);                        \
            fprintf(file, "%s\n", Oper_table[OPEN_SQ_BR].name); \
            (*tab_count)++

void PrintReverse(const Node_t *node, const char *output_file)
{
    assert(node);
    assert(output_file);

    FILE *file = fopen(output_file, "w");
    assert(file);

    PrintOriginalCode(node, file);
    fprintf(file, "%s", Oper_table[OP_END].name);
    fclose(file);
}

void PrintOriginalCode(const Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    static int tab_count = 0;

    PrintPrefixCode(node, &tab_count, file);

    if (GetLeft(node))
    {
        PrintOriginalCode(GetLeft(node), file);    
    }

    PrintInfixCode(node, &tab_count, file);

    if (GetRight(node))
    {
        PrintOriginalCode(GetRight(node), file);    
    }

    PrintPostfixCode(node, &tab_count, file);
}

void PrintTabs(int tab_count, FILE *file)
{
    assert(file);

    for (int ntabs = 0; ntabs < tab_count; ntabs++)
    {
        fprintf(file, "\t"); 
    }
}

void PrintPrefixCode(const Node_t *node, int *tab_count, FILE *file)
{
    assert(node);
    assert(tab_count);
    assert(file);

    if(IsOper(node, OP_STR_END))
    {
        PrintTabs(*tab_count, file);
    }

    if(IsPrefix(node))
    {
        fprintf(file, "%s ", Oper_table[GetOper(node)].name);
        if (IsConditionalOp(node) || IsOper(node, OP_SQRT) || IsOper(node, OP_PRINT) || IsOper(node, OP_SCAN) || IsOper(node, OP_MEMGET) || IsOper(node, OP_MEMSET))
            fprintf(file, "(");
    }

    if (IsFuncType(node))
    {
        fprintf(file, "%s (", Func_table.data[GetFunc(node)].name);
    }
}

void PrintInfixCode   (const Node_t *node, int *tab_count, FILE *file)
{
    assert(node);
    assert(tab_count);
    assert(file);

    if(IsOper(node, OP_SQRT) || IsOper(node, OP_PRINT) || IsOper(node, OP_SCAN) || IsOper(node, OP_MEMGET) || IsOper(node, OP_MEMSET))
    {
        fprintf(file, ")");
    }
    
    if (IsConditionalOp(node))
    {
        fprintf(file, ")\n");
        _BEGINCODE_;
    }

    if (IsFuncType(node))
    {
        fprintf(file, ")");
        if(IsOper(GetParent(node), OP_F_DCLR))
        {
            fprintf(file, "\n");
            _BEGINCODE_;
        }
    }

    if(IsInfix(node))
    {
        fprintf(file, " %s ", Oper_table[GetOper(node)].name);
        if (IsOper(node, OP_STR_END))
            fprintf(file, " \n");
    }
}

void PrintPostfixCode (const Node_t *node, int *tab_count, FILE *file)
{
    assert(node);
    assert(tab_count);
    assert(file);

    switch (GetType(node))
    {
        case TYPE_OP:
            if(IsPostix(node))
            {
                fprintf(file, "%s", Oper_table[GetOper(node)].name);
            }
            if (IsConditionalOp(node))
            {
                _ENDCODE_;
            }
            break;

        case TYPE_VAR:
            fprintf(file, "%s", Var_table.data[GetVar(node)].name);            
            break;

        case TYPE_NUM:
            fprintf(file, "%d", GetNum(node));
            break;

        case TYPE_UFUNC:
            if(IsOper(GetParent(node), OP_F_DCLR))
            {
                _ENDCODE_;    
            }
            break;

        case TYPE_ERR:
            break;
        
        default:
            break;
    }
}