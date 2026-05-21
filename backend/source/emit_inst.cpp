#include "../headers/emit_inst.h"
#include <cassert>

//=============================================================================
// Help funcs
//=============================================================================

static void emit_rex_b(Section_t *sec, Reg_t reg, Reg_t rm)
{
    assert(sec);

    uint8_t rex = REX_BASE;
    if (reg >= 8) rex |= REX_R;
    if (rm >= 8) rex |= REX_B;
    if (rex != REX_BASE) EMIT_BYTE(sec, rex);
}

static void emit_rex_wb(Section_t *sec, int w, Reg_t reg, Reg_t rm)
{
    assert(sec);

    uint8_t rex = REX_BASE;
    if (w) rex |= REX_W;
    if (reg >= 8) rex |= REX_R;
    if (rm >= 8) rex |= REX_B;
    if (rex != REX_BASE) EMIT_BYTE(sec, rex);
}

static void emit_modrm_disp(Section_t *sec, Reg_t reg, Reg_t rm, int32_t disp)
{
    assert(sec);

    uint8_t mod = MOD_INDIRECT;

    if (disp == 0 && (rm & 7) != REG_RBP) 
        { mod = MOD_INDIRECT; } 

    else if (disp >= -128 && disp <= 127) 
        { mod = MOD_DISP8; } 

    else 
        { mod = MOD_DISP32; }

    emit_rex_b(sec, reg, rm);
    EMIT_MODRM(sec, mod, reg & 7, rm & 7);

    if (mod == MOD_DISP8) 
        { EMIT_BYTE(sec, disp & 0xFF); } 
    
    else if (mod == MOD_DISP32) 
        { EMIT_DWORD(sec, disp); }
}

//=============================================================================
// Arith Reg2Reg
//=============================================================================

void emit_arith_rr(Section_t *sec, ArithOp_t op, Reg_t dst, Reg_t src)
{
    assert(sec);
    
    uint8_t opcode = 0;

    switch (op) {
        case ARITH_ADD:  opcode = OPC_ADD_RR; break;
        case ARITH_SUB:  opcode = OPC_SUB_RR; break;
        case ARITH_XOR:  opcode = OPC_XOR_RR; break;
        case ARITH_AND:  opcode = OPC_AND_RR; break;
        case ARITH_OR:   opcode = OPC_OR_RR;  break;
        case ARITH_CMP:  opcode = OPC_CMP_RR; break;
        case ARITH_TEST: opcode = OPC_TEST_RR; break;
        default: assert(0); break;
    }
    
    uint8_t rex = REX_64;
    if (src >= 8) rex |= REX_R;
    if (dst >= 8) rex |= REX_B;
    EMIT_BYTE(sec, rex);
    
    EMIT_BYTE(sec, opcode);
    EMIT_MODRM(sec, MOD_REG, dst & 7, src & 7);
}

void emit_imul_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);

    emit_rex_wb(sec, 1, dst, src);
    EMIT_BYTE(sec, OPC_TWO_BYTE_PREFIX);
    EMIT_BYTE(sec, OPC_IMUL_RR);
    EMIT_MODRM(sec, MOD_REG, dst & 7, src & 7);
}

void emit_idiv(Section_t *sec, Reg_t reg)
{
    assert(sec);

    emit_rex_wb(sec, 1, REG_RAX, reg);
    EMIT_BYTE(sec, OPC_IDIV);
    EMIT_MODRM(sec, MOD_REG, MODRM_REG_IDIV, reg & 7);
}

void emit_not_r(Section_t *sec, Reg_t reg)
{
    assert(sec);

    uint8_t rex = REX_64;
    if (reg >= 8) rex |= REX_B;
    EMIT_BYTE(sec, rex);

    EMIT_BYTE(sec, OPC_NOT_R);
    EMIT_MODRM(sec, MOD_REG, MODRM_REG_NOT, reg & 7);
}

//=============================================================================
// Arith Imm2Reg
//=============================================================================

