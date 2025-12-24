#include "treefuncs.h"

Node_t *NodeCtor()
{
    Node_t *node = (Node_t*) calloc(ONENODE, sizeof(Node_t));
    assert(node);

    SetLeft(node, NULL);
    SetRight(node, NULL);
    SetParent(node, NULL);
    SetType(node, TYPE_ERR);
    
    return node;
}

Node_t *CtorOperation(Operators oper)
{
    Node_t *node = NodeCtor();

    SetType(node, TYPE_OP);
    SetOper(node, oper);

    return node;
}

Node_t *CtorFunc(int func)
{
    Node_t *node = NodeCtor();

    SetType(node, TYPE_UFUNC);
    SetFunc(node, func);

    return node;
}

Node_t *CtorVariable(int var)
{
    Node_t *node = NodeCtor();

    SetType(node, TYPE_VAR);
    SetVar(node, var);

    return node;
}

Node_t *CtorNumber(TreeElem_t number)
{
    Node_t *node = NodeCtor();

    SetType(node, TYPE_NUM);
    SetNum(node, number);

    return node;
}

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
 
Node_t *RemoveFict(Node_t *node, int *change_par)
{
    assert(node);
    assert(change_par);

    Node_t *fix_node = node;

    if ((GetLeft(node) && (IsNum(GetLeft(node), 1) || IsNum(GetLeft(node), 0))) || (GetRight(node) && (IsNum(GetRight(node), 1) || IsNum(GetRight(node), 0))) )                                                                                                         
        fix_node = RemoveFictNode(node, change_par);                    

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

#define _LOneRemL_(val)     if (IsNum(GetLeft(node), 0))\
                            {                           \
                                _RemoveLeft_;           \
                            }

#define _LOneRemR_(val)     if (IsNum(GetLeft(node), 0))\
                            {                           \
                                _RemoveRight_;          \
                            }

#define _ROneRemR_(val)     if (IsNum(GetRight(node), 0))\
                            {                            \
                                _RemoveRight_;           \
                            }

#define _ROneRemL_(val)     if (IsNum(GetRight(node), 0))\
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
            
        case OP_POW:
            if (IsNum(GetRight(node), 0))
            {
                SetNum(GetRight(node), 1);
                _RemoveLeft_;
            }

             _LOneRemR_(1);

             _ROneRemR_(1);

            break;

        default:
            break;
    }

    return fix_node;
}

Node_t *NodeCpy(const Node_t *node)
{
    assert(node);

    Node_t *cnode = NULL;

    switch (GetType(node))
    {
        case TYPE_OP:
            cnode = CTOR_OP(GetOper(node));
            break;

        case TYPE_VAR:
            cnode = CTOR_VAR(GetVar(node));
            break;

        case TYPE_NUM:
            cnode = CTOR_NUM(GetNum(node));
            break;

        case TYPE_UFUNC:
            cnode = CTOR_FUNC(GetFunc(node));

        case TYPE_ERR:
            break;

        default:
            break;
    }

    if (GetLeft(node))
    {
        SetLeft(cnode, NodeCpy(GetLeft(node)));
        SetParent(GetLeft(cnode), cnode);
    }

    if (GetRight(node))
    {
        SetRight(cnode, NodeCpy(GetRight(node)));
        SetParent(GetRight(cnode), cnode);
    }

    return cnode;
}

Node_t *NewNode(Node_t *node, Node_t *left_node, Node_t *right_node)
{
    assert(node);

    SetLeft(node, left_node);

    if (left_node)
    {
        SetParent(left_node, node);
    }

    SetRight(node, right_node);

    if (right_node)
    {
        SetParent(right_node, node);
    }

    return node;
}

void NodeDtor(Node_t *node)
{
    if (node == NULL)
        return;

    NodeDtor(GetLeft(node));
    
    NodeDtor(GetRight(node));

    free(node);
}

bool IsZero(double value)
{
    if (fabs(value) < EPSILON)
        return true;

    else
        return false;
}

bool IsNumType(const Node_t *node)
{
    assert(node);

    if (GetType(node) == TYPE_NUM)
        return true;

    else
        return false;
}

bool IsVarType(const Node_t *node)
{
    assert(node);

    if (GetType(node) == TYPE_VAR)
        return true;

    else
        return false;
}

bool IsOperType(const Node_t *node)
{
    assert(node);

    if (GetType(node) == TYPE_OP)
        return true;

    else
        return false;
}

bool IsFuncType(const Node_t *node)
{
    assert(node);

    if (GetType(node) == TYPE_UFUNC)
        return true;

    else
        return false;
}

bool IsNum(const Node_t *node, TreeElem_t value)
{
    assert(node);

    if (IsNumType(node) && IsZero(GetNum(node) - value))
        return true;

    else
        return false;
}

bool IsVar(const Node_t *node, int var)
{
    assert(node);

    if (IsVarType(node) && GetVar(node) == var)
        return true;
    else
        return false;
}

