#include "bul.h"


// Рекурсивно собираем все уникальные переменные в дереве
void collect_variables(struct NODE* node, Variable* vars, int* count) 
{
    if (!node) 
    {
        return;
    }

    if (node->type == VAR) 
    {
        // Проверяем, есть ли переменная уже в списке
        for (int i = 0; i < *count; i++) 
        {
            if (vars[i].name == node->value.var_value) 
            {
                return;
            }
        }
        // Добавляем новую переменную
        vars[*count].name = node->value.var_value;
        vars[*count].value = 0;
        (*count)++;
    }

    collect_variables(node->left, vars, count);
    collect_variables(node->right, vars, count);
}

// Рекурсивно вычисляем значение дерева
int evaluate(struct NODE* node, Variable* vars, int var_count) {
    if (!node) return 0;

    if (node->type == NUM) 
    {
        return node->value.num_value;
    }
    if (node->type == VAR) 
    {
        for (int i = 0; i < var_count; i++) 
        {
            if (vars[i].name == node->value.var_value) 
            {
                return vars[i].value;
            }
        }
        return 0; // Если переменная не найдена
    }

    int left = evaluate(node->left, vars, var_count);
    int right = evaluate(node->right, vars, var_count);

    switch (node->value.oper_value) 
    {
        case AND: return left && right;
        case OR:  return left || right;
        case NOT: return !left;
        case XOR: return left ^ right;
        case IMP: return !left || right;
        case XNOR: return !(left ^ right);
        default: return 0;
    }
}

// Генерация всех комбинаций и вывод таблицы
void print_truth_table(struct NODE* root) 
{
    Variable vars[max_variable]; 
    int var_count = 0;

    // Собираем переменные
    collect_variables(root, vars, &var_count);

    for (int i = 0; i < var_count; i++) 
    {
        printf("%c ", vars[i].name);
    }
    printf("| Result\n");

    for (int i = 0; i < var_count*2 + 8; i++) 
    {
        printf("-");
    }
    printf("\n");

    // Перебираем все комбинации 
    for (int mask = 0; mask < (1 << var_count); mask++) 
    {
        for (int i = 0; i < var_count; i++) 
        {
            vars[i].value = (mask >> (var_count - 1 - i)) & 1;
        }

        // Выводим комбинацию
        for (int i = 0; i < var_count; i++) 
        {
            printf("%d ", vars[i].value);
        }

        // Вычисляем и выводим результат
        printf("|   %d\n", evaluate(root, vars, var_count));
    }
}

