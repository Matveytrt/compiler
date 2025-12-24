#include "stdio.h"
#include "stdlib.h"

#include "syntax.h"

#define _TOKEN_ stk->data[*stk_index]
#define _PREV_TOKEN_ stk->data[*stk_index - 1]
#define _NEXT_TOKEN_ stk->data[*stk_index + 1]
#define ReadInfo(info)                                                                                                    \
    fprintf(Logfile, "Я функция по имени %s called from line:%d\n" info "\n", __func__, __LINE__);
/*   fprintf(Logfile, "cur_pos:%c\ncur_buff_pos:<span style = \"background-color:#a0ffa0;\">%.*s</span>"                  \
                                              "<span style = \"background-color:#ffc0a0;\">%c</span>"                     \
                                              "<span style = \"background-color:#c0c0ff;\">%s</span>\n",                  \
                          **s, (int)((*s) - start_ptr), start_ptr, **s, (*s + 1));                                        \
    fprintf(Logfile, "\n\n\n");*/

Node_t *GetGeneral(const TokStack_t *stk)
{
    assert(stk);

    ReadInfo("Начинаю чтение корня");

    int stk_index = 0;

    Node_t *node = GetOperator(stk, &stk_index);
    Node_t *cur_node = node;

    while (!IsOper(stk->data[stk_index], OP_END))
    {
        Node_t *node_right = GetOperator(stk, &stk_index);
        cur_node = NewNode(cur_node, cur_node->left, node_right);
        cur_node = node_right;
    }
    
    ReadInfo("Чтение корня подходит к концу...");

    return node;
}

Node_t *GetOperator(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);

    Node_t *node = NULL;
    Node_t *node_left = NULL;

    if (IsVarType(_TOKEN_))
    {
        node_left = GetAssign(stk, stk_index);
    }

    else if (IsConditionalOp(_TOKEN_))
    {
        node_left = GetConditional(stk, stk_index);
    }

    else if (IsOper(_TOKEN_, OP_F_DCLR))
    {
        node_left = GetFuncDeclare(stk, stk_index);
    }

    else if (IsOper(_TOKEN_, OP_V_DCLR))
    {
        node_left = _TOKEN_;
        (*stk_index)++;
        Node_t *node_left_left = GetVariable(stk, stk_index);
        node_left = NewNode(node_left, node_left_left, NULL);
    }

    else if (IsOper(_TOKEN_, OPEN_SQ_BR))
    {
        (*stk_index)++;
        node = GetOperator(stk, stk_index);
        Node_t *cur_node = node;

        while (!IsOper(_TOKEN_, CLOSE_SQ_BR))
        {
            Node_t *node_right = GetOperator(stk, stk_index);
            cur_node = NewNode(cur_node, cur_node->left, node_right);
            cur_node = node_right;
        }

        (*stk_index)++;
        return node;
    }

    else if (IsOper(_TOKEN_, OP_RET) || IsOper(_TOKEN_, OP_BREAK))
    {
        node_left = _TOKEN_;
        (*stk_index)++;
        Node_t *node_left_left = GetExpression(stk, stk_index);
        node_left = NewNode(node_left, node_left_left, NULL);
    }

    else
    {
        node_left = GetExpression(stk, stk_index);
    }

    node = NewNode(_TOKEN_, node_left, NULL);
    (*stk_index)++;

    return node;
}

Node_t *GetConditional(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);
    
    if (!IsConditionalOp(_TOKEN_))
        return NULL;

    Node_t *node = _TOKEN_;
    Node_t *node_left = NULL;
    (*stk_index)++;

    if (IsOper(_TOKEN_, OPEN_R_BR))
    {
        (*stk_index)++;
        node_left = GetExpression(stk, stk_index);
        (*stk_index)++;  
    }

    Node_t *node_right = GetOperator(stk, stk_index);
    node = NewNode(node, node_left, node_right);

    ReadInfo("Успешно! Выполняю Dump");
    TreeDump(node, "out.txt", __LINE__);

    return node;
}

Node_t *GetFuncDeclare(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);

    if(!IsOper(_TOKEN_, OP_F_DCLR))
        return NULL;

    Node_t *func_node = _TOKEN_;
    (*stk_index)++;

    Node_t *node = GetFunction(stk, stk_index);

    Node_t *node_right = GetOperator(stk, stk_index);

    node = NewNode(node, GetLeft(node), node_right);
    func_node = NewNode(func_node, node, NULL);

    ReadInfo("Успешно! Выполняю Dump");
    TreeDump(func_node, "out.txt", __LINE__);

    return func_node;
}

