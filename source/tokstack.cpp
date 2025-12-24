#include "tokstack.h"

#define TYPE_ELEM       "%p"

#define ERROR        fprintf(Tokstk_log, "error: %d line: %d\n", err.code, err.line);
#define INFO         fprintf(Tokstk_log, "%s:%d Tokstack size = %ld, capacity = %ld\n", __func__, line, stk->size, stk->capacity);
#define NEWLINE      fprintf(Tokstk_log, "\n");
#define VERIFY(stk)  TokStackVerify(stk, line)
#define CANARY       0xEDAA
#define ERRORPOINT   0xBADDD
#define WARNINGPOINT 0xBED
#define NOERROR      0x0
#define STARTSIZE    10
#define STRSIZE      200
#define CHECKFUNCERROR(error)   if (error.type == ERRORPOINT)                                         \
                                {                                                                     \
                                fprintf(Tokstk_log, "err.code = %d, line: %d\n", error.code, error.line);\
                                return error;                                                         \
                                }

enum tok_errors 
{
    NULLSTKPTR        = 1 << 0, 
    NULLDATAPTR       = 1 << 1, 
    NEGATIVECAPACITY  = 1 << 2, 
    STKATTACKLEFT     = 1 << 3, 
    STKATTACKRIGHT    = 1 << 4, 
    HASHTRASH         = 1 << 5, 
    STRUCTATTACKLEFT  = 1 << 6, 
    STRUCTATTACKRIGHT = 1 << 7, 
    ERRORS_END        = 1 << 8,
    POISONING         = 1 << 9, 
    SIZELIMIT         = 1 << 10, 
};

FILE *Tokstk_log = NULL;

TokStackErr_t TokStackVerify(ONDEBUGTOKARGS(TokStack_t *stk, int line));  
TokStackErr_t AllocationStk(TokStack_t *stk);
TokStackErr_t TokStackOk(TokStack_t *stk, TokStackErr_t err, int line);
int ErrorType(TokStackErr_t err);
Ssize_t CalcHASHTok(ONDEBUGTOKARGS(TokStack_t *stk));
void CheckSize(TokStack_t *stk); 

TokStackErr_t TokStackInit(TokStack_t *stk, int capacity, int line)
{ 
    assert(stk);

    TokStackErr_t error ={};
    stk->size = 0;

    Tokstk_log = fopen("tokenstk.log", "w");
    assert(Tokstk_log);

    #ifdef DEBUGTOK
        if (capacity < 0)
        {
            error.code = NEGATIVECAPACITY;
            return error;
        } 

        else 
        {
            stk->capacity = capacity;
        }
    #else
        stk->capacity = capacity;
    #endif

    #ifdef CANARY_DEBUGTOK
        stk->capacity += 2;
        
        error = AllocationStk(stk);

        stk->canaryleft = CANARY;
        stk->canaryright = CANARY;
        stk->data[0] = CANARY;
        stk->data[stk->capacity - 1] = CANARY;
        stk->flag = 0;   
    #else
        error = AllocationStk(stk);

        stk->flag = -1;
    #endif
    
    #ifdef DEBUGTOK
        INFO
        stk->hash = CalcHASHTok(stk);
        error = VERIFY(stk);
        if (error.code == NOERROR)
        {
            fprintf(Tokstk_log, "Initialisation succses\n");
        }
    #else
        INFO
        fprintf(Tokstk_log, "Initialisation succses\n");
    #endif

    return error;
}

TokStackErr_t TokStackPush(TokStack_t *stk, TokStackElement_t value, int line)
{
    assert(stk);

    #ifdef DEBUGTOK
        TokStackErr_t error = VERIFY(stk);
        CHECKFUNCERROR(error);
    #else
        TokStackErr_t error = {};
    #endif

    stk->size++;
    CheckSize(stk);

    stk->data[stk->size + stk->flag] = value;

    fprintf(Tokstk_log, "line: %d pushed value = " TYPE_ELEM "\n", line, stk->data[stk->size + stk->flag]);
    INFO

    #ifdef DEBUGTOK
        stk->hash = CalcHASHTok(stk);
        error = VERIFY(stk);
    #endif

    return error;
}

