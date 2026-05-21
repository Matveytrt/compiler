#ifndef EMIT_INST_H
#define EMIT_INST_H

#include "dsl.h"

//=====================================================================================
// Regs
//=====================================================================================
typedef enum {
    REG_AL = 0, REG_CL = 1, REG_DL = 2, REG_BL = 3,
    REG_AH = 4, REG_CH = 5, REG_DH = 6, REG_BH = 7,
    REG_AX = 0, REG_CX = 1, REG_DX = 2, REG_BX = 3,
    REG_SP = 4, REG_BP = 5, REG_SI = 6, REG_DI = 7,
    REG_EAX = 0, REG_ECX = 1, REG_EDX = 2, REG_EBX = 3,
    REG_ESP = 4, REG_EBP = 5, REG_ESI = 6, REG_EDI = 7,
    REG_RAX = 0, REG_RCX = 1, REG_RDX = 2, REG_RBX = 3,
    REG_RSP = 4, REG_RBP = 5, REG_RSI = 6, REG_RDI = 7,
    REG_R8 = 8, REG_R9 = 9, REG_R10 = 10, REG_R11 = 11,
    REG_R12 = 12, REG_R13 = 13, REG_R14 = 14, REG_R15 = 15
} Reg_t;

//=====================================================================================
// REX bits
//=====================================================================================
typedef enum {
    REX_W = 1 << 3,
    REX_R = 1 << 2,
    REX_X = 1 << 1,
    REX_B = 1 << 0
} REX_Bits_t;

//=====================================================================================
// Mod Mem2Reg
//=====================================================================================
typedef enum {
    MOD_REG = 3,
    MOD_DISP8 = 1,
    MOD_DISP32 = 2,
    MOD_INDIRECT = 0
} ModRM_Mod_t;

//=====================================================================================
// Opcodes
//=====================================================================================
typedef enum {
    OPC_MOV_RM8   = 0x8A,
    OPC_MOV_RM64  = 0x8B,
    OPC_MOV_MR8   = 0x88,
    OPC_MOV_MR64  = 0x89,
    OPC_MOV_RR    = 0x89,
    OPC_MOV_RI    = 0xB8,
    OPC_ADD_RR    = 0x01,
    OPC_SUB_RR    = 0x29,
    OPC_XOR_RR    = 0x31,
    OPC_IMUL_RR   = 0xAF,
    OPC_IDIV      = 0xF7,
    OPC_CMP_RR    = 0x39,
    OPC_CMP_IMM   = 0x81,
    OPC_JMP       = 0xE9,
    OPC_CALL      = 0xE8,
    OPC_JCC       = 0x0F,
    OPC_PUSH      = 0x50,
    OPC_POP       = 0x58,
    OPC_RET       = 0xC3,
    OPC_SYSCALL   = 0x05,
    OPC_NOP       = 0x90,
    OPC_LEA       = 0x8D,
    OPC_AND_RR    = 0x21,
    OPC_OR_RR     = 0x09,
    OPC_TEST_RR   = 0x85,
    OPC_SHIFT     = 0xC1,
    OPC_ADD_RI    = 0x83,
    OPC_SUB_RI    = 0x83,
    OPC_AND_RI    = 0x83,
    OPC_OR_RI     = 0x83,
    OPC_NOT_R     = 0xF7,
    OPC_SETCC     = 0x0F,
    OPC_MOVZX     = 0xB6,
    OPC_TWO_BYTE_PREFIX = 0x0F,
} Opcodes_t;

//=====================================================================================
// JCC conditions
//=====================================================================================
typedef enum {
    JCC_JO  = 0x80, JCC_JNO = 0x81,
    JCC_JB  = 0x82, JCC_JAE = 0x83,
    JCC_JE  = 0x84, JCC_JNE = 0x85,
    JCC_JBE = 0x86, JCC_JA  = 0x87,
    JCC_JS  = 0x88, JCC_JNS = 0x89,
    JCC_JP  = 0x8A, JCC_JNP = 0x8B,
    JCC_JL  = 0x8C, JCC_JGE = 0x8D,
    JCC_JLE = 0x8E, JCC_JG  = 0x8F
} JCC_Cond_t;

//=====================================================================================
// SETCC ops
//=====================================================================================
typedef enum {
    SET_E = 0x94, SET_NE = 0x95,
    SET_L = 0x9C, SET_G = 0x9F,
    SET_LE = 0x9E, SET_GE = 0x9D,
    SET_B = 0x92, SET_A = 0x97,
    SET_BE = 0x96, SET_AE = 0x93,
} SetCCOp_t;

