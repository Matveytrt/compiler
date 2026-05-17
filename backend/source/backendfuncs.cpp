#include "../headers/backendfuncs.h"
#include <cstdio>

#define LOGPRINT_(text) fprintf(Logfile, "<pre>\n\t<h3>\n\t\tDUMP from %s:%d <font color = red>Tree %s </font>\n\t</h3>\n<p style=\"font-size: 30px;\">\n", __func__, __LINE__, text)

Node_t *ReadTreeFromFile(const char *input_tree, const char *output_tree, int line)
{
    assert(input_tree);
    assert(output_tree);

    File_Info_t info = {};

    info.buff = (char *) ReadBuffResult(input_tree, "r", &info.buff_size, sizeof(char));
    
    char *start_ptr = info.buff;
    int cur_pos = 0;
    int start_idx = 0;

    LOGPRINT_("Начало чтения дерева");
    Node_t *root_node = ReadNode(info.buff, &cur_pos, output_tree, &start_idx);
    SetScopes(root_node, GLOBAL, 0);

    TreeDump(root_node, output_tree, line);
    fprintf(Logfile, "<h3>\n\t<font color = red> Чтение дерева закончено! </font>\n</h3>\n</p>\n</pre>\n");

    free(start_ptr);

    return root_node;
}

void SetScopes(Node_t *node, int scope, int arg_end_idx)
{
    if (!node) return;

    if (IsOper(node, OP_V_DCLR)) {
        Node_t *var_node = GetLeft(node);
        int var_ofs = - (GetVar(var_node) - arg_end_idx + 1) * _REG_SIZE_;

        SetVarScope(var_node, scope);
        
        SetVarOfs(var_node, var_ofs);
        return;
    }

    if (IsOper(node, OP_F_DCLR)) {
        int arg_ofs = _ARGS_OFS_;
        Node_t *func_node = GetLeft(node);

        SetArgScopes(GetLeft(func_node), arg_ofs, &arg_end_idx);

        Func_table.data[GetFunc(func_node)].arg_end_idx = arg_end_idx;

        SetScopes(GetRight(func_node), LOCAL, arg_end_idx);
    }
        
    else SetScopes(GetLeft(node), scope, arg_end_idx);

    SetScopes(GetRight(node), scope, arg_end_idx);
}

int SetArgScopes(Node_t *node, int arg_ofs, int *arg_end_idx)
{
    if (!node) return arg_ofs;

    arg_ofs = SetArgScopes(GetLeft(node), arg_ofs, arg_end_idx);

    arg_ofs = SetArgScopes(GetRight(node), arg_ofs, arg_end_idx);

    if (IsVarType(node))
    {
        SetVarScope(node, ARGUMENT);
        SetVarOfs(node, arg_ofs);  
        arg_ofs += 8;
        *arg_end_idx = GetVar(node) + 1;
    }

    return arg_ofs;
}

#define ReadInfo(info)                                                                                                  \
    fprintf(Logfile, "Вызов #%d Я функция по имени %s called from line:%d\n" info "\n", iteration, __func__, __LINE__); \
    fprintf(Logfile, "cur_pos:%d\ncur_buff_pos:<font color = green>%.*s</font>"                                         \
                                              "<font color = red>%c</font>"                                             \
                                              "<font color = blue>%s</font>\n",                                         \
                          *cur_pos, *cur_pos, buff, *(buff + *cur_pos), buff + *cur_pos + 1);                           \
    fprintf(Logfile, "\n\n\n");