void emit_arith_ri(Section_t *sec, ArithOp_t op, Reg_t dst, int64_t imm)
{
    assert(sec);
    
    uint8_t modrm_reg = 0;

    switch (op) {
        case ARITH_ADD: modrm_reg = MODRM_REG_ADD; break;
        case ARITH_SUB: modrm_reg = MODRM_REG_SUB; break;
        case ARITH_AND: modrm_reg = MODRM_REG_AND; break;
        case ARITH_OR:  modrm_reg = MODRM_REG_OR;  break;
        default: assert(0); break;
    }
    
    uint8_t rex_base = (dst >= 8) ? REX_64_B : REX_64;
    
    if (imm <= 0x7F && imm >= -0x80) {
        EMIT_BYTE(sec, rex_base);
        EMIT_BYTE(sec, OPC_ADD_RI);
        EMIT_MODRM(sec, MOD_REG, modrm_reg, dst & 7);
        EMIT_BYTE(sec, imm & 0xFF);
    } 
    
    else {
        EMIT_BYTE(sec, rex_base);
        EMIT_BYTE(sec, OPC_CMP_IMM);
        EMIT_MODRM(sec, MOD_REG, modrm_reg, dst & 7);
        EMIT_DWORD(sec, imm);
    }
}

void emit_cmp_ri(Section_t *sec, Reg_t dst, int64_t imm)
{
    assert(sec);

    assert(imm >= -0x80000000 && imm <= 0x7FFFFFFF);

    if (dst >= 8) EMIT_REX(sec, 1, 0, 0, 1);
    else EMIT_REX(sec, 1, 0, 0, 0);

    EMIT_BYTE(sec, OPC_CMP_IMM);
    EMIT_MODRM(sec, MOD_REG, MODRM_REG_CMP, dst & 7);
    EMIT_DWORD(sec, imm);
}

//=============================================================================
// MOV
//=============================================================================

void emit_mov_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);

    uint8_t rex = REX_64;
    if (src >= 8) rex |= REX_R;
    if (dst >= 8) rex |= REX_B;
    EMIT_BYTE(sec, rex);

    EMIT_BYTE(sec, OPC_MOV_RR);
    EMIT_MODRM(sec, MOD_REG, src & 7, dst & 7);
}

void emit_mov_ri(Section_t *sec, Reg_t dst, int64_t imm)
{
    assert(sec);
    
    uint8_t rex = REX_64;
    if (dst >= 8) rex |= REX_B;
    EMIT_BYTE(sec, rex);

    EMIT_BYTE(sec, OPC_MOV_RI | (dst & 7));
    EMIT_QWORD(sec, imm);
}

void emit_mov_rm(Section_t *sec, Reg_t dst, Reg_t src, int32_t disp)
{
    assert(sec);

    uint8_t rex = REX_64;
    if (dst >= 8) rex |= REX_R;
    if (src >= 8) rex |= REX_B;
    EMIT_BYTE(sec, rex);

    EMIT_BYTE(sec, OPC_MOV_RM64);
    emit_modrm_disp(sec, dst, src, disp);
}

void emit_mov_mr(Section_t *sec, Reg_t dst, int32_t disp, Reg_t src)
{
    assert(sec);

    uint8_t rex = REX_64;
    if (src >= 8) rex |= REX_R;
    if (dst >= 8) rex |= REX_B;
    EMIT_BYTE(sec, rex); 

    EMIT_BYTE(sec, OPC_MOV_MR64);
    emit_modrm_disp(sec, src, dst, disp);
}

void emit_movzx_rr(Section_t *sec, Reg_t dst, Reg_t src)
{
    assert(sec);

    emit_rex_wb(sec, 0, dst, src);
    EMIT_BYTE(sec, OPC_TWO_BYTE_PREFIX);
    EMIT_BYTE(sec, OPC_MOVZX);
    EMIT_MODRM(sec, MOD_REG, dst & 7, src & 7);
}

//=============================================================================
// LEA
//=============================================================================

void emit_lea_rm(Section_t *sec, Reg_t dst, Reg_t src, int32_t disp)
{
    assert(sec);

    uint8_t rex = REX_64;
    if (dst >= 8) rex |= REX_R;
    if (src >= 8) rex |= REX_B;
    EMIT_BYTE(sec, rex);  
    
    EMIT_BYTE(sec, OPC_LEA);
    emit_modrm_disp(sec, dst, src, disp);
}

//=============================================================================
// Shifts
//=============================================================================

