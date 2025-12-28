#include "generalheaders/workwithstruct.h"

Operators GetOper(const Node_t *node)
{
    assert(node);

    return node->data.oper;
}

int GetVar(const Node_t *node)
{
    assert(node);

    return node->data.var;
}

int GetFunc(const Node_t *node)
{
    assert(node);

    return node->data.func;
}

TreeElem_t GetNum(const Node_t *node)
{
    assert(node);

    return node->data.num;
}

Node_t *GetLeft(const Node_t *node)
{
    assert(node);

    return node->left;
}

Node_t *GetRight(const Node_t *node)
{
    assert(node);

    return node->right;
}

Node_t *GetParent(const Node_t *node)
{
    assert(node);

    return node->parent;
}

Value_t GetData(const Node_t *node)
{
    assert(node);
    
    return node->data;
}

NodeType_t GetType(const Node_t *node)
{
    assert(node);
    
    return node->type;
}

void SetType(Node_t *node, NodeType_t type)
{
    assert(node);
    
    node->type = type;
}

void SetOper(Node_t *node, Operators oper)
{
    assert(node);

    node->data.oper = oper;
}

void SetVar(Node_t *node, int var)
{
    assert(node);

    node->data.var = var;
}

void SetNum(Node_t *node, TreeElem_t num)
{
    assert(node);

    node->data.num = num;
}

void SetFunc(Node_t *node, int func)
{
    assert(node);

    node->data.func = func;
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

void SetLeft(Node_t *node, Node_t *new_node)
{
    assert(node);

    node->left = new_node;
}

void SetRight(Node_t *node, Node_t *new_node)
{
    assert(node);

    node->right = new_node;
}

void SetParent(Node_t *node, Node_t *new_node)
{
    assert(node);

    node->parent = new_node;
}