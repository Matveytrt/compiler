#include "../generalheaders/varstack.h"

#define TYPE_ELEM       "%s"

#define ERROR        fprintf(Varstk_log, "error: %d line: %d\n", err.code, err.line);
#define INFO         fprintf(Varstk_log, "%s:%d Varstack size = %ld, capacity = %ld\n", __func__, line, stk->size, stk->capacity);
#define NEWLINE      fprintf(Varstk_log, "\n");
#define VERIFY(stk)  VarStackVerify(stk, line)
#define CANARY       0xEDAA
#define ERRORPOINT   0xBADDD
#define WARNINGPOINT 0xBED
#define NOERROR      0x0
#define STARTSIZE    10
#define STRSIZE      200
#define CHECKFUNCERROR(error)   if (error.type == ERRORPOINT)                                         \
                                {                                                                     \
                                fprintf(Varstk_log, "err.code = %d, line: %d\n", error.code, error.line);\
                                return error;                                                         \
                                }

enum var_errors 
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

FILE *Varstk_log = NULL;

VarStackErr_t VarStackVerify(ONDEBUGVARARGS(VarStack_t *stk, int line));  
VarStackErr_t AllocationStk(VarStack_t *stk);
VarStackErr_t VarStackOk(VarStack_t *stk, VarStackErr_t err, int line);
int ErrorType(VarStackErr_t err);
Ssize_t CalcHASHVar(ONDEBUGVARARGS(VarStack_t *stk));
void CheckSize(VarStack_t *stk); 

VarStackErr_t VarStackInit(VarStack_t *stk, int capacity, int line)
{ 
    assert(stk);

    VarStackErr_t error ={};
    stk->size = 0;

    Varstk_log = fopen("general/stklogs/varstk.log", "w");
    assert(Varstk_log);

    #ifdef DEBUGVAR
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

    #ifdef CANARY_DEBUGVAR
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
    
    #ifdef DEBUGVAR
        INFO
        stk->hash = CalcHASHVar(stk);
        error = VERIFY(stk);
        if (error.code == NOERROR)
        {
            fprintf(Varstk_log, "Initialisation succses\n");
        }
    #else
        INFO
        fprintf(Varstk_log, "Initialisation succses\n");
    #endif

    return error;
}

VarStackErr_t VarStackPush(VarStack_t *stk, VarStackElement_t value, int line)
{
    assert(stk);

    #ifdef DEBUGVAR
        VarStackErr_t error = VERIFY(stk);
        CHECKFUNCERROR(error);
    #else
        VarStackErr_t error = {};
    #endif

    stk->size++;
    CheckSize(stk);

    stk->data[stk->size + stk->flag] = value;

    fprintf(Varstk_log, "line: %d pushed value = " TYPE_ELEM "\n", line, stk->data[stk->size + stk->flag].name);
    INFO

    #ifdef DEBUGVAR
        stk->hash = CalcHASHVar(stk);
        error = VERIFY(stk);
    #endif

    return error;
}

VarStackElement_t VarStackPop(VarStack_t *stk, VarStackErr_t *error, int line)
{
    assert(stk);
    assert(error);
    
    #ifdef DEBUGVAR
        *error = VERIFY(stk);
        CHECKFUNCERROR(error);
    #else
        *error = {};
    #endif

    VarStackElement_t last_input = stk->data[stk->size + stk->flag];

    if (stk->size > 0)
    {
        #ifdef DEBUGVAR
            stk->data[stk->size + stk->flag] = POISON;
        #else
            //stk->data[stk->size + stk->flag] = 0;
        #endif

        stk->size--;

        #ifdef DEBUGVAR
            stk->hash = CalcHASHVar(stk);
        #endif
    }

    fprintf(Varstk_log, "line: %d popped value =" TYPE_ELEM "\n", line,  last_input.name);

    #ifdef DEBUGVAR
        else
        {
            fprintf(Varstk_log, "can't pop: empty Varstack\n");
            error.code = SIZELIMIT;
            last_input = 0;
            *error = VarStackOk(stk, *error, line);
            return last_input;
        }

        *error = VERIFY(stk);
    #endif

    NEWLINE
    INFO 

    return last_input;
}

VarStackErr_t VarStackDestroy(VarStack_t *stk, int line)
{
    assert(stk);
    
    #ifdef DEBUGVAR
        VarStackErr_t error = VERIFY(stk);
        CHECKFUNCERROR(error);

    #else
        VarStackErr_t error = {};
    #endif

    NEWLINE
    fprintf(Varstk_log, "info about Varstack before death:\n");
    INFO

    free(stk->data);
    fclose(Varstk_log);

    return error;
}

VarStackErr_t VarStackVerify(ONDEBUGVARARGS(VarStack_t *stk, int line))
{  
    
    VarStackErr_t err = {};
    
    #ifdef DEBUGVAR
        assert(stk);
        err.line = line;
        err.type = NOERROR;

        if (stk <= NULL)
        {
            err.code |= NULLSTKPTR;
            printf("stkptr err.code = %d\n", err.code);
        }
        #ifdef CANARY_DEBUGVAR
            if (stk->canaryleft != CANARY)
            {
                err.code |= STRUCTATTACKLEFT;
                printf("left err.code = %d\n", err.code);
                err = VarStackOk(stk, err, line);
                return err;
            }
            if (stk->canaryright != CANARY)
            {
                err.code |= STRUCTATTACKRIGHT; 
                printf("right err.code = %d\n", err.code);
                err = VarStackOk(stk, err, line);
                return err; 
            }
        #endif
        if (stk->data <= NULL)
        {
            err.code |= NULLDATAPTR;
            printf("dataptr err.code = %d\n", err.code);
            err = VarStackOk(stk, err, line);
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
                    fprintf(Varstk_log, "VarStack POISONing from %ld position\n", i); 
                    break;
                }
            }
            if (stk->hash != CalcHASHVar(stk))
            {
                err.code |= HASHTRASH;
            }
            if ( stk->size > (stk->capacity CANDEBUGVAR(-2)))
            {
                err.code |= SIZELIMIT;
            }
        }  
          
    #endif

    #ifdef CANARY_DEBUGVAR
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

    ONDEBUGVAR(err = VarStackOk(stk, err, line));
    
    return err;
}

