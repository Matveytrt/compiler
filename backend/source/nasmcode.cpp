#include "../headers/nasmcode.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define DATA_ALLOC_(ftype, sec, type)       ftype##_DATA_(sec) = (type *) calloc(ftype##_CAP_(sec), sizeof(type)); \
                                            assert(ftype##_DATA_(sec))

void CtorSections()
{
    S_CAP_(TEXT_SEC) = _TEXT_SEC_SIZE_;
    S_CAP_(DATA_SEC) = _DATA_SEC_SIZE_;
    BIN_CAP_(TEXT_SEC) = _TEXT_SEC_SIZE_;
    BIN_CAP_(DATA_SEC) = _DATA_SEC_SIZE_;

    DATA_ALLOC_(S, TEXT_SEC, char);
    DATA_ALLOC_(S, DATA_SEC, char);   

    DATA_ALLOC_(BIN, TEXT_SEC, uint8_t);
    DATA_ALLOC_(BIN, DATA_SEC, uint8_t); 

    TEXT_("default abs");
    TEXT_("extern print");
    TEXT_("extern printchar");
    TEXT_("extern my_scanf");
    TEXT_("global main\n");
    TEXT_("section .text");
    TEXT_("main");
    DATA_("section .data");
    // EmitDataArray("vmem_buf", '*', 901);
}

void Store_S_Buf(const char *output_file)
{
    assert(output_file);

    char filename[STRSIZE] = "";
    sprintf(filename, "binary/%s.asm", output_file);

    FILE *s_file = fopen(filename, "w");
    assert(s_file);

    if (s_file) 
    {
        fwrite(S_DATA_(TEXT_SEC), 1, S_SIZE_(TEXT_SEC), s_file);
        fwrite(S_DATA_(DATA_SEC), 1, S_SIZE_(DATA_SEC), s_file);
        fclose(s_file);
    }
}

void Store_Bin_Buf(const char *output_file)
{
    assert(output_file);

    printf("code_size: %zu\n", BIN_SIZE_(TEXT_SEC));
    ResolveLabels();
    Build_Elf(output_file);
}

void DtorSections()
{
    free(S_DATA_(TEXT_SEC));
    free(S_DATA_(DATA_SEC));

    free(BIN_DATA_(TEXT_SEC));
    free(BIN_DATA_(DATA_SEC));   
}

void MakeCode(const Node_t *node, const char *output_file)
{
    assert(node);
    assert(output_file);

    CtorSections();
    InitPatches();
    
    CALL_("Main");
    MOV_RI_(RAX, 0x3C);
    XOR_RR_(RDI, RDI);
    SYSCALL_();

    Translate_AST(node, NULL);
    
    Store_S_Buf(output_file);
    Store_Bin_Buf(output_file);
    DtorSections();
}

void Translate_AST(const Node_t *node, char *func_name)
{
    if (!node) return;

    // WriteNodeInfo(node);

    if (IsOper(node, OP_F_DCLR)) {
        WriteFunc(GetLeft(node));
        return;
    }

    if (IsOper(node, OP_WHILE)) LBL_BIN("WHILE", node);

    if (!IsOper(node, OP_ASSIGN) && !IsOper(node, OP_SCAN) && !IsFuncType(node)) Translate_AST(GetLeft(node), func_name);    

    PrintInfixOps(node);

    Translate_AST(GetRight(node), func_name);
    
    switch (GetType(node)) {
        case TYPE_OP:
            if (IsOper(node, OP_RET)) TEXT_("jmp exit_%s", func_name); //fix
            Do_S_Oper(node);
            break;

        case TYPE_VAR:
            PushVar(node);
            break;

        case TYPE_NUM:
            MOV_RI_(RAX, GetNum(node));
            PUSH_(RAX);
            break;

        case TYPE_UFUNC: {
            int n_args = GetFuncArgEndIdx(node) - GetFuncStartIdx(node);
            CALL_(GetFuncName(node));
            ADD_RI_(RSP, n_args * (_REG_SIZE_));

            if (!IsOper(GetParent(node), OP_STR_END)) PUSH_(RAX);    
            break;
        }
        case TYPE_ERR:
            break; 

        default:
            break;
    }
}

void PrintInfixOps(const Node_t *node)
{
    assert(node);

    if (IsFuncType(node)) PushFuncArgs(node);

    if (IsOper(node, OP_IF)) Do_S_InfixIF(node);

    if (IsOper(node, OP_WHILE)) Do_S_InfixWHILE(node);
}

void PushFuncArgs(const Node_t *node)
{
    if (!node) return;

    PushFuncArgs(GetRight(node));

    PushFuncArgs(GetLeft(node));

    if (IsVarType(node)) PushVar(node);

    else if (IsNumType(node)) { MOV_RI_(RAX, GetNum(node)); PUSH_(RAX); }
}

void PushVar(const Node_t *node)
{
    assert(node);

    if (GetVarScope(node) != GLOBAL) { MOV_RM_OFS_(RAX, GetVarOfs(node)); }
    else MOV_RM_LABEL_(RAX, GetVarName(node));
    PUSH_(RAX);
}

void WriteFunc(const Node_t *node)
{
    assert(node);

    char _label[_LBL_SIZE_] = "";

    char *name = GetFuncName(node);
    int n_local_vars = GetFuncEndIdx(node) - GetFuncArgEndIdx(node) + 1;

    TEXT_("\n;==========================================================================");
    TEXT_("jmp end_func_%s\n; / FUNC %s /", name, name);
    TEXT_(";==========================================================================");

    TEXT_("%s:", name);
    AddLabel(name);
    PUSH_(RBP);
    MOV_RR_(RBP, RSP);
    SUB_RI_(RSP, n_local_vars * (_REG_SIZE_));

    Translate_AST(GetRight(node), name);
    
    sprintf(_label, "exit_%s", GetFuncName(node));
    AddLabel(_label);
    TEXT_("exit_%s:", GetFuncName(node));
    
    POP_(RAX);

    ADD_RI_(RSP, n_local_vars * (_REG_SIZE_));
    POP_(RBP);
    RET_();

    TEXT_(";==========================================================================");
    TEXT_("end_func_%s:", name);
    TEXT_(";==========================================================================\n");
}

void WriteNodeInfo(const Node_t *node)
{
    assert(node);

    switch (GetType(node)) {
        case TYPE_OP:
            TEXT_(";OP - %s", Oper_table[GetOper(node)].std_name);
            break;
        case TYPE_VAR:
            TEXT_(";VAR - %s table_idx [%d]", Var_table.data[GetVar(node)].name, GetVar(node));
            break;
        case TYPE_NUM:
            TEXT_(";NUM = %d", GetNum(node));
            break;
        case TYPE_UFUNC:
            TEXT_(";FUNC - %s st_idx = %d, end_idx = %d\n", Func_table.data[GetFunc(node)].name, Func_table.data[GetFunc(node)].start_idx, Func_table.data[GetFunc(node)].end_idx);
            break;
        case TYPE_ERR:
            break;
        default:
            break;
    }
}