TokStackElement_t TokStackPop(TokStack_t *stk, TokStackErr_t *error, int line)
{
    assert(stk);
    assert(error);
    
    #ifdef DEBUGTOK
        *error = VERIFY(stk);
        CHECKFUNCERROR(error);
    #else
        *error = {};
    #endif

    TokStackElement_t last_input = stk->data[stk->size + stk->flag];

    if (stk->size > 0)
    {
        #ifdef DEBUGTOK
            stk->data[stk->size + stk->flag] = POISON;
        #else
            //stk->data[stk->size + stk->flag] = 0;
        #endif

        stk->size--;

        #ifdef DEBUGTOK
            stk->hash = CalcHASHTok(stk);
        #endif
    }

    fprintf(Tokstk_log, "line: %d popped value =" TYPE_ELEM "\n", line,  last_input);

    #ifdef DEBUGTOK
        else
        {
            fprintf(Tokstk_log, "can't pop: empty Tokstack\n");
            error.code = SIZELIMIT;
            last_input = 0;
            *error = TokStackOk(stk, *error, line);
            return last_input;
        }

        *error = VERIFY(stk);
    #endif

    NEWLINE
    INFO 

    return last_input;
}

TokStackErr_t TokStackDestroy(TokStack_t *stk, int line)
{
    assert(stk);
    
    #ifdef DEBUGTOK
        TokStackErr_t error = VERIFY(stk);
        CHECKFUNCERROR(error);

    #else
        TokStackErr_t error = {};
    #endif

    NEWLINE
    fprintf(Tokstk_log, "info about Tokstack before death:\n");
    INFO

    free(stk->data);
    fclose(Tokstk_log);

    return error;
}

TokStackErr_t TokStackVerify(ONDEBUGTOKARGS(TokStack_t *stk, int line))
{  
    
    TokStackErr_t err = {};
    
    #ifdef DEBUGTOK
        assert(stk);
        err.line = line;
        err.type = NOERROR;

        if (stk <= NULL)
        {
            err.code |= NULLSTKPTR;
            printf("stkptr err.code = %d\n", err.code);
        }
        #ifdef CANARY_DEBUGTOK
            if (stk->canaryleft != CANARY)
            {
                err.code |= STRUCTATTACKLEFT;
                printf("left err.code = %d\n", err.code);
                err = TokStackOk(stk, err, line);
                return err;
            }
            if (stk->canaryright != CANARY)
            {
                err.code |= STRUCTATTACKRIGHT; 
                printf("right err.code = %d\n", err.code);
                err = TokStackOk(stk, err, line);
                return err; 
            }
        #endif
        if (stk->data <= NULL)
        {
            err.code |= NULLDATAPTR;
            printf("dataptr err.code = %d\n", err.code);
            err = TokStackOk(stk, err, line);
            return err;
        }

        else
        {
            if (stk->capacity < 0)
            {
                err.code |= NEGATIVECAPACITY;
                printf("cap err.code = %d\n", err.code);
            }
            for (Ssize_t i = 0; i <= stk->size + stk->flag; i++)
            {
                if (stk->data[i] == POISON)
                {
                    err.code |= POISONING;
                    fprintf(Tokstk_log, "TokStack POISONing from %ld position\n", i); 
                    break;
                }
            }
            if (stk->hash != CalcHASHTok(stk))
            {
                err.code |= HASHTRASH;
            }
            if ( stk->size > (stk->capacity CANDEBUGTOK(-2)))
            {
                err.code |= SIZELIMIT;
            }
        }  
          
    #endif

    #ifdef CANARY_DEBUGTOK
        if (stk->data > NULL)
        {
            if (stk->data[0] != CANARY)
            {
                err.code |= STKATTACKLEFT;
            }
            if (stk->data[stk->capacity - 1] != CANARY)
            {
                err.code |= STKATTACKRIGHT;   
            }
        }  
    #endif

    ONDEBUGTOK(err = TokStackOk(stk, err, line));
    
    return err;
}

TokStackErr_t TokStackDump(TokStack_t *stk, int line, const char *filename, const char *stkname)
{
    #ifdef DEBUGTOK
        assert(stk);
        assert(filename);
        assert(stkname);
        TokStackErr_t error = TokStackVerify(stk, line);
        CHECKFUNCERROR(error);
    #else
        TokStackErr_t error = {};
    #endif

    NEWLINE
    fprintf(Tokstk_log, "Tokstack name: %s\nTokStackDump called from %s: %d\n", stkname, filename, line);
    
    if (error.type != ERRORPOINT)
    {
        INFO
        NEWLINE

        for (Ssize_t index = 0; index < stk->capacity; index++)
        {
            #ifdef DEBUGTOK
                if (stk->data[index] == POISON) 
                {
                    fprintf(Tokstk_log, "*[%ld] = %d POISON\n", index, stk->data[index]);
                }
                else if (stk->data[index] == CANARY)
                {
                    fprintf(Tokstk_log, "*[%ld] = %d CANARY\n", index, stk->data[index]);
                } 
                else
                {
                    fprintf(Tokstk_log, "[%ld] = " TYPE_ELEM "\n", index, stk->data[index]);
                }
            #else
                if (index == stk->size) break;

                fprintf(Tokstk_log, "[%ld] = " TYPE_ELEM "\n", index, stk->data[index]);
            #endif    
        }
    }

    ONDEBUGTOK(error = TokStackVerify(stk, line));

    return error;
}

