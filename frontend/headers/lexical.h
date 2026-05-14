#ifndef LEXICAL_H
#define LEXICAL_H

#include "../../general/generalheaders/workwithfile.h"
#include "../../general/generalheaders/treefuncs.h"
#include "tokstack.h"

TokStack_t  TokStkCtor       ();
void        TokStkDtor       (TokStack_t *stk);
void        GetTokens        (File_Info_t *info, TokStack_t *stk);
bool        GetOpToken       (char **buff, int nline, TokStack_t *stk);
void        DumpTokens       (TokStack_t *stk, int line);

int         SkipSpaces       (char **buff);

#endif