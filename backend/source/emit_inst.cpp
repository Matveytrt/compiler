#include "../headers/emit_inst.h"
#include <cassert>

static void emit_rex_b(Section_t *sec, Reg_t reg, Reg_t rm)
{
    assert(sec);

    uint8_t rex = 0x40;
    if (reg >= 8) rex |= REX_R;
    if (rm >= 8) rex |= REX_B;
    if (rex != 0x40) EMIT_BYTE(sec, rex);
}

static void emit_rex_wb(Section_t *sec, int w, Reg_t reg, Reg_t rm)
{
    assert(sec);

    uint8_t rex = 0x40;
    if (w) rex |= REX_W;
    if (reg >= 8) rex |= REX_R;
    if (rm >= 8) rex |= REX_B;
    if (rex != 0x40) EMIT_BYTE(sec, rex);
}

static void emit_modrm_reg(Section_t *sec, Reg_t reg, Reg_t rm)
{
    assert(sec);
    emit_rex_b(sec, reg, rm);
    EMIT_MODRM(sec, MOD_REG, reg & 7, rm & 7);
}

static void emit_modrm_disp(Section_t *sec, Reg_t reg, Reg_t rm, int32_t disp)
{
    assert(sec);

    uint8_t mod = MOD_INDIRECT;

    if (disp == 0 && (rm & 7) != REG_RBP) {
        mod = MOD_INDIRECT;
    } 
    
    else if (disp >= -128 && disp <= 127) {
        mod = MOD_DISP8;
    } 
    
    else {
        mod = MOD_DISP32;
    }

    emit_rex_b(sec, reg, rm);
    EMIT_MODRM(sec, mod, reg & 7, rm & 7);

    if (mod == MOD_DISP8) {
        EMIT_BYTE(sec, disp & 0xFF);
    } 
    
    else if (mod == MOD_DISP32) {
        EMIT_DWORD(sec, disp);
    }
}

void emit_mov_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);

    if (dst <= 7 && src <= 7) {
        EMIT_BYTE(sec, OPC_MOV_RR);
        EMIT_MODRM(sec, MOD_REG, dst, src);
    } 
    
    else {
        emit_rex_wb(sec, 1, src, dst);
        EMIT_BYTE(sec, OPC_MOV_RR);
        EMIT_MODRM(sec, MOD_REG, src & 7, dst & 7);
    }
}

void emit_mov_ri(Section_t *sec, Reg_t dst, int64_t imm)
{
    assert(sec);

    printf("emit_mov_ri: dst=%d, imm=%ld, bin_size=%zu\n", dst, imm, sec->bin_size);

    if (dst <= 7 && imm <= 0xFFFFFFFF && imm >= -0x80000000) {
        EMIT_BYTE(sec, OPC_MOV_RI | (dst & 7));
        EMIT_DWORD(sec, imm);
    } 

    else {
        if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
        else EMIT_REX(sec, 1, 0, 0, 0);
        EMIT_BYTE(sec, OPC_MOV_RI | (dst & 7));
        EMIT_QWORD(sec, imm);
    }

    printf("  after: bin_size=%zu\n", sec->bin_size);
}

void emit_mov_rm(Section_t *sec, Reg_t dst, Reg_t src, int32_t disp)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_MOV_RM64);
    emit_modrm_disp(sec, dst, src, disp);
}

void emit_mov_mr(Section_t *sec, Reg_t dst, int32_t disp, Reg_t src)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_MOV_MR64);
    emit_modrm_disp(sec, src, dst, disp);
}

void emit_add_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_ADD_RR);
    emit_modrm_reg(sec, dst, src);
}

void emit_sub_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_SUB_RR);
    emit_modrm_reg(sec, dst, src);
}

void emit_xor_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_XOR_RR);
    emit_modrm_reg(sec, dst, src);
}

void emit_imul_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    emit_rex_wb(sec, 1, dst, src);
    EMIT_BYTE(sec, 0x0F);
    EMIT_BYTE(sec, OPC_IMUL_RR);
    EMIT_MODRM(sec, MOD_REG, dst & 7, src & 7);
}

void emit_idiv(Section_t *sec, Reg_t reg)
{
    assert(sec);
    emit_rex_wb(sec, 1, REG_RAX, reg);
    EMIT_BYTE(sec, OPC_IDIV);
    EMIT_MODRM(sec, MOD_REG, 7, reg & 7);
}

