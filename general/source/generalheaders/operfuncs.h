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

#define PUSH_(value)         fprintf(file, "PUSH %d\n", value)
#define PUSHR_(name)         fprintf(file, "PUSHR %s\n", name)
#define PUSHM_(name)         fprintf(file, "PUSHM [%s]\n", name)
#define POP_(value)          fprintf(file, "POP %d\n", value)
#define POPR_(name)          fprintf(file, "POPR %s\n", name)
#define POPM_(name)          fprintf(file, "POPM [%s]\n", name)
#define CALL_(label)         fprintf(file, "CALL :%s\n", label)
#define LBL_(name, ptr)      fprintf(file, ":%s_%p\n", name, ptr)
#define STRT_(name)          fprintf(file, ":%s\n", name);
#define TEXT_(text, ...)     fprintf(file, text, ##__VA_ARGS__); \
                             fprintf(file, "\n");
                             
#define JMP_(name, lbl, ptr) fprintf(file, "%s ", name);\
                             LBL_(lbl, ptr)

#endif