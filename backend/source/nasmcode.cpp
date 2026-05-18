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
    S_CAP_(DATA_SEC) = _TEXT_SEC_SIZE_;
    S_CAP_(RODATA_SEC) = _TEXT_SEC_SIZE_;


    DATA_ALLOC_(S, TEXT_SEC, char);
    DATA_ALLOC_(S, DATA_SEC, char);
    // DATA_ALLOC_(S, RODATA_SEC, char);    

    DATA_ALLOC_(BIN, TEXT_SEC, uint8_t);
    DATA_ALLOC_(BIN, DATA_SEC, uint8_t);
    // DATA_ALLOC_(BIN, RODATA_SEC, uint8_t); 

    TEXT_("default rel");
    TEXT_("extern printf");
    TEXT_("extern my_scanf");
    TEXT_("global main\n");
    TEXT_("section .text");
    TAG_("main");
    DATA_("section .data");
    DATA_("vmem_buf db 901 dup('*')");
}

void StoreBuf(const char *output_file)
{
    assert(output_file);

    FILE *s_file = fopen(output_file, "w");
    assert(s_file);

    if (s_file) 
    {
        fwrite(S_DATA_(TEXT_SEC), 1, S_SIZE_(TEXT_SEC), s_file);
        fwrite(S_DATA_(DATA_SEC), 1, S_SIZE_(DATA_SEC), s_file);
        fclose(s_file);
    }
}

void DtorSections()
{
    free(S_DATA_(TEXT_SEC));
    free(S_DATA_(DATA_SEC));
    // free(S_DATA_(RODATA_SEC));

    free(BIN_DATA_(TEXT_SEC));
    free(BIN_DATA_(DATA_SEC));
    // free(BIN_DATA_(RODATA_SEC));    
}

void MakeCode(const Node_t *node, const char *output_file)
{
    assert(node);
    assert(output_file);

    CtorSections();
    
    CALL_("Main");
    MOV_RI_(rax, 0x3C);
    TEXT_("xor rdi, rdi");
    TEXT_("syscall\n");

    DATA_("fmt_int db \"%%d\", 10, 0");
    DATA_("fmt_char db \"%%c\", 0");

    Translate_AST(node, NULL);
    
    StoreBuf(output_file);
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

    if (IsOper(node, OP_WHILE)) LBL_("WHILE", node);

    if (!IsOper(node, OP_ASSIGN) && !IsOper(node, OP_SCAN) && !IsFuncType(node)) Translate_AST(GetLeft(node), func_name);    

    PrintInfixOps(node);

    Translate_AST(GetRight(node), func_name);
    
    switch (GetType(node)) {
        case TYPE_OP:
            if (IsOper(node, OP_RET)) TEXT_("jmp exit_%s", func_name);
            Do_S_Oper(node);
            break;

        case TYPE_VAR:
            PushVar(node);
            break;

        case TYPE_NUM:
            MOV_RI_(rax, GetNum(node));
            PUSH_(rax);
            break;

        case TYPE_UFUNC: {
            int n_args = GetFuncArgEndIdx(node) - GetFuncStartIdx(node);
            CALL_(GetFuncName(node));
            ADD_RI_(rsp, n_args * (_REG_SIZE_));

            if (!IsOper(GetParent(node), OP_STR_END)) PUSH_(rax);    
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

    else if (IsNumType(node)) { MOV_RI_(rax, GetNum(node)); PUSH_(rax); }
}

void PushVar(const Node_t *node)
{
    assert(node);

    if (GetVarScope(node) != GLOBAL) { MOV_RM_OFS_(rax, GetVarOfs(node)); }
    else TEXT_("mov rax, [%s]", GetVarName(node));
    PUSH_(rax);
}

void WriteFunc(const Node_t *node)
{
    assert(node);

    char *name = GetFuncName(node);
    int n_local_vars = GetFuncEndIdx(node) - GetFuncArgEndIdx(node) + 1;

    TEXT_("\n;==========================================================================");
    TEXT_("jmp end_func_%s\n; / FUNC %s /", name, name);
    TEXT_(";==========================================================================");

    TAG_(name);
    PUSH_(rbp);
    MOV_RR_(rbp, rsp);
    SUB_RI_(rsp, n_local_vars * (_REG_SIZE_));

    Translate_AST(GetRight(node), name);
    TEXT_("exit_%s:", GetFuncName(node));
    POP_(rax);

    ADD_RI_(rsp, n_local_vars * (_REG_SIZE_));
    POP_(rbp);
    TEXT_("ret");

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