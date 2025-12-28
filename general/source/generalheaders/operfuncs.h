#ifndef OPERFUNCS_H
#define OPERFUNCS_H

#include "treefuncs.h"

void GetAsmAdd             (Node_t *node, FILE *file);     
void GetAsmSub             (Node_t *node, FILE *file);     
void GetAsmMul             (Node_t *node, FILE *file);         
void GetAsmDiv             (Node_t *node, FILE *file);
void GetAsmSqrt            (Node_t *node, FILE *file);
void GetAsmSkip            (Node_t *node, FILE *file);     
void GetAsmInfixIf         (Node_t *node, FILE *file); 
void GetAsmInfixElse       (Node_t *node, FILE *file);     
void GetAsmInfixWhile      (Node_t *node, FILE *file);
void GetAsmPostIf          (Node_t *node, FILE *file); 
void GetAsmPostElse        (Node_t *node, FILE *file);     
void GetAsmPostWhile       (Node_t *node, FILE *file);     
void GetAsmFor             (Node_t *node, FILE *file);     
void GetAsmRet             (Node_t *node, FILE *file);     
void GetAsmAssign          (Node_t *node, FILE *file);     
void GetAsmMemget          (Node_t *node, FILE *file);     
void GetAsmMemset          (Node_t *node, FILE *file);
void GetAsmPrint           (Node_t *node, FILE *file);     
void GetAsmScanf           (Node_t *node, FILE *file);     
void GetAsmFDecl           (Node_t *node, FILE *file);     
void GetAsmVDecl           (Node_t *node, FILE *file);     
void GetAsmStrEnd          (Node_t *node, FILE *file);

void PushVar               (Node_t *node, FILE *file);
void PopVar                (Node_t *node, FILE *file);

#endif