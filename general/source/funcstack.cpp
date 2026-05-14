#include "../generalheaders/funcstack.h"

#define TYPE_ELEM       "%s"
#define ERROR        fprintf(Funcstk_log, "error: %d line: %d\n", err.code, err.line);
#define INFO         fprintf(Funcstk_log, "%s:%d Funcstack size = %ld, capacity = %ld\n", __func__, line, stk->size, stk->capacity);
#define NEWLINE      fprintf(Funcstk_log, "\n");
#define VERIFY(stk)  FuncStackVerify(stk, line)
#define CANARY       0xEDAA
#define ERRORPOINT   0xBADDD
#define WARNINGPOINT 0xBED
#define NOERROR      0x0
#define STARTSIZE    10
#define STRSIZE      200
#define CHECKFUNCERROR(error)   if (error.type == ERRORPOINT)                                         \
                                {                                                                     \
                                fprintf(Funcstk_log, "err.code = %d, line: %d\n", error.code, error.line);\
                                return error;                                                         \
                                } 

enum func_errors 
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

FILE *Funcstk_log = NULL;

FuncStackErr_t FuncStackVerify(ONDEBUGFUNCARGS(FuncStack_t *stk, int line));  
FuncStackErr_t AllocationStk(FuncStack_t *stk);
FuncStackErr_t FuncStackOk(FuncStack_t *stk, FuncStackErr_t err, int line);
int ErrorType(FuncStackErr_t err);
Ssize_t CalcHASHFunc(ONDEBUGFUNCARGS(FuncStack_t *stk));
void CheckSize(FuncStack_t *stk); 

FuncStackErr_t FuncStackInit(FuncStack_t *stk, int capacity, int line)
{ 
    assert(stk);

    FuncStackErr_t error ={};
    stk->size = 0;

    Funcstk_log = fopen("general/stklogs/funcstk.log", "w");
    assert(Funcstk_log);

    #ifdef DEBUGFUNC
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

    #ifdef CANARY_DEBUGFUNC
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
    
    #ifdef DEBUGFUNC
        INFO
        stk->hash = CalcHASHFunc(stk);
        error = VERIFY(stk);
        if (error.code == NOERROR)
        {
            fprintf(Funcstk_log, "Initialisation succses\n");
        }
    #else
        INFO
        fprintf(Funcstk_log, "Initialisation succses\n");
    #endif

    return error;
}

FuncStackErr_t FuncStackPush(FuncStack_t *stk, FuncStackElement_t value, int line)
{
    assert(stk);

    #ifdef DEBUGFUNC
        FuncStackErr_t error = VERIFY(stk);
        CHECKFUNCERROR(error);
    #else
        FuncStackErr_t error = {};
    #endif

    stk->size++;
    CheckSize(stk);

    stk->data[stk->size + stk->flag] = value;

    fprintf(Funcstk_log, "line: %d pushed value = " TYPE_ELEM "\n", line, stk->data[stk->size + stk->flag].name);
    INFO

    #ifdef DEBUGFUNC
        stk->hash = CalcHASHFunc(stk);
        error = VERIFY(stk);
    #endif

    return error;
}

FuncStackElement_t FuncStackPop(FuncStack_t *stk, FuncStackErr_t *error, int line)
{
    assert(stk);
    assert(error);
    
    #ifdef DEBUGFUNC
        *error = VERIFY(stk);
        CHECKFUNCERROR(error);
    #else
        *error = {};
    #endif

    FuncStackElement_t last_input = stk->data[stk->size + stk->flag];

    if (stk->size > 0)
    {
        #ifdef DEBUGFUNC
            stk->data[stk->size + stk->flag] = POISON;
        #else
            //stk->data[stk->size + stk->flag] = 0;
        #endif

        stk->size--;

        #ifdef DEBUGFUNC
            stk->hash = CalcHASHFunc(stk);
        #endif
    }

    fprintf(Funcstk_log, "line: %d popped value =" TYPE_ELEM "\n", line,  last_input.name);

    #ifdef DEBUGFUNC
        else
        {
            fprintf(Funcstk_log, "can't pop: empty Funcstack\n");
            error.code = SIZELIMIT;
            last_input = 0;
            *error = FuncStackOk(stk, *error, line);
            return last_input;
        }

        *error = VERIFY(stk);
    #endif

    NEWLINE
    INFO 

    return last_input;
}

