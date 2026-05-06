#include "headers/backendfuncs.h"

Node_t *ReadTreeFromFile(const char *input_tree, const char *output_tree, int line)
{
    assert(input_tree);
    assert(output_tree);

    File_Info_t info = {};

    info.buff = (char *) ReadBuffResult(input_tree, "r", &info.buff_size, sizeof(char));
    
    char *start_ptr = info.buff;
    int cur_pos = 0;
    int start_idx = 0;

    ONDEBUG(fprintf(Logfile, "<pre>\n\t<h3>\n\t\tDUMP from %s:%d <font color = red>Tree НАЧАЛО чтения дерева </font>\n\t</h3>\n<p style=\"font-size: 30px;\">\n", __func__, line));

    Node_t *root_node = ReadNode(info.buff, &cur_pos, output_tree, &start_idx);

    TreeDump(root_node, output_tree, line);
    ONDEBUG(fprintf(Logfile, "<h3>\n\t<font color = red> Чтение дерева закончено! </font>\n</h3>\n</p>\n</pre>\n"));

    free(start_ptr);

    return root_node;
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

        if (IsOper(node, OP_F_DCLR))
        {
            *start_index = (int) Var_table.size;
            temp_idx = *start_index;
        }

        *(buff + *cur_pos) = '\"';
        (*cur_pos)++;
        (*cur_pos) += SkipSpaces(buff + *cur_pos);

        ONDEBUG(fprintf(Logfile, "it = %d: node_name: %s\n", iteration, name));
        ONDEBUG(ReadInfo("После чтения имени узла / До чтения левого поддерева"));

        SetLeft(node, ReadNode(buff, cur_pos, output_tree, start_index));

        if(GetLeft(node))
            SetParent(GetLeft(node), node);

        (*cur_pos) += SkipSpaces(buff + *cur_pos);

        ONDEBUG(ReadInfo("После чтения левого поддерева / До чтения правого поддерева"));

        SetRight(node, ReadNode(buff, cur_pos, output_tree, start_index));

        if(GetRight(node))
            SetParent(GetRight(node), node);

        (*cur_pos) += SkipSpaces(buff + *cur_pos);

        #ifdef DEBUG
            ReadInfo("После чтения правого поддерева");
        
            ReadInfo("Закончила чтение узла выполняю Dump");
            TreeDump(node, output_tree, __LINE__);

            fprintf(Logfile, "<p style=\"font-size: 30px;\"> ");
        #endif

        (*cur_pos)++;

        if (IsOper(node, OP_F_DCLR))
        {
            *start_index = (int) Var_table.size;
            Func_table.data[GetFunc(GetLeft(node))].start_idx = temp_idx;
            Func_table.data[GetFunc(GetLeft(node))].end_idx = *start_index - 1;
            // printf("start_idx = %d\n", Func_table.data[GetFunc(node)].start_idx);
            // printf("end_idx = %d\n", Func_table.data[GetFunc(node)].end_idx);
        }

        return node;
    }

    else 
    {
        (*cur_pos) += IsNil(buff + *cur_pos);
        
        return NULL;
    }
}

Node_t *CheckNodeType(const char *str, int start_idx)
{
    assert(str);

    char *type_str = (char *) calloc(STRSIZE, sizeof(char));
    assert(type_str);

    int offset = 0;
    int index = NOT_FOUND;

    sscanf(str, " %s%n", type_str, &offset);
    str += offset;  

    char *name_str = (char *) calloc(STRSIZE, sizeof(char));
    assert(name_str);

    sscanf(str, " %s", name_str);

    //printf("name_str = %s\ntype_str = %s\n", name_str, type_str);

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

    free(name_str);
    free(type_str);

    return node;
}

int SkipSpaces(const char *buff)
{
    assert(buff);

    int offset = 0;

    while (*buff == ' ' || *buff == '\n' || *buff == '\r')
    {
        buff++;
        offset++;
    }

    return offset;
}

int IsNil(const char *buff)
{
    assert(buff);

    int offset = 0;

    if (strncmp(buff, "nil", strlen("nil")) == 0)
    {
        offset += (int) strlen("nil");
    }

    return offset;
}

void DumpVarTable()
{
    fprintf(Logfile, "<pre>\n\t<h3>\n\t\tDUMP from %s:%d <font color = red>ПЕЧАТЬ таблицы имен </font>\n\t</h3>\n<p style=\"font-size: 30px;\">\n", __func__, __LINE__);

    for (int idx = 0; idx < Var_table.size; idx++)
    {
        fprintf(Logfile, "| %03d | %.*s |\n", idx, NUMSTEP, Var_table.data[idx].name);
    }    
}

void DumpFuncTable()
{
    fprintf(Logfile, "<pre>\n\t<h3>\n\t\tDUMP from %s:%d <font color = red>ПЕЧАТЬ таблицы функций</font>\n\t</h3>\n<p style=\"font-size: 30px;\">\n", __func__, __LINE__);
    
    fprintf(Logfile, "| %16s | start | end |\n", "func_name");

    for (int idx = 0; idx < Func_table.size; idx++)
    {
        fprintf(Logfile, "| %16s | %5d | %3d |\n", Func_table.data[idx].name, Func_table.data[idx].start_idx, Func_table.data[idx].end_idx);
    }
}