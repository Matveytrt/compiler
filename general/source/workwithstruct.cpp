#include "../generalheaders/workwithstruct.h"

const char *GetVarScopeName  (int scope)
{
    switch (scope) 
    {
        case GLOBAL:
            return "GLOBAL";
        case ARGUMENT:
            return "ARGUMENT";
        case LOCAL:
            return "LOCAL";
        default:
            break;
    }

    return "error_type";
}

void SetData(Node_t *node, Value_t new_data)
{
    assert(node);

    switch (node->type)
    {
        case TYPE_OP:
            node->data.oper = new_data.oper;
            break;
        case TYPE_VAR:
            node->data.var = new_data.var;
            break;
        case TYPE_NUM:
            node->data.num = new_data.num;
            break;
        case TYPE_UFUNC:
            node->data.func = new_data.func;
            break;
        case TYPE_ERR:
            break;
        default:
            printf("ErrorType\n");
            break;
    }
}