void emit_cmp_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_CMP_RR);
    emit_modrm_reg(sec, dst, src);
}

void emit_cmp_ri(Section_t *sec, Reg_t dst, int64_t imm)
{
    assert(sec);
    assert(imm >= -0x80000000 && imm <= 0x7FFFFFFF);

    if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);

    else EMIT_REX(sec, 1, 0, 0, 0);

    EMIT_BYTE(sec, OPC_CMP_IMM);
    EMIT_MODRM(sec, MOD_REG, 7, dst & 7);
    EMIT_DWORD(sec, imm);
}

void emit_jmp(Section_t *sec, int32_t offset)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_JMP);
    EMIT_DWORD(sec, offset);
}

void emit_jcc(Section_t *sec, JCC_Cond_t cond, int32_t offset)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_JCC);
    EMIT_BYTE(sec, cond);
    EMIT_DWORD(sec, offset);
}

void emit_push(Section_t *sec, Reg_t reg)
{
    assert(sec);

    if (reg <= 7) {
        EMIT_BYTE(sec, OPC_PUSH | reg);
    } 

    else {
        EMIT_REX(sec, 0, 0, 0, 1);
        EMIT_BYTE(sec, OPC_PUSH | (reg & 7));
    }
}

void emit_pop(Section_t *sec, Reg_t reg)
{
    assert(sec);
    
    if (reg <= 7) {
        EMIT_BYTE(sec, OPC_POP | reg);
    } 

    else {
        EMIT_REX(sec, 0, 0, 0, 1);
        EMIT_BYTE(sec, OPC_POP | (reg & 7));
    }
}

void emit_ret(Section_t *sec)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_RET);
}

void emit_syscall(Section_t *sec)
{
    assert(sec);
    EMIT_BYTE(sec, 0x0F);
    EMIT_BYTE(sec, OPC_SYSCALL);
}

void emit_call(Section_t *sec, int32_t offset)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_CALL);
    EMIT_DWORD(sec, offset);
}

void emit_nop(Section_t *sec)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_NOP);
}

void emit_lea_rm(Section_t *sec, Reg_t dst, Reg_t src, int32_t disp)
{
    assert(sec);

    if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
    else EMIT_REX(sec, 1, 0, 0, 0);

    EMIT_BYTE(sec, OPC_LEA);
    emit_modrm_disp(sec, dst, src, disp);
}

void emit_and_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_AND_RR);
    emit_modrm_reg(sec, dst, src);
}

void emit_or_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_OR_RR);
    emit_modrm_reg(sec, dst, src);
}

void emit_test_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_TEST_RR);
    emit_modrm_reg(sec, dst, src);
}

void emit_not_r(Section_t *sec, Reg_t reg)
{
    assert(sec);
    if (reg <= 7) {
        EMIT_BYTE(sec, OPC_NOT_R);
        EMIT_MODRM(sec, MOD_REG, 2, reg);
    } else {
        emit_rex_b(sec, (Reg_t) 0, reg);
        EMIT_BYTE(sec, OPC_NOT_R);
        EMIT_MODRM(sec, MOD_REG, 2, reg & 7);
    }
}

void emit_shl(Section_t *sec, Reg_t dst, uint8_t shift)
{
    assert(sec);

    if (dst >= 8) {
        EMIT_REX(sec, 1, 0, 0, 1); 
    } 

    else {
        EMIT_REX(sec, 1, 0, 0, 0); 
    }
        emit_rex_b(sec, (Reg_t) 0, dst);
        EMIT_BYTE(sec, OPC_SHIFT);
        EMIT_MODRM(sec, MOD_REG, 4, dst & 7);
        EMIT_BYTE(sec, shift);
}

void emit_shr(Section_t *sec, Reg_t dst, uint8_t shift)
{
    assert(sec);

    if (dst >= 8) {
        EMIT_REX(sec, 1, 0, 0, 1); 
    } 

    else {
        EMIT_REX(sec, 1, 0, 0, 0); 
    }
        emit_rex_b(sec, (Reg_t) 0, dst);
        EMIT_BYTE(sec, OPC_SHIFT);
        EMIT_MODRM(sec, MOD_REG, 5, dst & 7);
        EMIT_BYTE(sec, shift);
}

