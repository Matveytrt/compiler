#include "generalheaders/treefuncs.h"

Node_t *NodeCtor()
{
    Node_t *node = (Node_t*) calloc(1, sizeof(Node_t));
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

const char *GetInvLogOp(const Node_t *node)
{
    assert(node);
    
    switch (GetOper(node))
    {
    case OP_EQ:
        return "JNE";
        break;

    case OP_NEQ:
        return "JE";
        break;

    case OP_ABOVE_EQ:
        return "JB";
        break;
    
    case OP_BELOW_EQ:
        return "JA";
        break;
    
    case OP_BELOW:
        return "JAE";
        break;

    case OP_ABOVE:
        return "JBE";
        break;
    
    default:
        break;
    }

    return NULL;
}

bool IsZero(double value)
{
    if (fabs(value) < EPSILON)
    return true;
    
    else
    return false;
}

bool IsLogicOp(const Node_t *node)
{
    assert(node);

    if (IsOper(node, OP_ABOVE) || IsOper(node, OP_ABOVE_EQ) || IsOper(node, OP_BELOW) || IsOper(node, OP_BELOW_EQ) || IsOper(node, OP_EQ) || IsOper(node, OP_NEQ))
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

bool IsPostix(const Node_t *node)
{
    assert(node);
    
    if (IsOperType(node) && Oper_table[GetOper(node)].order_type == POSTFIX_ORD)
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
            fprintf(tree_file, "\"OP %s\" ", Oper_table[GetOper(node)].std_name);
            break;
        case TYPE_VAR:
            fprintf(graph, "fillcolor=\"#0091a1ff\", label = \"{%p| type = VAR | <f0>val = %s (%d) | table_idx = %d ", GetParent(node), Var_table.data[GetVar(node)].name, Var_table.data[GetVar(node)].value, GetVar(node));
            fprintf(tree_file, "\"VAR %s\" ", Var_table.data[GetVar(node)].name);
            break;
        case TYPE_NUM:
            fprintf(graph, "fillcolor=\"#fd0101ff\", label = \"{%p| type = NUM | <f0>val =  %d ", GetParent(node), GetNum(node));
            fprintf(tree_file, "\"NUM %d\" ", GetNum(node));
            break;
        case TYPE_UFUNC:
            fprintf(graph, "fillcolor=\"#b94c84ff\", label = \"{%p| type = FUNC | <f0>val =  %s ", GetParent(node), Func_table.data[GetFunc(node)].name);
            fprintf(tree_file, "\"FUNC %s\" ", Func_table.data[GetFunc(node)].name);
            break;
        case TYPE_ERR:
            fprintf(graph, "label = \"{%p| type = ERR_NODE | <f0>val =  ... ", GetParent(node));
        default:
            break;
    }

    fprintf(graph, "| {%p | %p}}\"];\n", GetLeft(node), GetRight(node));
    
    if(GetLeft(node))
    {
        fprintf(graph, "\ts%p -> s%p [color = blue]\n", node, GetLeft(node));
        PrintNode(GetLeft(node), graph, tree_file);
    }
    
    fprintf(tree_file, "%s %s", IsNullBranch(GetLeft(node), ""), IsNullBranch(GetRight(node), ""));

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

void PrintNodeInfo(const Node_t *node, FILE *file)
{
    assert(node);
    assert(file);

    switch (GetType(node))
    {
        case TYPE_OP:
            fprintf(file, "OP - %s\n", Oper_table[GetOper(node)].std_name);
            break;
        case TYPE_VAR:
            fprintf(file, "VAR - %s, table_idx [%d]\n", Var_table.data[GetVar(node)].name, GetVar(node));
            break;
        case TYPE_NUM:
            fprintf(file, "NUM = %d\n", GetNum(node));
            break;
        case TYPE_UFUNC:
            fprintf(file, "FUNC - %s st_idx = %d, end_idx = %d\n", Func_table.data[GetFunc(node)].name, Func_table.data[GetFunc(node)].start_idx, Func_table.data[GetFunc(node)].end_idx);
            break;
        case TYPE_ERR:
            break;
        default:
            break;
    }
}

int SearchFuncName(const char *func)
{
    assert(func);

    for (int index = 0; index < Func_table.size; index++)
    {
        if (strcmp(func, Func_table.data[index].name) == 0)
            return index;
    }

    return NOT_FOUND;
}

int SearchVarName(const char *var, int start_idx)
{
    assert(var);

    for (int index = start_idx; index < Var_table.size; index++)
    {
        if (strcmp(var, Var_table.data[index].name) == 0)
            return index;
    }

    return NOT_FOUND;
}

void VarTableDtor()
{
    for(int index = 0; index < Var_table.size; index++)
    {
        free(Var_table.data[index].name);
    }
    DTOR_VAR();
}

void FuncTableDtor()
{
    for(int index = 0; index < Func_table.size; index++)
    {
        free(Func_table.data[index].name);
    }
    DTOR_FUNC();
}