FuncStackErr_t FuncStackDestroy(FuncStack_t *stk, int line)
{
    assert(stk);
    
    #ifdef DEBUGFUNC
        FuncStackErr_t error = VERIFY(stk);
        CHECKFUNCERROR(error);

    #else
        FuncStackErr_t error = {};
    #endif

    NEWLINE
    fprintf(Funcstk_log, "info about Funcstack before death:\n");
    INFO

    free(stk->data);
    fclose(Funcstk_log);

    return error;
}

FuncStackErr_t FuncStackVerify(ONDEBUGFUNCARGS(FuncStack_t *stk, int line))
{  
    
    FuncStackErr_t err = {};
    
    #ifdef DEBUGFUNC
        assert(stk);
        err.line = line;
        err.type = NOERROR;

        if (stk <= NULL)
        {
            err.code |= NULLSTKPTR;
            printf("stkptr err.code = %d\n", err.code);
        }
        #ifdef CANARY_DEBUGFUNC
            if (stk->canaryleft != CANARY)
            {
                err.code |= STRUCTATTACKLEFT;
                printf("left err.code = %d\n", err.code);
                err = FuncStackOk(stk, err, line);
                return err;
            }
            if (stk->canaryright != CANARY)
            {
                err.code |= STRUCTATTACKRIGHT; 
                printf("right err.code = %d\n", err.code);
                err = FuncStackOk(stk, err, line);
                return err; 
            }
        #endif
        if (stk->data <= NULL)
        {
            err.code |= NULLDATAPTR;
            printf("dataptr err.code = %d\n", err.code);
            err = FuncStackOk(stk, err, line);
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
                    fprintf(Funcstk_log, "FuncStack POISONing from %ld position\n", i); 
                    break;
                }
            }
            if (stk->hash != CalcHASHFunc(stk))
            {
                err.code |= HASHTRASH;
            }
            if ( stk->size > (stk->capacity CANDEBUGFUNC(-2)))
            {
                err.code |= SIZELIMIT;
            }
        }  
          
    #endif

    #ifdef CANARY_DEBUGFUNC
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

    ONDEBUGFUNC(err = FuncStackOk(stk, err, line));
    
    return err;
}

FuncStackErr_t FuncStackDump(FuncStack_t *stk, int line, const char *filename, const char *stkname)
{
    assert(stk);
    
    #ifdef DEBUGFUNC
        assert(filename);
        assert(stkname);
        FuncStackErr_t error = FuncStackVerify(stk, line);
        CHECKFUNCERROR(error);
    #else
        FuncStackErr_t error = {};
    #endif

    NEWLINE
    fprintf(Funcstk_log, "Funcstack name: %s\nFuncStackDump called from %s: %d\n", stkname, filename, line);
    
    if (error.type != ERRORPOINT)
    {
        INFO
        NEWLINE

        for (Ssize_t index = 0; index < stk->capacity; index++)
        {
            #ifdef DEBUGFUNC
                if (stk->data[index] == POISON) 
                {
                    fprintf(Funcstk_log, "*[%ld] = %d POISON\n", index, stk->data[index]);
                }
                else if (stk->data[index] == CANARY)
                {
                    fprintf(Funcstk_log, "*[%ld] = %d CANARY\n", index, stk->data[index]);
                } 
                else
                {
                    fprintf(Funcstk_log, "[%ld] = " TYPE_ELEM "\n", index, stk->data[index]);
                }
            #else
                if (index == stk->size) break;

                fprintf(Funcstk_log, "[%ld] = " TYPE_ELEM "\n", index, stk->data[index].name);
            #endif    
        }
    }

    ONDEBUGFUNC(error = FuncStackVerify(stk, line));

    return error;
}