Ssize_t CalcHASHTok(ONDEBUGTOKARGS(TokStack_t *stk))
{   
    #ifdef DEBUGTOK
        assert(stk);

        Ssize_t hash = stk->capacity + stk->size CANDEBUGTOK(+ stk->canaryleft + stk->canaryright);

        
        for (Ssize_t i = 0; i < stk->capacity; i++)
        {
            ONDEBUGTOK(hash += stk->data[i] * (i + 1));
        }

        return hash;
    #else
        return 0;
    #endif
}    

void CheckSize(TokStack_t *stk)
{
    assert(stk);

    Ssize_t last_capacity = stk->capacity;

    if (stk->size >= (stk->capacity CANDEBUGTOK(-2)))
    {
        stk->capacity *= 2;
        stk->data = (TokStackElement_t*) realloc(stk->data, (size_t) stk->capacity * sizeof(TokStackElement_t));

        assert(stk->data);

            for (Ssize_t i = last_capacity CANDEBUGTOK(-1); i < stk->capacity - 1; i++)
            {
                ONDEBUGTOK(stk->data[i] = POISON);
                ONDEBUGTOK(stk->data[i] = NULL);
            }   

            fprintf(Tokstk_log, "succesful reallocation\n"); 
        
            
        CANDEBUGTOK(stk->data[stk->capacity - 1] = CANARY;)
        ONDEBUGTOK(stk->hash = CalcHASHTok(stk);)
    }
}

TokStackErr_t AllocationStk(TokStack_t *stk)
{
    assert(stk);
    
    TokStackErr_t err = {};
    TokStackElement_t *alloc_ptr = (TokStackElement_t*) calloc((size_t)stk->capacity, sizeof(TokStackElement_t));

    #ifdef DEBUGTOK
        if (alloc_ptr == NULL)
        {
            fprintf(Tokstk_log, "allocation error\n"); 
            err.code = NULLDATAPTR;  
        }

        else
        {
            stk->data = alloc_ptr;
            err.code = NOERROR;
        }
    #else
        stk->data = alloc_ptr;
    #endif

    return err;
}

TokStackErr_t TokStackOk(TokStack_t *stk, TokStackErr_t err, int line)
{
    assert(stk);

    if ((err.code & NULLSTKPTR))
    {
        fprintf(Tokstk_log, "line: %d Error: TokStack pointer = NULL\n", line);      
    }
    if (err.code & NULLDATAPTR)
    {
        fprintf(Tokstk_log, "line: %d Error: Data pointer = NULL\n", line);     
    }
    if (err.code & NEGATIVECAPACITY)
    {
        fprintf(Tokstk_log, "line: %d Error: Capacity too small!\n", line);  
    }
    if (err.code & STKATTACKLEFT)
    {
        fprintf(Tokstk_log, "line: %d Error: TokStack attack from the left\n", line);      
    }
    if (err.code & STKATTACKRIGHT)
    {
        fprintf(Tokstk_log, "line: %d Error: TokStack attack from the right\n", line);      
    }
    if (err.code & STRUCTATTACKRIGHT)
    {
        fprintf(Tokstk_log, "line: %d Error: Struct attack from the right\n", line);      
    }
    if (err.code & STRUCTATTACKLEFT)
    {
        fprintf(Tokstk_log, "line: %d Error: Struct attack from the left\n", line);     
    }
    if (err.code & SIZELIMIT)
    {
        fprintf(Tokstk_log, "line: %d Warning: Size limit errors\n", line);      
    }
    if (err.code & POISONING)
    {
        fprintf(Tokstk_log, "line: %d Warning: TokStack poisoning\n", line);      
    }
    if (err.code & HASHTRASH)
    {
        fprintf(Tokstk_log, "line: %d Error: hash violation\n", line);
    }
    
    err.type = ErrorType(err);

    return err;
}

int ErrorType(TokStackErr_t err)
{
    if (err.code == 0)
    {
        return NOERROR;
    }
    else if (err.code < ERRORS_END)
    {
        return ERRORPOINT;
    }
    else
    {
        return WARNINGPOINT;
    }
}