void emit_add_ri(Section_t *sec, Reg_t dst, int64_t imm)
{
    assert(sec);

    if (imm <= 0x7F && imm >= -0x80) {
        EMIT_BYTE(sec, OPC_ADD_RI);
        EMIT_MODRM(sec, MOD_REG, 0, dst & 7);
        EMIT_BYTE(sec, imm & 0xFF);
    } 
    else {
        if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
        else EMIT_REX(sec, 1, 0, 0, 0);
        EMIT_BYTE(sec, OPC_ADD_RI);
        EMIT_MODRM(sec, MOD_REG, 0, dst & 7);
        EMIT_DWORD(sec, imm);
    }
}

void emit_sub_ri(Section_t *sec, Reg_t dst, int64_t imm)
{
    assert(sec);

    if (imm <= 0x7F && imm >= -0x80) {
        EMIT_BYTE(sec, OPC_SUB_RI);
        EMIT_MODRM(sec, MOD_REG, 5, dst & 7);
        EMIT_BYTE(sec, imm & 0xFF);
    } 
    
    else {
        if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
        else EMIT_REX(sec, 1, 0, 0, 0);
        EMIT_BYTE(sec, OPC_SUB_RI);
        EMIT_MODRM(sec, MOD_REG, 5, dst & 7);
        EMIT_DWORD(sec, imm);
    }
}

void emit_and_ri(Section_t *sec, Reg_t dst, int64_t imm)
{
    assert(sec);

    if (imm <= 0x7F && imm >= -0x80) {
        EMIT_BYTE(sec, OPC_AND_RI);
        EMIT_MODRM(sec, MOD_REG, 4, dst & 7);
        EMIT_BYTE(sec, imm & 0xFF);
    } 
    
    else {
        if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
        else EMIT_REX(sec, 1, 0, 0, 0);
        EMIT_BYTE(sec, OPC_AND_RI);
        EMIT_MODRM(sec, MOD_REG, 4, dst & 7);
        EMIT_DWORD(sec, imm);
    }
}

void emit_or_ri(Section_t *sec, Reg_t dst, int64_t imm)
{
    assert(sec);
    
    if (imm <= 0x7F && imm >= -0x80) {
        EMIT_BYTE(sec, OPC_OR_RI);
        EMIT_MODRM(sec, MOD_REG, 1, dst & 7);
        EMIT_BYTE(sec, imm & 0xFF);
    } 
    
    else {
        if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
        else EMIT_REX(sec, 1, 0, 0, 0);
        EMIT_BYTE(sec, OPC_OR_RI);
        EMIT_MODRM(sec, MOD_REG, 1, dst & 7);
        EMIT_DWORD(sec, imm);
    }
}

void emit_setcc(Section_t *sec, SetCCOp_t op, Reg_t reg)
{
    assert(sec);
    if (reg >= 8) EMIT_REX(sec, 0, 0, 0, 1);
    EMIT_BYTE(sec, OPC_SETCC);
    EMIT_BYTE(sec, op);
    EMIT_MODRM(sec, MOD_REG, 0, reg & 7);
}

void emit_movzx_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);
    emit_rex_wb(sec, 0, dst, src);
    EMIT_BYTE(sec, OPC_JCC);
    EMIT_BYTE(sec, OPC_MOVZX);
    EMIT_MODRM(sec, MOD_REG, dst & 7, src & 7);
}

void emit_mov_mr_label(Section_t *sec, Reg_t src)
{
    assert(sec);
    if (src >= 8) EMIT_REX(sec, 0, 0, 0, 1);
    EMIT_BYTE(sec, OPC_MOV_MR64);
    EMIT_MODRM(sec, MOD_INDIRECT, src & 7, 5);
}

void emit_mov_rm_label(Section_t *sec, Reg_t dst)
{
    assert(sec);
    if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
    EMIT_BYTE(sec, OPC_MOV_RM64);
    EMIT_MODRM(sec, MOD_INDIRECT, dst & 7, 5);
}

void emit_lea_label(Section_t *sec, Reg_t dst)
{
    assert(sec);
    if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
    EMIT_BYTE(sec, OPC_LEA);
    EMIT_MODRM(sec, MOD_INDIRECT, dst & 7, 5);
}