void emit_shift(Section_t *sec, ShiftOp_t op, Reg_t dst, uint8_t shift)
{
    assert(sec);
    
    uint8_t modrm_reg = (op == SHIFT_SHL) ? MODRM_REG_SHL : MODRM_REG_SHR;
    
    uint8_t rex = REX_64;
    if (dst >= 8) rex |= REX_B;
    EMIT_BYTE(sec, rex);
    
    EMIT_BYTE(sec, OPC_SHIFT);
    EMIT_MODRM(sec, MOD_REG, modrm_reg, dst & 7);
    EMIT_BYTE(sec, shift);
}

void emit_shl(Section_t *sec, Reg_t dst, uint8_t shift)
{
    emit_shift(sec, SHIFT_SHL, dst, shift);
}

void emit_shr(Section_t *sec, Reg_t dst, uint8_t shift)
{
    emit_shift(sec, SHIFT_SHR, dst, shift);
}

//=============================================================================
// Stack
//=============================================================================

void emit_stack(Section_t *sec, StackOp_t op, Reg_t reg)
{
    assert(sec);
    
    uint8_t base_op = (op == STACK_PUSH) ? OPC_PUSH : OPC_POP;
    
    if (reg <= 7) {
        EMIT_BYTE(sec, base_op | reg);
    } else {
        EMIT_REX(sec, 0, 0, 0, 1);
        EMIT_BYTE(sec, base_op | (reg & 7));
    }
}

void emit_push(Section_t *sec, Reg_t reg)
{
    emit_stack(sec, STACK_PUSH, reg);
}

void emit_pop(Section_t *sec, Reg_t reg)
{
    emit_stack(sec, STACK_POP, reg);
}

//=============================================================================
// Jumps
//=============================================================================

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

void emit_call(Section_t *sec, int32_t offset)
{
    assert(sec);

    EMIT_BYTE(sec, OPC_CALL);
    EMIT_DWORD(sec, offset);
}

void emit_ret(Section_t *sec)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_RET);
}

//=============================================================================
// Other
//=============================================================================

void emit_nop(Section_t *sec)
{
    assert(sec);
    EMIT_BYTE(sec, OPC_NOP);
}

void emit_syscall(Section_t *sec)
{
    assert(sec);

    EMIT_BYTE(sec, OPC_JCC);
    EMIT_BYTE(sec, OPC_SYSCALL);
}

void emit_setcc(Section_t *sec, SetCCOp_t op, Reg_t reg)
{
    assert(sec);
    if (reg >= 8) EMIT_REX(sec, 0, 0, 0, 1);
    EMIT_BYTE(sec, OPC_SETCC);
    EMIT_BYTE(sec, op);
    EMIT_MODRM(sec, MOD_REG, 0, reg & 7);
}

//=============================================================================
// Label emitters
//=============================================================================

void emit_label(Section_t *sec, LabelOp_t op, Reg_t reg)
{
    assert(sec);
    
    uint8_t opcode = 0;
    int rex_w = 0;
    
    switch (op) {
        case LABEL_MOV_MR:
            opcode = OPC_MOV_MR64;
            rex_w = 0;
            break;
        case LABEL_MOV_RM:
            opcode = OPC_MOV_RM64;
            rex_w = 1;
            break;
        case LABEL_LEA:
            opcode = OPC_LEA;
            rex_w = 1;
            break;
        default:
            assert(0);
            break;
    }
    
    if (rex_w && (reg >= 8)) 
        { EMIT_REX(sec, 1, 0, 0, 1); } 

    else if (rex_w) 
        { EMIT_REX(sec, 1, 0, 0, 0); } 

    else if (reg >= 8)
        { EMIT_REX(sec, 0, 0, 0, 1); }
    
    EMIT_BYTE(sec, opcode);
    EMIT_MODRM(sec, MOD_INDIRECT, reg & 7, 5);
}

void emit_mov_mr_label(Section_t *sec, Reg_t src)
{
    emit_label(sec, LABEL_MOV_MR, src);
}

void emit_mov_rm_label(Section_t *sec, Reg_t dst)
{
    emit_label(sec, LABEL_MOV_RM, dst);
}

void emit_lea_label(Section_t *sec, Reg_t dst)
{
    emit_label(sec, LABEL_LEA, dst);
}