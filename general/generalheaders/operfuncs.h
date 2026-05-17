#ifndef OPERFUNCS_H
#define OPERFUNCS_H

#include "treefuncs.h"

void Do_VM_ADD             (Node_t *node, FILE *file);     
void Do_VM_SUB             (Node_t *node, FILE *file);     
void Do_VM_MUL             (Node_t *node, FILE *file);         
void Do_VM_DIV             (Node_t *node, FILE *file);
void Do_VM_SQRT            (Node_t *node, FILE *file);
void Do_VM_EQ              (Node_t *node, FILE *file);
void Do_VM_NEQ             (Node_t *node, FILE *file);
void Do_VM_ABOVE_EQ        (Node_t *node, FILE *file);
void Do_VM_BELOW_EQ        (Node_t *node, FILE *file);
void Do_VM_ABOVE           (Node_t *node, FILE *file);
void Do_VM_BELOW           (Node_t *node, FILE *file);
void Do_VM_NOT             (Node_t *node, FILE *file);
void Do_VM_AND             (Node_t *node, FILE *file);
void Do_VM_OR              (Node_t *node, FILE *file);

void Do_VM_SKIP            (Node_t *node, FILE *file);     
void Do_VM_InfixIF         (Node_t *node, FILE *file); 
void Do_VM_InfixELSE       (Node_t *node, FILE *file);     
void Do_VM_InfixWHILE      (Node_t *node, FILE *file);
void Do_VM_IF              (Node_t *node, FILE *file); 
void Do_VM_ELSE            (Node_t *node, FILE *file);     
void Do_VM_WHILE           (Node_t *node, FILE *file);     
void Do_VM_FOR             (Node_t *node, FILE *file);     
void Do_VM_RET             (Node_t *node, FILE *file);     
void Do_VM_ASSIGN          (Node_t *node, FILE *file);     
void Do_VM_MEMGET          (Node_t *node, FILE *file);     
void Do_VM_MEMSET          (Node_t *node, FILE *file);
void Do_VM_Print           (Node_t *node, FILE *file);     
void Do_VM_Scanf           (Node_t *node, FILE *file);     

void PushVar               (Node_t *node, FILE *file);
void PopVar                (Node_t *node, FILE *file);

#define VM_PUSH_(value)         fprintf(file, "PUSH %d\n", value)
#define VM_PUSHR_(name)         fprintf(file, "PUSHR %s\n", name)
#define VM_PUSHM_(name)         fprintf(file, "PUSHM [%s]\n", name)
#define VM_POP_(value)          fprintf(file, "POP %d\n", value)
#define VM_POPR_(name)          fprintf(file, "POPR %s\n", name)
#define VM_POPM_(name)          fprintf(file, "POPM [%s]\n", name)
#define VM_CALL_(label)         fprintf(file, "CALL :%s\n", label)
#define VM_LBL_(name, ptr)      fprintf(file, ":%s_%p\n", name, ptr)
#define VM_STRT_(name)          fprintf(file, ":%s\n", name);
#define VM_TEXT_(text, ...)     fprintf(file, text "\n", ##__VA_ARGS__);
                             
#define VM_JMP_(name, lbl, ptr) fprintf(file, "%s ", name);\
                             VM_LBL_(lbl, ptr)

#endif