#include "../headers/asmcode.h"

#define _CALC_NARGS_ (Func_table.data[GetFunc(node)].end_idx - Func_table.data[GetFunc(node)].start_idx + 1)
#define PRINT_INFIX_OP Oper_table[GetOper(node)].ptr_infix_func(node, file);
#define PRINT_POSTFIX_OP Oper_table[GetOper(node)].ptr_postfix_func(node, file);

void MakeAsm(Node_t *node, const char *output_file)
{
    assert(node);
    assert(output_file);
    
    FILE *file = fopen(output_file, "w");
    assert(file);

    VM_PUSH_(Var_table.size);
    VM_POPR_("RAX");

    PrintAsmCode(node, file);
    VM_TEXT_("HLT");
    
    fclose(file);
}

void FillVarInfo(FILE *file, VarStack_t *stk, int start_index, int end_index)
{
    assert(file);
    assert(stk);

    int max_index = end_index - start_index;

    for (int index = 0; index <= max_index; index++)
    {
        VM_PUSH_(stk->data[start_index + index].value);
        VM_PUSH_(start_index + index);
        VM_POPR_("AX");
        VM_POPM_("AX"); //ntabs*4 %*s
        VM_TEXT_(";initialized in ram var [");
        VM_TEXT_("%s", Var_table.data[start_index + index].name);
        VM_TEXT_("]\n");
    }
}

void PrintAsmCode(Node_t *node, FILE *file) //todo visitor pattern projection
{
    assert(file);

    if (!node) return;

    fprintf(file, "\n;");
    PrintNodeInfo(node, file);

    if (IsOper(node, OP_F_DCLR))
    {
        PrintFunc(node, file);
        return;
    }

    if (!IsOper(node, OP_ASSIGN))
    {
        PrintAsmCode(GetLeft(node), file);    
    }

    PRINT_INFIX_OP

    PrintAsmCode(GetRight(node), file);  

    switch (GetType(node))
    {
        case TYPE_OP:
            PRINT_POSTFIX_OP
            break;

        case TYPE_VAR:
            PushVar(node, file);            
            break;

        case TYPE_NUM:
            VM_PUSH_(GetNum(node));
            break;

        case TYPE_UFUNC:
            VM_CALL_(Func_table.data[GetFunc(node)].name);
            break;

        case TYPE_ERR:
            break;
        
        default:
            break;
    }
}

void PrintFunc(Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    Node_t *func_node = GetLeft(node);
    int start_idx = Func_table.data[GetFunc(func_node)].start_idx;

    VM_TEXT_("JMP :end_%s_%p", Func_table.data[GetFunc(func_node)].name, func_node);
    VM_STRT_(Func_table.data[GetFunc(func_node)].name);

    FillFuncArgs(GetLeft(func_node), file, start_idx);
    PrintFuncCode(GetRight(func_node), file, start_idx);

    VM_TEXT_(":end_%s_%p", Func_table.data[GetFunc(func_node)].name, func_node);
}

void FillFuncArgs(Node_t *node, FILE *file, int start_idx)
{
    assert(file);

    if (!node) return;

    FillFuncArgs(GetLeft(node), file, start_idx);

    FillFuncArgs(GetRight(node), file, start_idx);

    if (IsVarType(node))
    {
        PopFuncVar(node, file, start_idx);
    }
}

void PrintFuncCode(Node_t *node, FILE *file, int start_idx)
{
    assert(file);

    if (!node) return;

    fprintf(file, "\n;");
    PrintNodeInfo(node, file);

    if (!IsOper(node, OP_ASSIGN))
    {
        PrintFuncCode(GetLeft(node), file, start_idx);    
    }

    PRINT_INFIX_OP

    PrintFuncCode(GetRight(node), file, start_idx);    

    switch (GetType(node))
    {
        case TYPE_OP:
            PrintFuncPostfixOpers(node, file, start_idx);
            break;

        case TYPE_VAR:
            PushFuncVar(node, file, start_idx);            
            break;

        case TYPE_NUM:
            VM_PUSH_(GetNum(node));
            break;

        case TYPE_UFUNC:
            VM_PUSHR_("RAX");
            VM_PUSH_(_CALC_NARGS_);
            VM_TEXT_("ADD");
            VM_POPR_("RAX");

            VM_CALL_(Func_table.data[GetFunc(node)].name);

            VM_PUSHR_("RAX");
            VM_PUSH_(_CALC_NARGS_);
            VM_TEXT_("SUB");
            VM_POPR_("RAX");

            break;

        case TYPE_ERR:
            break;
        
        default:
            break;
    }
}

void PrintFuncPostfixOpers(Node_t *node, FILE *file, int start_idx)
{
    assert(node);
    assert(file);
    
    if (!IsOper(node, OP_ASSIGN))
    {
        Oper_table[GetOper(node)].ptr_postfix_func(node, file);
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

        VM_TEXT_(";assign end");
    }
}

void PushFuncVar(Node_t *node, FILE *file, int start_idx)
{
    assert(node);
    assert(file);

    VM_PUSHR_("RAX");
    VM_PUSH_(GetVar(node) - start_idx);
    Do_VM_ADD(node, file);
    VM_POPR_("AX");

    VM_PUSHM_("AX"); 
    fprintf(file, ";pushed var [%s]\n", Var_table.data[GetVar(node)].name);
}

void PopFuncVar(Node_t *node, FILE *file, int start_idx)
{
    assert(node);
    assert(file);

    VM_PUSHR_("RAX");
    VM_PUSH_(GetVar(node) - start_idx);
    Do_VM_ADD(node, file);
    VM_POPR_("AX");
    
    VM_POPM_("AX");
    fprintf(file, ";popped in var [%s]\n", Var_table.data[GetVar(node)].name);
}