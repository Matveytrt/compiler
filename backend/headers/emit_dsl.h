#ifndef EMIT_DSL_H
#define EMIT_DSL_H

#include "emit_inst.h"

#define BIN_TEXT (&Binary.text)
#define BIN_DATA (&Binary.data)
#define BIN_RODATA (&Binary.rodata)

#define BIN_MOV_RR(dst, src)      emit_mov_rr(BIN_TEXT, dst, src)
#define BIN_MOV_RI(dst, imm)      emit_mov_ri(BIN_TEXT, dst, imm)
#define BIN_MOV_RM(dst, src, ofs) emit_mov_rm(BIN_TEXT, dst, src, ofs)
#define BIN_MOV_MR(dst, ofs, src) emit_mov_mr(BIN_TEXT, dst, ofs, src)
#define BIN_MOVZX_RR(dst, src)    emit_movzx_rr(BIN_TEXT, dst, src)
#define BIN_IDIV(reg)             emit_idiv(BIN_TEXT, reg)
#define BIN_ADD_RR(dst, src)      emit_add_rr(BIN_TEXT, dst, src)
#define BIN_SUB_RR(dst, src)      emit_sub_rr(BIN_TEXT, dst, src)
#define BIN_XOR_RR(dst, src)      emit_xor_rr(BIN_TEXT, dst, src)
#define BIN_IMUL_RR(dst, src)     emit_imul_rr(BIN_TEXT, dst, src)
#define BIN_CMP_RR(dst, src)      emit_cmp_rr(BIN_TEXT, dst, src)
#define BIN_CMP_RI(dst, imm)      emit_cmp_ri(BIN_TEXT, dst, imm)
#define BIN_JMP(offset)           emit_jmp(BIN_TEXT, offset)
#define BIN_JCC(cond, offset)     emit_jcc(BIN_TEXT, cond, offset)
#define BIN_PUSH(reg)             emit_push(BIN_TEXT, reg)
#define BIN_POP(reg)              emit_pop(BIN_TEXT, reg)
#define BIN_RET()                 emit_ret(BIN_TEXT)
#define BIN_SYSCALL()             emit_syscall(BIN_TEXT)
#define BIN_CALL(offset)          emit_call(BIN_TEXT, offset)
#define BIN_NOP()                 emit_nop(BIN_TEXT)
#define BIN_LEA_RM(dst, src, ofs) emit_lea_rm(BIN_TEXT, dst, src, ofs)
#define BIN_AND_RR(dst, src)      emit_and_rr(BIN_TEXT, dst, src)
#define BIN_OR_RR(dst, src)       emit_or_rr(BIN_TEXT, dst, src)
#define BIN_TEST_RR(dst, src)     emit_test_rr(BIN_TEXT, dst, src)
#define BIN_NOT_R(reg)            emit_not_r(BIN_TEXT, reg)
#define BIN_SHL(dst, shift)       emit_shl(BIN_TEXT, dst, shift)
#define BIN_SHR(dst, shift)       emit_shr(BIN_TEXT, dst, shift)
#define BIN_ADD_RI(dst, imm)      emit_add_ri(BIN_TEXT, dst, imm)
#define BIN_SUB_RI(dst, imm)      emit_sub_ri(BIN_TEXT, dst, imm)
#define BIN_CMP_RI(dst, imm)      emit_cmp_ri(BIN_TEXT, dst, imm)
#define BIN_AND_RI(dst, imm)      emit_and_ri(BIN_TEXT, dst, imm)
#define BIN_OR_RI(dst, imm)       emit_or_ri(BIN_TEXT, dst, imm)
#define BIN_SETCC(op, reg)        emit_setcc(BIN_TEXT, op, reg)

#endif