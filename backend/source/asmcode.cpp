#include "headers/asmcode.h"

#define _NARGS_ (Func_table.data[GetFunc(node)].end_idx - Func_table.data[GetFunc(node)].start_idx + 1)

void MakeAsm(Node_t *node, const char *output_file)
{
    assert(node);
    assert(output_file);
    
    FILE *file = fopen(output_file, "w");
    assert(file);

    PUSH_(Var_table.size);
    POPR_("RAX");

    PrintAsmCode(node, file);
    TEXT_("HLT");
    
    fclose(file);
}

void FillVarInfo(FILE *file, VarStack_t *stk, int start_index, int end_index)
{
    assert(file);
    assert(stk);

    int max_index = end_index - start_index;

    for (int index = 0; index <= max_index; index++)
    {
        PUSH_(stk->data[start_index + index].value);
        PUSH_(start_index + index);
        POPR_("AX");
        POPM_("AX"); //ntabs*4 %*s
        TEXT_(";initialized in ram var [");
        TEXT_("%s", Var_table.data[start_index + index].name);
        TEXT_("]\n");
    }
}

void PrintAsmCode(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    fprintf(file, "\n;");
    PrintNodeInfo(node, file);

    if (IsOper(node, OP_F_DCLR))
    {
        PrintFunc(node, file);
        return;
    }

    if (GetLeft(node) && !IsOper(node, OP_ASSIGN))
    {
        PrintAsmCode(GetLeft(node), file);    
    }

    PrintInfixOpers(node, file);

    if (GetRight(node))
    {
        PrintAsmCode(GetRight(node), file);    
    }

    switch (GetType(node))
    {
        case TYPE_OP:
            PrintPostfixOpers(node, file);
            break;

        case TYPE_VAR:
            PushVar(node, file);            
            break;

        case TYPE_NUM:
            PUSH_(GetNum(node));
            break;

        case TYPE_UFUNC:
            CALL_(Func_table.data[GetFunc(node)].name);
            break;

        case TYPE_ERR:
            break;
        
        default:
            break;
    }
}

void PrintPrefixOpers(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    Oper_table[GetOper(node)].ptr_prefix(node, file);
}

void PrintInfixOpers(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    Oper_table[GetOper(node)].ptr_infix(node, file);
}

void PrintPostfixOpers(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);
    
    Oper_table[GetOper(node)].ptr_postix(node, file);
}

void PrintFunc(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    Node_t *func_node = GetLeft(node);
    int start_idx = Func_table.data[GetFunc(func_node)].start_idx;

    TEXT_("JMP :end_%s_%p", Func_table.data[GetFunc(func_node)].name, func_node);
    STRT_(Func_table.data[GetFunc(func_node)].name);

    FillFuncArgs(GetLeft(func_node), file, start_idx);
    PrintFuncCode(GetRight(func_node), file, start_idx);

    TEXT_(":end_%s_%p", Func_table.data[GetFunc(func_node)].name, func_node);
}

void FillFuncArgs(Node_t *node, FILE *file, int start_idx)
{
    assert(node);
    assert(file);

    if (GetLeft(node))
    {
        FillFuncArgs(GetLeft(node), file, start_idx);
    }

    if (GetRight(node))
    {
        FillFuncArgs(GetRight(node), file, start_idx);
    }

    if (IsVarType(node))
    {
        PopFuncVar(node, file, start_idx);
    }
}

void PrintFuncCode(Node_t *node, FILE *file, int start_idx)
{
    assert(node);
    assert(file);

    fprintf(file, "\n;");
    PrintNodeInfo(node, file);

    if (GetLeft(node) && !IsOper(node, OP_ASSIGN))
    {
        PrintFuncCode(GetLeft(node), file, start_idx);    
    }

    PrintInfixOpers(node, file);

    if (GetRight(node))
    {
        PrintFuncCode(GetRight(node), file, start_idx);    
    }

    switch (GetType(node))
    {
        case TYPE_OP:
            PrintFuncPostfixOpers(node, file, start_idx);
            break;

        case TYPE_VAR:
            PushFuncVar(node, file, start_idx);            
            break;

        case TYPE_NUM:
            PUSH_(GetNum(node));
            break;

        case TYPE_UFUNC:
            PUSHR_("RAX");
            PUSH_(_NARGS_);
            TEXT_("ADD");
            POPR_("RAX");

            CALL_(Func_table.data[GetFunc(node)].name);

            PUSHR_("RAX");
            PUSH_(_NARGS_);
            TEXT_("SUB");
            POPR_("RAX");

            break;

        case TYPE_ERR:
            break;
        
        default:
            break;
    }
}

void PushFuncVar(Node_t *node, FILE *file, int start_idx)
{
    assert(node);
    assert(file);

    PUSHR_("RAX");
    PUSH_(GetVar(node) - start_idx);
    GetAsmAdd(node, file);

    POPR_("AX");
    PUSHM_("AX"); 
    fprintf(file, ";pushed var [%s]\n", Var_table.data[GetVar(node)].name);
}

void PopFuncVar(Node_t *node, FILE *file, int start_idx)
{
    assert(node);
    assert(file);

    PUSHR_("RAX");
    PUSH_(GetVar(node) - start_idx);
    GetAsmAdd(node, file);
    
    POPR_("AX");
    POPM_("AX");
    fprintf(file, ";popped in var [%s]\n", Var_table.data[GetVar(node)].name);
}

void PrintFuncPostfixOpers(Node_t *node, FILE *file, int start_idx)
{
    assert(node);
    assert(file);
    
    if (!IsOper(node, OP_ASSIGN))
    {
        Oper_table[GetOper(node)].ptr_postix(node, file);
    }

    else 
    {
        if (IsOper(GetLeft(node), OP_V_DCLR))
        {
            PopFuncVar(GetLeft(GetLeft(node)), file, start_idx);
        }

        else
        {
            PopFuncVar(GetLeft(node), file, start_idx);
        }

        TEXT_(";assign end");
    }
}