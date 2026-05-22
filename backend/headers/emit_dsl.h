#ifndef EMIT_DSL_H
#define EMIT_DSL_H

#include "emit_inst.h"

#define BIN_TEXT (&Binary.text)
#define BIN_DATA (&Binary.data)
#define BIN_RODATA (&Binary.rodata)

// MOV
#define BIN_MOV_REG2REG(dst, src)          emit_MOV_REG2REG(BIN_TEXT, dst, src)
#define BIN_MOV_IMM2REG(dst, imm)          emit_MOV_IMM2REG(BIN_TEXT, dst, imm)
#define BIN_MOV_MEM2REG(dst, src, ofs)     emit_MOV_MEM2REG(BIN_TEXT, dst, src, ofs)
#define BIN_MOV_REG2MEM(dst, ofs, src)     emit_MOV_REG2MEM(BIN_TEXT, dst, ofs, src)
#define BIN_MOVZX_REG2REG(dst, src)        emit_MOVZX_REG2REG(BIN_TEXT, dst, src)
#define BIN_MOV_REG2MEM_LABEL(src)         emit_MOV_REG2MEM_label(BIN_TEXT, src)
#define BIN_MOV_MEM2REG_LABEL(dst)         emit_MOV_MEM2REG_label(BIN_TEXT, dst)

// Arith Reg2Reg 
#define BIN_ADD_REG2REG(dst, src)          emit_arith_reg2reg(BIN_TEXT, ARITH_ADD, dst, src)
#define BIN_SUB_REG2REG(dst, src)          emit_arith_reg2reg(BIN_TEXT, ARITH_SUB, dst, src)
#define BIN_XOR_REG2REG(dst, src)          emit_arith_reg2reg(BIN_TEXT, ARITH_XOR, dst, src)
#define BIN_AND_REG2REG(dst, src)          emit_arith_reg2reg(BIN_TEXT, ARITH_AND, dst, src)
#define BIN_OR_REG2REG(dst, src)           emit_arith_reg2reg(BIN_TEXT, ARITH_OR, dst, src)
#define BIN_CMP_REG_REG(dst, src)          emit_arith_reg2reg(BIN_TEXT, ARITH_CMP, dst, src)
#define BIN_TEST_REG_REG(dst, src)         emit_arith_reg2reg(BIN_TEXT, ARITH_TEST, dst, src)
#define BIN_IMUL_REG2REG(dst, src)         emit_IMUL_REG2REG(BIN_TEXT, dst, src)
#define BIN_NOT_R(reg)                     emit_not_r(BIN_TEXT, reg)

// Arith Imm2Reg
#define BIN_ADD_IMM2REG(dst, imm)          emit_arith_imm2reg(BIN_TEXT, ARITH_ADD, dst, imm)
#define BIN_SUB_IMM2REG(dst, imm)          emit_arith_imm2reg(BIN_TEXT, ARITH_SUB, dst, imm)
#define BIN_AND_IMM2REG(dst, imm)          emit_arith_imm2reg(BIN_TEXT, ARITH_AND, dst, imm)
#define BIN_OR_RI(dst, imm)                emit_arith_imm2reg(BIN_TEXT, ARITH_OR, dst, imm)
#define BIN_CMP_REG_IMM(dst, imm)          emit_CMP_REG_IMM(BIN_TEXT, dst, imm)
#define BIN_IDIV(reg)                      emit_idiv(BIN_TEXT, reg)

// LEA
#define BIN_LEA_RM(dst, src, ofs)     emit_lea_rm(BIN_TEXT, dst, src, ofs)
#define BIN_LEA_LABEL(dst)            emit_lea_label(BIN_TEXT, dst)

// Shifts
#define BIN_SHL(dst, shift)           emit_shl(BIN_TEXT, dst, shift)
#define BIN_SHR(dst, shift)           emit_shr(BIN_TEXT, dst, shift)

// Stk
#define BIN_PUSH(reg)                 emit_push(BIN_TEXT, reg)
#define BIN_POP(reg)                  emit_pop(BIN_TEXT, reg)

// Jmps
#define BIN_JMP(offset)               emit_jmp(BIN_TEXT, offset)
#define BIN_JCC(cond, offset)         emit_jcc(BIN_TEXT, cond, offset)
#define BIN_CALL(offset)              emit_call(BIN_TEXT, offset)
#define BIN_CALL_REG(reg)             emit_call_reg(BIN_TEXT, reg)
#define BIN_RET()                     emit_ret(BIN_TEXT)

// Other
#define BIN_NOP()                     emit_nop(BIN_TEXT)
#define BIN_SYSCALL()                 emit_syscall(BIN_TEXT)
#define BIN_SETCC(op, reg)            emit_setcc(BIN_TEXT, op, reg)

#endif