Node_t *ReadNode(char *buff, int *cur_pos, const char *output_tree, int *start_index)
{
    assert(cur_pos);
    assert(buff);
    assert(output_tree);
    assert(start_index);

    int offset = 0;
    static int iteration = 0;
    int temp_idx = 0;

    iteration++;
    
    ONDEBUG(ReadInfo("Начинаю чтение узла"));

    (*cur_pos) += SkipSpaces(buff + *cur_pos);

    if(*(buff + *cur_pos) == '(')
    {
        (*cur_pos)++;
        (*cur_pos) += SkipSpaces(buff + *cur_pos);

        ONDEBUG(ReadInfo("До чтения имени узла"));

        sscanf(buff + *cur_pos, " \"%*[^\"]%n", &offset);

        char *name = buff + *cur_pos + 1;
        
        (*cur_pos) += offset;
        *(buff + *cur_pos) = '\0';

        Node_t *node = CheckNodeType(name, *start_index);

        if (IsOper(node, OP_F_DCLR)) {
            *start_index = (int) Var_table.size;
            temp_idx = *start_index;
        }

        *(buff + *cur_pos) = '\"';
        (*cur_pos)++;
        (*cur_pos) += SkipSpaces(buff + *cur_pos);

        ONDEBUG(fprintf(Logfile, "it = %d: node_name: %s\n", iteration, name));
        ONDEBUG(ReadInfo("После чтения имени узла / До чтения левого поддерева"));

        SetLeft(node, ReadNode(buff, cur_pos, output_tree, start_index));

        if(GetLeft(node)) SetParent(GetLeft(node), node);

        (*cur_pos) += SkipSpaces(buff + *cur_pos);

        ONDEBUG(ReadInfo("После чтения левого поддерева / До чтения правого поддерева"));

        SetRight(node, ReadNode(buff, cur_pos, output_tree, start_index));

        if(GetRight(node)) SetParent(GetRight(node), node);

        (*cur_pos) += SkipSpaces(buff + *cur_pos);

        #ifdef DEBUG
            ReadInfo("После чтения правого поддерева");
            ReadInfo("Закончила чтение узла выполняю Dump");
            TreeDump(node, output_tree, __LINE__);
            fprintf(Logfile, "<p style=\"font-size: 30px;\"> ");
        #endif

        (*cur_pos)++;

        if (IsOper(node, OP_F_DCLR)) {
            *start_index = (int) Var_table.size;
            Func_table.data[GetFunc(GetLeft(node))].start_idx = temp_idx;
            Func_table.data[GetFunc(GetLeft(node))].end_idx = *start_index - 1;
        }

        return node;
    }

    else {
        (*cur_pos) += IsNil(buff + *cur_pos);    
        return NULL;
    }
}

Node_t *CheckNodeType(const char *str, int start_idx)
{
    assert(str);

    char type_str[STRSIZE] = "";
    int offset = 0;
    int index = NOT_FOUND;

    sscanf(str, " %s%n", type_str, &offset);
    str += offset;  

    char name_str[STRSIZE] = "";

    sscanf(str, " %s", name_str);

    Node_t *node = NULL;

    if (strcmp(type_str, "OP") == 0)
    {
        for (int op_index = 0; op_index < _OPERDATASIZE_; op_index++)
        {
            if (strcmp(name_str, Oper_table[op_index].std_name) == 0) 
                node = CTOR_OP(Oper_table[op_index].code);    
        }    
    }

    if (strcmp(type_str, "VAR") == 0)
    {
        index = SearchVarName(name_str, start_idx);

        if (index == NOT_FOUND)
        {
            Var_t var = {};
            var.name = strdup(name_str);
            var.len = strlen(name_str);

            index = (int) Var_table.size;
            PUSH_VAR(var);
        }

        node = CTOR_VAR(index);
    }

    if (strcmp(type_str, "FUNC") == 0)
    {
        index = SearchFuncName(name_str);
        if (index == NOT_FOUND)
        {
            Func_t func = {};
            func.name = strdup(name_str);
            func.len = strlen(name_str);

            index = (int) Func_table.size;
            PUSH_FUNC(func);
        }

        node = CTOR_FUNC(index);
    }

    if (strcmp(type_str, "NUM") == 0)
    {
        TreeElem_t result = (TreeElem_t) strtod(name_str, NULL);
        node = CTOR_NUM(result);
    }

    return node;
}

int SkipSpaces(const char *buff)
{
    assert(buff);

    int offset = 0;

    while (*buff == ' ' || *buff == '\n' || *buff == '\r') {
        buff++;
        offset++;
    }

    return offset;
}

int IsNil(const char *buff)
{
    assert(buff);

    int offset = 0;

    if (strncmp(buff, "nil", strlen("nil")) == 0) offset += (int) strlen("nil");

    return offset;
}

void DumpVarTable()
{   
    LOGPRINT_("ПЕЧАТЬ таблицы имен");
    
    for (int idx = 0; idx < Var_table.size; idx++) {
        Var_t var = Var_table.data[idx];
        fprintf(Logfile, "| %8s | %03d | ofs:%03d | %.*s |\n", GetVarScopeName(var.scope), idx, var.ofs, NUMSTEP, var.name);
    }    
}

void DumpFuncTable()
{
    LOGPRINT_("ПЕЧАТЬ таблицы функций");

    fprintf(Logfile, "| %16s | start | end |arg_end|\n", "func_name");

    for (int idx = 0; idx < Func_table.size; idx++) {
        Func_t func = Func_table.data[idx];
        fprintf(Logfile, "| %16s | %05d | %03d | %05d |\n", func.name, func.start_idx, func.end_idx, func.arg_end_idx);
    }
}