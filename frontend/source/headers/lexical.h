#ifndef LEXICAL_H
#define LEXICAL_H

#include "../../../general/source/generalheaders/workwithfile.h"
#include "tokstack.h"
#include "../../../general/source/generalheaders/treefuncs.h"

TokStack_t  TokStkCtor       ();
void        TokStkDtor       (TokStack_t *stk);
void        GetTokens        (File_Info_t *info, TokStack_t *stk);
bool        GetOpToken       (char **buff, int nline, TokStack_t *stk);
void        DumpTokens       (TokStack_t *stk, int line);

int         SkipSpaces       (char **buff);

#endif