Ssize_t CalcHASHFunc(ONDEBUGFUNCARGS(FuncStack_t *stk))
{   
    #ifdef DEBUGFUNC
        assert(stk);

        Ssize_t hash = stk->capacity + stk->size CANDEBUGFUNC(+ stk->canaryleft + stk->canaryright);

        
        for (Ssize_t i = 0; i < stk->capacity; i++)
        {
            ONDEBUGFUNC(hash += stk->data[i] * (i + 1));
        }

        return hash;
    #else
        return 0;
    #endif
}    

void CheckSize(FuncStack_t *stk)
{
    assert(stk);

    Ssize_t last_capacity = stk->capacity;

    if (stk->size >= (stk->capacity CANDEBUGFUNC(-2)))
    {
        stk->capacity *= 2;
        stk->data = (FuncStackElement_t*) realloc(stk->data, (size_t) stk->capacity * sizeof(FuncStackElement_t));

        assert(stk->data);

            for (Ssize_t i = last_capacity CANDEBUGFUNC(-1); i < stk->capacity - 1; i++)
            {
                ONDEBUGFUNC(stk->data[i] = POISON);
                ONDEBUGFUNC(stk->data[i] = NULL);
            }   

            fprintf(Funcstk_log, "succesful reallocation\n"); 
        
            
        CANDEBUGFUNC(stk->data[stk->capacity - 1] = CANARY;)
        ONDEBUGFUNC(stk->hash = CalcHASHFunc(stk);)
    }
}

FuncStackErr_t AllocationStk(FuncStack_t *stk)
{
    assert(stk);
    
    FuncStackErr_t err = {};
    FuncStackElement_t *alloc_ptr = (FuncStackElement_t*) calloc((size_t)stk->capacity, sizeof(FuncStackElement_t));

    #ifdef DEBUGFUNC
        if (alloc_ptr == NULL)
        {
            fprintf(Funcstk_log, "allocation error\n"); 
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

#define PRINT_LOG_MSG(msg) fprintf(Funcstk_log, "line: %d Error: %s\n", line, msg)

FuncStackErr_t FuncStackOk(FuncStack_t *stk, FuncStackErr_t err, int line)
{
    assert(stk);

    if ((err.code & NULLSTKPTR))
        PRINT_LOG_MSG("FuncStack pointer = NULL");
    if (err.code & NULLDATAPTR)
        PRINT_LOG_MSG("Data pointer = NULL");   
    if (err.code & NEGATIVECAPACITY)
        PRINT_LOG_MSG("Capacity too small!");
    if (err.code & STKATTACKLEFT)
        PRINT_LOG_MSG("FuncStack attack from the left");
    if (err.code & STKATTACKRIGHT)
        PRINT_LOG_MSG("FuncStack attack from the right");
    if (err.code & STRUCTATTACKRIGHT)
        PRINT_LOG_MSG("Struct attack from the right");
    if (err.code & STRUCTATTACKLEFT)
        PRINT_LOG_MSG("Struct attack from the left");
    if (err.code & SIZELIMIT)
        PRINT_LOG_MSG("Warning: Size limit errors");      
    if (err.code & POISONING)
        PRINT_LOG_MSG("Warning: FuncStack poisoning");
    if (err.code & HASHTRASH)
        PRINT_LOG_MSG("Error: hash violation"); 
    
    err.type = ErrorType(err);

    return err;
}


int ErrorType(FuncStackErr_t err)
{
    if (err.code == 0)
    {
        return NOERROR;
    }
    else if (err.code < ERRORS_END)
    {
        return ERRORPOINT;
    }

    return WARNINGPOINT;
}