//=====================================================================================
// Arith ops for Reg2Reg and Reg2Imm
//=====================================================================================
typedef enum {
    ARITH_ADD, ARITH_SUB, ARITH_XOR, ARITH_AND, ARITH_OR, ARITH_CMP, ARITH_TEST
} ArithOp_t;

//=====================================================================================
// Stack ops
//=====================================================================================
typedef enum {
    STACK_PUSH, STACK_POP
} StackOp_t;

//=====================================================================================
// Shift ops
//=====================================================================================
typedef enum {
    SHIFT_SHL, SHIFT_SHR
} ShiftOp_t;

//=====================================================================================
// Label ops
//=====================================================================================
typedef enum {
    LABEL_MOV_MR,   // mov [label], reg
    LABEL_MOV_RM,   // mov reg, [label]
    LABEL_LEA       // lea reg, [label]
} LabelOp_t;

//=====================================================================================
// REX prefixes
//=====================================================================================
#define REX_BASE     0x40
#define REX_64       (REX_BASE | REX_W)
#define REX_64_R     (REX_BASE | REX_W | REX_R)
#define REX_64_B     (REX_BASE | REX_W | REX_B)
#define REX_64_RB    (REX_BASE | REX_W | REX_R | REX_B)

//=====================================================================================
// ModRM reg field values
//=====================================================================================
#define MODRM_REG_ADD 0
#define MODRM_REG_OR  1
#define MODRM_REG_AND 4
#define MODRM_REG_SUB 5
#define MODRM_REG_CMP 7
#define MODRM_REG_NOT 2
#define MODRM_REG_SHL 4
#define MODRM_REG_SHR 5
#define MODRM_REG_IDIV 7

//=====================================================================================
// Emitters
//=====================================================================================

// Arithmetic Reg2Reg
void emit_arith_rr(Section_t *sec, ArithOp_t op, Reg_t dst, Reg_t src);
void emit_imul_rr(Section_t *sec, Reg_t dst, Reg_t src);
void emit_idiv(Section_t *sec, Reg_t reg);
void emit_not_r(Section_t *sec, Reg_t reg);

// Arithmetic Imm2Reg
void emit_arith_ri(Section_t *sec, ArithOp_t op, Reg_t dst, int64_t imm);
void emit_cmp_ri(Section_t *sec, Reg_t dst, int64_t imm);

// MOV
void emit_mov_rr(Section_t *sec, Reg_t dst, Reg_t src);
void emit_mov_ri(Section_t *sec, Reg_t dst, int64_t imm);
void emit_mov_rm(Section_t *sec, Reg_t dst, Reg_t src, int32_t disp);
void emit_mov_mr(Section_t *sec, Reg_t dst, int32_t disp, Reg_t src);
void emit_movzx_rr(Section_t *sec, Reg_t dst, Reg_t src);

// LEA
void emit_lea_rm(Section_t *sec, Reg_t dst, Reg_t src, int32_t disp);

// Shifts
void emit_shift(Section_t *sec, ShiftOp_t op, Reg_t dst, uint8_t shift);
void emit_shl(Section_t *sec, Reg_t dst, uint8_t shift);
void emit_shr(Section_t *sec, Reg_t dst, uint8_t shift);

// Stack
void emit_stack(Section_t *sec, StackOp_t op, Reg_t reg);
void emit_push(Section_t *sec, Reg_t reg);
void emit_pop(Section_t *sec, Reg_t reg);

// Jumps
void emit_jmp(Section_t *sec, int32_t offset);
void emit_jcc(Section_t *sec, JCC_Cond_t cond, int32_t offset);
void emit_call(Section_t *sec, int32_t offset);
void emit_ret(Section_t *sec);

// Other
void emit_nop(Section_t *sec);
void emit_syscall(Section_t *sec);
void emit_setcc(Section_t *sec, SetCCOp_t op, Reg_t reg);

// Label emitters
void emit_label(Section_t *sec, LabelOp_t op, Reg_t reg);
void emit_mov_mr_label(Section_t *sec, Reg_t src);
void emit_mov_rm_label(Section_t *sec, Reg_t dst);
void emit_lea_label(Section_t *sec, Reg_t dst);

#endif