Node_t *GetAssign(const TokStack_t *stk, int *stk_index)
{
    assert(stk);//null
    assert(stk_index);
    
    Node_t *node_left = GetVariable(stk, stk_index);

    if (node_left == NULL)
        return NULL;

    Node_t *node = _TOKEN_;
    (*stk_index)++;
    Node_t *node_right = GetExpression(stk, stk_index);

    node = NewNode(node, node_left, node_right);
    ReadInfo("Успешно! Выполняю Dump");
    TreeDump(node, "out.txt", __LINE__);

    return node;
}

Node_t *GetExpression(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);

    Node_t *node = GetTerm(stk, stk_index);

    if (node == NULL)
    {
        return node;
    }

    ReadInfo("Чтение операции сложения/вычитания");

    while (IsOper(_TOKEN_, OP_ADD) || IsOper(_TOKEN_, OP_SUB))
    {
        Node_t *temp_node = _TOKEN_;
        (*stk_index)++;

        Node_t *node_left = node;
        Node_t *node_right = GetTerm(stk, stk_index);
        
        node = NewNode(temp_node, node_left, node_right);
    }

    ReadInfo("Успешно! Выполняю Dump");
    TreeDump(node, "out.txt", __LINE__);

   return node;
}

Node_t *GetTerm(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);

    Node_t *node = GetExp(stk, stk_index);

    if (node == NULL)
    {
        return node;
    }

    ReadInfo("Чтение операции умножения/деления");
    while (IsOper(_TOKEN_, OP_MUL) || IsOper(_TOKEN_, OP_DIV))
    {
        Node_t *temp_node = _TOKEN_;
        (*stk_index)++;

        Node_t *node_left = node;
        Node_t *node_right = GetExp(stk, stk_index);
        
        node = NewNode(temp_node, node_left, node_right);
    }

    ReadInfo("Успешно! Выполняю Dump");
    TreeDump(node, "out.txt", __LINE__);

   return node;
}

Node_t *GetExp(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);

    Node_t *node = GetParent(stk, stk_index);
    
    if (node == NULL)
    {
        return node;
    }

    ReadInfo("Чтение операции возведения в степень");
    while (IsOper(_TOKEN_, OP_POW))
    {
        Node_t *temp_node = _TOKEN_;
        (*stk_index)++;

        Node_t *node_left = node;
        Node_t *node_right = GetParent(stk, stk_index);
        
        node = NewNode(temp_node, node_left, node_right);
    }
    
    ReadInfo("Успешно! Выполняю Dump");
    TreeDump(node, "out.txt", __LINE__);

   return node;
}

Node_t *GetParent(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);
    
    Node_t *node = NULL;

    if (IsOper(_TOKEN_, OPEN_R_BR))
    {
        ReadInfo("Чтение выражения в скобках");

        (*stk_index)++;
        node = GetExpression(stk, stk_index);
        (*stk_index)++;
    }

    else if (IsNumType(_TOKEN_))
    {
        ReadInfo("Чтение числа");
        node = GetNumber(stk, stk_index);
    }

    else if (IsVarType(_TOKEN_))
    {
        ReadInfo("Чтение переменной");
        node = GetVariable(stk, stk_index);
    }

    else if (IsFuncType(_TOKEN_) || IsOperType(_TOKEN_))
    {
        ReadInfo("Чтение функции");
        node = GetFunction(stk, stk_index);
    }

    return node;
}

Node_t *GetVariable(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);

    if (IsVarType(_TOKEN_))
    {
        Node_t *node = _TOKEN_;
        (*stk_index)++;

        return node;        
    }

    else
    {
        return NULL;
    }
}

Node_t *GetFunction(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);

    if (!IsFuncType(_TOKEN_) && !IsOper(_TOKEN_, OP_SQRT))
    {
        return NULL;
    }

    Node_t *node = _TOKEN_;//func type op type dif
    (*stk_index) += 2;

    Node_t *node_args = GetExpression(stk, stk_index);

    while (IsOper(_TOKEN_, OP_COMMA))
    {
        Node_t *temp_node = _TOKEN_;
        (*stk_index)++;

        Node_t *node_right = GetExpression(stk, stk_index);
        Node_t *node_left = node_args;
        
        node_args = NewNode(temp_node, node_left, node_right);
    }

    node = NewNode(node, node_args, NULL);
    (*stk_index)++;

    ReadInfo("Успешно! Выполняю Dump");
    TreeDump(node, "out.txt", __LINE__);

    return node;
}

Node_t *GetNumber(const TokStack_t *stk, int *stk_index)
{
    assert(stk);
    assert(stk_index);

    if (IsNumType(_TOKEN_))
    {
        Node_t *node = _TOKEN_;
        (*stk_index)++;

        return node;
    }

    else
    {
        return NULL;
    }
}