VarStackErr_t VarStackDump(VarStack_t *stk, int line, const char *filename, const char *stkname)
{
    assert(stk);
    
    #ifdef DEBUGVAR
        assert(filename);
        assert(stkname);
        VarStackErr_t error = VarStackVerify(stk, line);
        CHECKFUNCERROR(error);
    #else
        VarStackErr_t error = {};
    #endif

    NEWLINE
    fprintf(Varstk_log, "Varstack name: %s\nVarStackDump called from %s: %d\n", stkname, filename, line);
    
    if (error.type != ERRORPOINT)
    {
        INFO
        NEWLINE

        for (Ssize_t index = 0; index < stk->capacity; index++)
        {
            #ifdef DEBUGVAR
                if (stk->data[index] == POISON) 
                {
                    fprintf(Varstk_log, "*[%ld] = %d POISON\n", index, stk->data[index]);
                }
                else if (stk->data[index] == CANARY)
                {
                    fprintf(Varstk_log, "*[%ld] = %d CANARY\n", index, stk->data[index]);
                } 
                else
                {
                    fprintf(Varstk_log, "[%ld] = " TYPE_ELEM "\n", index, stk->data[index]);
                }
            #else
                if (index == stk->size) break;

                fprintf(Varstk_log, "[%ld] = " TYPE_ELEM "%d" "\n", index, stk->data[index].name, stk->data[index].value);
            #endif    
        }
    }

    ONDEBUGVAR(error = VarStackVerify(stk, line));

    return error;
}

Ssize_t CalcHASHVar(ONDEBUGVARARGS(VarStack_t *stk))
{   
    #ifdef DEBUGVAR
        assert(stk);

        Ssize_t hash = stk->capacity + stk->size CANDEBUGVAR(+ stk->canaryleft + stk->canaryright);

        
        for (Ssize_t i = 0; i < stk->capacity; i++)
        {
            ONDEBUGVAR(hash += stk->data[i] * (i + 1));
        }

        return hash;
    #else
        return 0;
    #endif
}    

void CheckSize(VarStack_t *stk)
{
    assert(stk);

    Ssize_t last_capacity = stk->capacity;

    if (stk->size >= (stk->capacity CANDEBUGVAR(-2)))
    {
        stk->capacity *= 2;
        stk->data = (VarStackElement_t*) realloc(stk->data, (size_t) stk->capacity * sizeof(VarStackElement_t));

        assert(stk->data);

            for (Ssize_t i = last_capacity CANDEBUGVAR(-1); i < stk->capacity - 1; i++)
            {
                ONDEBUGVAR(stk->data[i] = POISON);
                ONDEBUGVAR(stk->data[i] = NULL);
            }   

            fprintf(Varstk_log, "succesful reallocation\n"); 
        
            
        CANDEBUGVAR(stk->data[stk->capacity - 1] = CANARY;)
        ONDEBUGVAR(stk->hash = CalcHASHVar(stk);)
    }
}

VarStackErr_t AllocationStk(VarStack_t *stk)
{
    assert(stk);
    
    VarStackErr_t err = {};
    VarStackElement_t *alloc_ptr = (VarStackElement_t*) calloc((size_t)stk->capacity, sizeof(VarStackElement_t));

    #ifdef DEBUGVAR
        if (alloc_ptr == NULL)
        {
            fprintf(Varstk_log, "allocation error\n"); 
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

#define PRINT_LOG_MSG(msg) fprintf(Varstk_log, "line: %d Error: %s\n", line, msg)

VarStackErr_t VarStackOk(VarStack_t *stk, VarStackErr_t err, int line)
{
    assert(stk);

    if ((err.code & NULLSTKPTR))
        PRINT_LOG_MSG("VarStack pointer = NULL");
    if (err.code & NULLDATAPTR)
        PRINT_LOG_MSG("Data pointer = NULL");   
    if (err.code & NEGATIVECAPACITY)
        PRINT_LOG_MSG("Capacity too small!");
    if (err.code & STKATTACKLEFT)
        PRINT_LOG_MSG("VarStack attack from the left");
    if (err.code & STKATTACKRIGHT)
        PRINT_LOG_MSG("VarStack attack from the right");
    if (err.code & STRUCTATTACKRIGHT)
        PRINT_LOG_MSG("Struct attack from the right");
    if (err.code & STRUCTATTACKLEFT)
        PRINT_LOG_MSG("Struct attack from the left");
    if (err.code & SIZELIMIT)
        PRINT_LOG_MSG("Warning: Size limit errors");      
    if (err.code & POISONING)
        PRINT_LOG_MSG("Warning: VarStack poisoning");
    if (err.code & HASHTRASH)
        PRINT_LOG_MSG("Error: hash violation"); 
    
    err.type = ErrorType(err);

    return err;
}

int ErrorType(VarStackErr_t err)
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