bool IsOper(const Node_t *node, Operators oper)
{
    assert(node);

    if (IsOperType(node) && GetOper(node) == oper)
        return true;

    else
        return false;
}

bool IsPrefix(const Node_t *node)
{
    assert(node);

    if (IsOperType(node) && Oper_table[GetOper(node)].order_type == PREFIX_ORD)
        return true;
    else
        return false;
}

bool IsInfix(const Node_t *node)
{
    assert(node);

    if (IsOperType(node) && Oper_table[GetOper(node)].order_type == INFIX_ORD)
        return true;
    else
        return false;
}

bool IsConditionalOp(const Node_t *node)
{
    assert(node);

    if (IsOper(node, OP_IF) || IsOper(node, OP_ELSE) || IsOper(node, OP_WHILE) || IsOper(node, OP_FOR))
        return true;
    else
        return false;
}

bool IsInt(TreeElem_t value)
{
    double fract = 0;
    double int_par = 0;
    fract = modf(value, &int_par);

    if (IsZero(fract))
        return true;
    else
        return false;
}

#define IsNullBranch(node, word) (node == NULL) ? "nil" : word

void PrintNode(const Node_t *node, FILE *graph, FILE *tree_file)
{
    assert(node);
    assert(graph);
    assert(tree_file);

    fprintf(tree_file, "( ");

    fprintf(graph, "\ts%p [shape=record, ", node);

    
    switch (GetType(node))
    {
        case TYPE_OP:
            fprintf(graph, "fillcolor=\"#b4ff05ff\", label = \"{%p| type = OP | <f0>key word: %s | std word: %s ", GetParent(node), Oper_table[GetOper(node)].name, Oper_table[GetOper(node)].std_name);
            fprintf(tree_file, "\"%s\" ", Oper_table[GetOper(node)].std_name);
            break;
        case TYPE_VAR:
            fprintf(graph, "fillcolor=\"#0091a1ff\", label = \"{%p| type = VAR | <f0>val = %s (%.3lg) ", GetParent(node), Var_table.data[GetVar(node)].name, Var_table.data[GetVar(node)].value);
            fprintf(tree_file, "\"%s\" ", Var_table.data[GetVar(node)].name);
            break;
        case TYPE_NUM:
            fprintf(graph, "fillcolor=\"#fd0101ff\", label = \"{%p| type = NUM | <f0>val =  %.3lg ", GetParent(node), GetNum(node));
            fprintf(tree_file, "\"%lg\" ", GetNum(node));
            break;
        case TYPE_UFUNC:
            fprintf(graph, "fillcolor=\"#b94c84ff\", label = \"{%p| type = FUNC | <f0>val =  %s ", GetParent(node), Func_table.data[GetFunc(node)].name);
            fprintf(tree_file, "\"%s\" ", Func_table.data[GetFunc(node)].name);
            break;
        case TYPE_ERR:
            fprintf(graph, "label = \"{%p| type = ERR_NODE | <f0>val =  ... ", GetParent(node));
        default:
            break;
    }

    fprintf(tree_file, "%s %s", IsNullBranch(GetLeft(node), ""), IsNullBranch(GetRight(node), ""));
    fprintf(graph, "| {%p | %p}}\"];\n", GetLeft(node), GetRight(node));
    
    if(GetLeft(node))
    {
        fprintf(graph, "\ts%p -> s%p [color = blue]\n", node, GetLeft(node));
        PrintNode(GetLeft(node), graph, tree_file);
    }

    if(GetRight(node))
    {
        fprintf(graph, "\ts%p -> s%p [color = red]\n", node, GetRight(node));
        PrintNode(GetRight(node), graph, tree_file);
    }

    fprintf(tree_file, " )");
}

void TreeDump(const Node_t *node, const char *output_tree, int line)
{
    assert(node);
    assert(output_tree);

    FILE *tree_file = fopen(output_tree, "w");
    assert(tree_file);

    FILE *graph = fopen("graph.txt", "w");
    assert(graph);

    fprintf(Logfile, "<pre>\n\t<h3>\n\t\tDUMP from %s:%d <font color = red>Tree </font>\n\t</h3>\n", __FILE__, line);
    
    fprintf(graph, "digraph structs\n{\n\tnode[style=filled];\n\trankdir = TB;\n");
    PrintNode(node, graph, tree_file);
    fprintf(graph, "}");

    fclose(graph);
    fclose(tree_file);
    
    char dot_cmd[REASONSTRSIZE] = "";
    static int png_counter = 0;

    png_counter++;

    sprintf(dot_cmd, "dot \"graph.txt\" -T png -o treepng/graph%d.png", png_counter);

    fprintf(Logfile, "\n\n\tImage:\n\t<img src = treepng/graph%d.png heigth = 1000px width = 1000px>\n</pre>\n", png_counter);
    system(dot_cmd);
}