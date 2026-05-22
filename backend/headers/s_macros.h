#ifndef S_MACROS_H
#define S_MACROS_H

#include "emit_dsl.h"
#include "section_table.h"
#include "elf.h"

// ========== PUSH / POP ==========
#define PUSH_(reg)              \
    do {                        \
        TEXT_("push %s", #reg); \
        BIN_PUSH(REG_##reg);    \
    } while(0)

#define POP_(reg)               \
    do {                        \
        TEXT_("pop %s", #reg);  \
        BIN_POP(REG_##reg);     \
    } while(0)

// ========== MATH reg reg ==========
#define ADD_REG2REG_(dst, src)                 \
    do {                                  \
        TEXT_("add %s, %s", #dst, #src);  \
        BIN_ADD_REG2REG(REG_##dst, REG_##src); \
    } while(0)

#define SUB_REG2REG_(dst, src)                 \
    do {                                  \
        TEXT_("sub %s, %s", #dst, #src);  \
        BIN_SUB_REG2REG(REG_##dst, REG_##src); \
    } while(0)

#define XOR_REG2REG_(dst, src)                 \
    do {                                  \
        TEXT_("xor %s, %s", #dst, #src);  \
        BIN_XOR_REG2REG(REG_##dst, REG_##src); \
    } while(0)

#define MUL_REG2REG_(dst, src)                  \
    do {                                   \
        TEXT_("imul %s, %s", #dst, #src);  \
        BIN_IMUL_REG2REG(REG_##dst, REG_##src); \
    } while(0)

#define CMP_REG_REG_(dst, src)                 \
    do {                                  \
        TEXT_("cmp %s, %s", #dst, #src);  \
        BIN_CMP_REG_REG(REG_##dst, REG_##src); \
    } while(0)

#define AND_REG2REG_(dst, src)                 \
    do {                                  \
        TEXT_("and %s, %s", #dst, #src);  \
        BIN_AND_REG2REG(REG_##dst, REG_##src); \
    } while(0)

#define OR_REG2REG_(dst, src)                 \
    do {                                 \
        TEXT_("or %s, %s", #dst, #src);  \
        BIN_OR_REG2REG(REG_##dst, REG_##src); \
    } while(0)

#define NOT_R_(reg)                      \
    do {                                 \
        TEXT_("not %s", #reg);           \
        BIN_NOT_R(REG_##reg);            \
    } while(0)

// ========== MATH reg imm ============
#define ADD_IMM2REG_(dst, imm)               \
    do {                                \
        TEXT_("add %s, %d", #dst, imm); \
        BIN_ADD_IMM2REG(REG_##dst, imm);     \
    } while(0)

#define SUB_IMM2REG_(dst, imm)               \
    do {                                \
        TEXT_("sub %s, %d", #dst, imm); \
        BIN_SUB_IMM2REG(REG_##dst, imm);     \
    } while(0)

#define MUL_RI_(dst, imm)                \
    do {                                 \
        TEXT_("imul %s, %d", #dst, imm); \
        BIN_IMUL_RI(REG_##dst, imm);     \
    } while(0)

#define CMP_REG_IMM_(dst, imm)               \
    do {                                \
        TEXT_("cmp %s, %d", #dst, imm); \
        BIN_CMP_REG_IMM(REG_##dst, imm);     \
    } while(0)

#define AND_IMM2REG_(dst, imm)               \
    do {                                \
        TEXT_("and %s, %d", #dst, imm); \
        BIN_AND_IMM2REG(REG_##dst, imm);     \
    } while(0)

#define OR_RI_(dst, imm)                \
    do {                                \
        TEXT_("or %s, %d", #dst, imm);  \
        BIN_OR_RI(REG_##dst, imm);      \
    } while(0)

// ========== MOV ==========
#define MOV_REG2REG_(dst, src)                 \
    do {                                  \
        TEXT_("mov %s, %s", #dst, #src);  \
        BIN_MOV_REG2REG(REG_##dst, REG_##src); \
    } while(0)

#define MOV_IMM2REG_(dst, imm)               \
    do {                                \
        TEXT_("mov %s, %d", #dst, imm); \
        BIN_MOV_IMM2REG(REG_##dst, imm);     \
    } while(0)

#define MOV_MEM2REG_(dst, src, disp)                        \
    do {                                               \
        TEXT_("mov %s, [%s + %d]", #dst, #src, disp);  \
        BIN_MOV_MEM2REG(REG_##dst, REG_##src, disp);        \
    } while(0)

#define MOV_REG2MEM_(dst, disp, src)                       \
    do {                                              \
        TEXT_("mov [%s + %d], %s", #dst, disp, #src); \
        BIN_MOV_REG2MEM(REG_##dst, disp, REG_##src);       \
    } while(0)

#define MOV_MEM2REG_LABEL_(dst, label)                 \
    do {                                          \
        TEXT_("mov %s, [%s]", #dst, label);       \
        BIN_MOV_MEM2REG_LABEL(REG_##dst);              \
        AddPatch(label);                          \
    } while(0)

#define MOV_REG2MEM_LABEL_(label, src)                 \
    do {                                          \
        TEXT_("mov [%s], %s", label, #src);       \
        BIN_MOV_REG2MEM_LABEL(REG_##src);              \
        AddPatch(label);                          \
    } while(0)

#define MOVZX_REG2REG_(dst, src)                       \
    do {                                          \
        TEXT_("movzx %s, %s", #dst, #src);        \
        BIN_MOVZX_REG2REG(REG_##dst, REG_##src);       \
    } while(0)

// =================== LEA ===================
#define LEA_RR_(dst, src, disp)                       \
    do {                                              \
        TEXT_("lea %s, [%s + %d]", #dst, #src, disp); \
        BIN_LEA_RM(REG_##dst, REG_##src, disp);       \
    } while(0)

#define LEA_LABEL_(dst, label)                   \
    do {                                         \
        TEXT_("lea %s, [%s]", #dst, label);      \
        BIN_LEA_LABEL(REG_##dst);                \
        AddPatch(label);                         \
    } while(0)

// ============ MOV ofs (rbp + ofs) ===========
#define MOV_MEM2REG_OFS_(dst, ofs)                  \
    do {                                       \
        TEXT_("mov rcx, %d", ofs);             \
        TEXT_("mov %s, [rbp + rcx]", #dst);    \
        BIN_MOV_IMM2REG(REG_RCX, ofs);              \
        BIN_MOV_MEM2REG(REG_##dst, REG_RBP, ofs);   \
    } while(0)

#define MOV_REG2MEM_OFS_(ofs, src)                \
    do {                                     \
        TEXT_("mov rcx, %d", ofs);           \
        TEXT_("mov [rbp + rcx], %s", #src);  \
        BIN_MOV_IMM2REG(REG_RCX, ofs);            \
        BIN_MOV_REG2MEM(REG_RBP, ofs, REG_##src); \
    } while(0)

// ================ bitops ================
#define SHL_(reg, ofs)                    \
    do {                                  \
        TEXT_("shl %s, %d", #reg, ofs);   \
        BIN_SHL(REG_##reg, ofs);          \
    } while(0)

#define SHR_(reg, ofs)                    \
    do {                                  \
        TEXT_("shr %s, %d", #reg, ofs);   \
        BIN_SHR(REG_##reg, ofs);          \
    } while(0)

// =================== TEST ==================
#define TEST_REG_REG_(reg1, reg2)                 \
    do {                                     \
        TEXT_("test %s, %s", #reg1, #reg2);  \
        BIN_TEST_REG_REG(REG_##reg1, REG_##reg2); \
    } while(0)

// ================ jmp with binary labels =======================
#define JMP_BIN_UNCOND(prefix, node)                             \
    do {                                                         \
        char _label[_LBL_SIZE_] = "";                            \
        snprintf(_label, sizeof(_label), "%s_%p", prefix, node); \
        TEXT_("jmp %s", _label);                                 \
        EMIT_BYTE(BIN_TEXT, OPC_JMP);                            \
        AddPatch(_label);                                        \
    } while(0)

#define JMP_BIN(opgcc, cond, prefix, node)                       \
    do {                                                         \
        char _label[_LBL_SIZE_] = "";                            \
        snprintf(_label, sizeof(_label), "%s_%p", prefix, node); \
        TEXT_("%s %s", #cond, _label);                           \
        EMIT_BYTE(BIN_TEXT, 0x0F);                               \
        EMIT_BYTE(BIN_TEXT, opgcc);                              \
        AddPatch(_label);                                        \
    } while(0)

#define JMP_SHORT_BIN(cond, prefix, node)                        \
    do {                                                         \
        char _label[_LBL_SIZE_] = "";                            \
        snprintf(_label, sizeof(_label), "%s_%p", prefix, node); \
        TEXT_("%s %s", #cond, _label);                           \
        EMIT_BYTE(BIN_TEXT, cond);                               \
        AddPatch(_label);                                        \
    } while(0)

#define LBL_BIN(prefix, node)                                    \
    do {                                                         \
        char _label[_LBL_SIZE_] = "";                            \
        snprintf(_label, sizeof(_label), "%s_%p", prefix, node); \
        TEXT_("%s:", _label);                                    \
        AddLabel(_label);                                        \
    } while(0)

// ================= NASM with lbls  ================
#define CALL_(func)                                 \
    do {                                            \
        TEXT_("call %s", func);                     \
        EMIT_BYTE(BIN_TEXT, OPC_CALL);              \
        AddPatch(func);                             \
    } while(0)

#define RET_()            \
    do {                  \
        TEXT_("ret");     \
        BIN_RET();        \
    } while(0)

#define SYSCALL_()        \
    do {                  \
        TEXT_("syscall"); \
        BIN_SYSCALL();    \
    } while(0)

#define NOP_()            \
    do {                  \
        TEXT_("nop");     \
        BIN_NOP();        \
    } while(0)

#define DIV_R_(src)             \
    do {                        \
        TEXT_("idiv %s", #src); \
        BIN_IDIV(REG_##src);    \
    } while(0)

#define CQO_()                  \
    do {                        \
        TEXT_("cqo");           \
        /* TODO: BIN_CQO */     \
    } while(0)
#endif