#include "../headers/nasmcode.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define DATA_ALLOC_(ftype, sec, type)       ftype##_DATA_(sec) = (type *) calloc(ftype##_CAP_(sec), sizeof(type)); \
                                            assert(ftype##_DATA_(sec))

void CtorSections()
{
    S_CAP_(TEXT_SEC) = _S_BUF_SIZE_;
    S_CAP_(DATA_SEC) = _S_BUF_SIZE_;
    S_CAP_(RODATA_SEC) = _S_BUF_SIZE_;


    DATA_ALLOC_(S, TEXT_SEC, char);
    DATA_ALLOC_(S, DATA_SEC, char);
    DATA_ALLOC_(S, RODATA_SEC, char);    

    DATA_ALLOC_(BIN, TEXT_SEC, uint8_t);
    DATA_ALLOC_(BIN, DATA_SEC, uint8_t);
    DATA_ALLOC_(BIN, RODATA_SEC, uint8_t); 
    
    TEXT_("Section .text");
    DATA_("Section .data");
}

void DtorSections()
{
    free(S_DATA_(TEXT_SEC));
    free(S_DATA_(DATA_SEC));
    free(S_DATA_(RODATA_SEC));

    free(BIN_DATA_(TEXT_SEC));
    free(BIN_DATA_(DATA_SEC));
    free(BIN_DATA_(RODATA_SEC));    
}

void MakeCode(Node_t *node, const char *output_file)
{
    assert(node);
    assert(output_file);

    FILE *s_file = fopen(output_file, "w");
    assert(s_file);

    CtorSections();

    LEA_(rax, End_Prog);
    PUSH_(rax);

    Translate_AST(node);

    TAG_("End_Prog");
    MOV_RI_(rax, 0x3C);
    TEXT_("xor rdi, rdi");
    TEXT_("syscall");

    DtorSections();

    fclose(s_file);
}

void Translate_AST(const Node_t *node)
{
    if (!node) return;

    TEXT_("\n");
    WriteNodeInfo(node);

    if (IsOper(node, OP_F_DCLR))
    {
        WriteFunc(GetLeft(node));
        return;
    }

    if (!IsOper(node, OP_ASSIGN))
    {
        Translate_AST(GetLeft(node));    
    }

    Translate_AST(GetRight(node));
    
    switch (GetType(node))
    {
        case TYPE_OP:
            Do_S_Oper(node);
            break;

        case TYPE_VAR:
            if (GetVarScope(node) != GLOBAL)
                MOV_RM_OFS_(rax, GetVarOfs(node)); //fix for global
            else
                MOV_RM_(rax, GetVarName(node));

            PUSH_(rax);
            break;

        case TYPE_NUM:
            MOV_RI_(rax, GetNum(node));
            PUSH_(rax);
            break;

        case TYPE_UFUNC: {
            int n_args = GetFuncArgEndIdx(node) - GetFuncStartIdx(node);
            CALL_(GetFuncName(node));
            ADD_RI_(rsp, n_args * _REG_SIZE_);
            break;
        }
        case TYPE_ERR:
            break;
        
        default:
            break;
    }
}

void WriteFunc(const Node_t *node)
{
    assert(node);

    char *name = GetFuncName(node);
    TAG_(name);
    PUSH_(rbp);
    MOV_RR_(rbp, rsp);
    Translate_AST(GetRight(node));
}

void WriteNodeInfo(const Node_t *node)
{
    assert(node);

    switch (GetType(node))
    {
        case TYPE_OP:
            TEXT_(";OP - %s\n", Oper_table[GetOper(node)].std_name);
            break;
        case TYPE_VAR:
            TEXT_(";VAR - %s\n, table_idx [%d]", Var_table.data[GetVar(node)].name, GetVar(node));
            break;
        case TYPE_NUM:
            TEXT_(";NUM = %d\n", GetNum(node));
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