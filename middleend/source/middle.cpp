#include "headers/middle.h"

#define _RemoveLeft_                                              \
                            fix_node = GetRight(node);            \
                                                                  \
                            SetParent(fix_node, GetParent(node)); \
                            SetRight(node, NULL);                 \
                            NodeDtor(node);                       \
                            (*change_par)++;                      \
                            return fix_node;
                            

#define _RemoveRight_                                             \
                            fix_node = GetLeft(node);             \
                                                                  \
                            SetParent(fix_node, GetParent(node)); \
                            SetLeft(node, NULL);                  \
                            NodeDtor(node);                       \
                            (*change_par)++;                      \
                            return fix_node;
 
Node_t *OptimizeTree(Node_t *node, int dump_flag)
{
    assert(node);

    int change_par = 0;
    int past_change_par = 0;

    while(1)
    {
        node = CalcConstNode(node, &change_par, dump_flag);
        node = RemoveFictElems(node, &change_par, dump_flag);
        if(change_par == past_change_par)
            break;
        past_change_par = change_par;
    }

    return node;
}

Node_t *RemoveFictElems(Node_t *node, int *change_par, int dump_flag)
{
    #ifdef DEBUG
        assert(node);
        assert(change_par);
    #endif
    
    if(IsOperType(node))
    {
        if(GetLeft(node))
            SetLeft(node, RemoveFictElems(GetLeft(node), change_par, dump_flag));

        else
            return node;

        if(GetRight(node))
            SetRight(node, RemoveFictElems(GetRight(node), change_par, dump_flag));

        node = RemoveFict(node, change_par);    
    }
    
    return node;
}

Node_t *RemoveFict(Node_t *node, int *change_par)
{
    assert(node);
    assert(change_par);

    Node_t *fix_node = node;

    if ( (GetLeft(node) && (IsNum(GetLeft(node), 1) || IsNum(GetLeft(node), 0))) || (GetRight(node) && (IsNum(GetRight(node), 1) || IsNum(GetRight(node), 0))) )
    {                                                                                                         
        fix_node = RemoveFictNode(node, change_par);                    
    }

    return fix_node;                                                
} 

#define OPERFUNC(val1, val2) Oper_table[GetOper(node)].ptr_func(val1, val2)

Node_t *CalcConstNode(Node_t *node, int *change_par, int dump_flag)
{
    assert(node);
    
    if(IsOperType(node) || IsFuncType(node))
    {

        if(GetLeft(node))
            SetLeft(node, CalcConstNode(GetLeft(node), change_par, dump_flag));

        else
            return node;

        if(GetRight(node))
            SetRight(node, CalcConstNode(GetRight(node), change_par, dump_flag));

        else  
        {
            return node;
        }  
                
        printf("myau\n");
        node = CalcNode(node, change_par);
    }
    
    return node;
}

Node_t *CalcNode(Node_t *node, int *change_par)
{
    assert(node);

    Node_t *fix_node = node;
    TreeElem_t val = 0;
    TreeDump(node, "out.txt", __LINE__);

    if(IsNumType(GetLeft(node)) && IsNumType(GetRight(node)))
    {
        printf("gaf\n");
        switch (GetOper(node))
        {
        case OP_ADD:
            val = GetNum(GetLeft(node)) + GetNum(GetRight(node));
            fix_node = CTOR_NUM(val);
            break;
        case OP_SUB:
            val = GetNum(GetLeft(node)) - GetNum(GetRight(node));
            printf("sub val = %d\n", val);
            fix_node = CTOR_NUM(val);
            break;
        case OP_MUL:
            val = GetNum(GetLeft(node)) * GetNum(GetRight(node));
            fix_node = CTOR_NUM(val);
            break;
        case OP_DIV:
            val = GetNum(GetLeft(node)) / GetNum(GetRight(node));
            fix_node = CTOR_NUM(val);
            break;
        default:
            break;
        }

        SetParent(fix_node, GetParent(node));
        NodeDtor(node);
        (*change_par)++;
    }
    
    return fix_node;
}

#define _LZeroRemL_(val)    if (IsNum(GetLeft(node), 0))\
                            {                           \
                                _RemoveLeft_;           \
                            }

#define _LZeroRemR_(val)    if (IsNum(GetLeft(node), 0))\
                            {                           \
                                _RemoveRight_;          \
                            }

#define _RZeroRemR_(val)    if (IsNum(GetRight(node), 0))\
                            {                            \
                                _RemoveRight_;           \
                            }

#define _RZeroRemL_(val)    if (IsNum(GetRight(node), 0))\
                            {                            \
                                _RemoveLeft_;            \
                            }

#define _LOneRemL_(val)     if (IsNum(GetLeft(node), 1))\
                            {                           \
                                _RemoveLeft_;           \
                            }

#define _LOneRemR_(val)     if (IsNum(GetLeft(node), 1))\
                            {                           \
                                _RemoveRight_;          \
                            }

#define _ROneRemR_(val)     if (IsNum(GetRight(node), 1))\
                            {                            \
                                _RemoveRight_;           \
                            }

#define _ROneRemL_(val)     if (IsNum(GetRight(node), 1))\
                            {                            \
                                _RemoveLeft_;            \
                            }

Node_t *RemoveFictNode(Node_t *node, int *change_par)
{
    assert(node);
    assert(change_par);

    Node_t *fix_node = node;

    switch (GetOper(node))
    {
        case OP_ADD:
            _LZeroRemL_(0);
            _RZeroRemR_(0);

            break;

        case OP_SUB:
            _RZeroRemR_(0);
            
            break;

        case OP_MUL:
            _LZeroRemR_(0);
            _ROneRemR_(1);
            _RZeroRemL_(0);
            _LOneRemL_(1);
            
            break;

        case OP_DIV:
            _LZeroRemR_(0);
            _ROneRemR_(1);
            
            break;

        case OP_SQRT:
            _LZeroRemR_(0);
            _LOneRemR_(1);

            break;

        default:
            break;
    }

    return fix_node;
}