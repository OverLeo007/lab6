//
// Created by leva on 14.05.2022. 19:38
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "inoutput_funcs.h"
#include "main.h"


#define CUR_RIVER (tmp->value)


int main() {
    DblLinkedList *list = create_dlLinkedList();

    srand(time(NULL));
    system("chcp 65001 > nul");


    int menu_variant;
    do {
        puts("1. Добавить реку");
        puts("2. Удалить реку по номеру");
        puts("3. Вывести реки");
        puts("4. Меню сортировки");
        puts("5. Меню фильтрации");
        puts("6. Сохранить реки в файл");
        puts("7. Загрузить реки из файла");
        puts("8. Развернуть список");
        puts("9. Вывести длину списка");
        puts("10. Выйти");


        menu_variant = input_int();

        switch (menu_variant) {
            case ADD_RIVER:
                puts("Введите назавние реки:");
                char *name = input_string();
                if (name[0] == '\0') {
                    puts("Некорректное имя!");
                    break;
                }
                puts("Введите длину реки:");
                int lenght = input_int();
                if (lenght == -1) {
                    puts("Некорректная длина!");
                    break;
                }
                puts("Введите минимальную глубину реки:");
                int depth = input_int();
                if (depth < 1) {
                    puts("Некорректная минимальная глубина!");
                    break;
                }
                add_river(lenght, name, depth, list);
                puts("Река успешно добавлена");
                break;

            case DEL_RIVER: {
                puts("Введите номер реки для удаления:");
                int num = input_int();
                char *d_name = delete_river(list, num);
                if (d_name[0] == '\0') break;
                printf("Река %s удалена\n", d_name);
                free(d_name);
            }
                break;

            case PRINT_RIVERS:
                print_rivers(list);
                break;

            case SORT_MENU:
                sort_menu(list);
                break;
            case FILTER_MENU: {
                unsigned char *fields = pick_ffields();
                print_filters(fields, list);
            }
                break;
            case SAVE:
                save(list);
                puts("Реки успешно сохранены в файл");
                break;
            case LOAD:
                delete_dblLinkedList(&list);
                list = load();
                puts("Реки успешно загружены из файла");
                break;
            case REVERSE:
                reverse_DDL(list);
                puts("Список развернут");
                break;
            case LIST_LEN:
                printf("Длина списка: %d\n", get_len(list));
                break;
            case EXIT:
                delete_dblLinkedList(&list);
                break;
            default:
                puts("Такого варианта в меню нет!");
                break;
        }
    } while (menu_variant != 10);

    return 0;
}


void sort_menu(DblLinkedList *list) {
    int sort_variant;
    do {
        puts("1. Отсортировать по имени");
        puts("2. Отсортировать по длине");
        puts("3. Отсортировать по минимальной глубине");
        puts("4. Отсортировать по проходимости для судов");
        puts("5. Выйти из меню сортировки");
        sort_variant = input_int();
        switch (sort_variant) {
            case SORT_NAME:
                bubble_sort(list, compare_names);
                print_rivers(list);
                break;
            case SORT_LEN:
                bubble_sort(list, compare_lens);
                print_rivers(list);
                break;
            case SORT_DEPTH:
                bubble_sort(list, compare_depths);
                print_rivers(list);
                break;
            case SORT_PASS:
                bubble_sort(list, compare_pass);
                print_rivers(list);
                break;
            case SORT_EXIT:
                break;
            default:
                puts("Такого варианта выбора нет!");
        }
    } while (sort_variant != 5);
}


unsigned char *pick_ffields() {
    unsigned char *picked_fields = calloc(4, sizeof(unsigned char));
    int variant;
    puts("Выберите поля по которым будет произведена фильтрация");
    do {
        (picked_fields[0]) ? puts("1. Вхождение в имя + ") :
        puts("1. Вхождение в имя");
        (picked_fields[1]) ? puts("2. Протяженность + ") :
        puts("2. Протяженность");
        (picked_fields[2]) ? puts("3. Наим. глубина + ") :
        puts("3. Наим. глубина");
        (picked_fields[3]) ? puts("4. Проходимость судов + ") :
        puts("4. Проходимость судов");
        puts("5. Сбросить фильтр");
        puts("6. Завершить выбор фильтров");
        variant = input_int();
        switch (variant) {
            case FILTER_NAME:
                picked_fields[0] = 1;
                break;
            case FILTER_LEN:
                picked_fields[1] = 1;
                break;
            case FILTER_DEPTH:
                picked_fields[2] = 1;
                break;
            case FILTER_PASS:
                picked_fields[3] = 1;
                break;
            case FILTER_CLEAR:
                for (int i = 0; i < 4; i++) picked_fields[i] = 0;
                break;
            case FILTER_EXIT:
                return picked_fields;
            default:
                puts("Такого варианта выбора нет!");
                break;
        }
    } while (true);
}


void print_filters(unsigned char *filters, DblLinkedList *list) {
    DblLinkedList *f_list = create_dlLinkedList();

    Node *tmp = list->head;
    while (tmp) {


        add_river(CUR_RIVER.length,
                  CUR_RIVER.name,
                  CUR_RIVER.min_depth,
                  f_list);
        tmp = tmp->next;
    }
    free(tmp);


    while (true) {
        if (filters[0]) {
            puts("\nВведите подстроку для имени");
            char *subname = input_string();
            if (subname[0] == '\0') {
                puts("Некорректное значение!");
                continue;
            }

            tmp = f_list->head;
            while (tmp) {
                if (strstr(CUR_RIVER.name, subname) == NULL) {
                    CUR_RIVER.length = -1;
                }
                tmp = tmp->next;
            }
        }

        if (filters[1]) {
            puts("Введите значение протяженности, от которого будем считать");
            int flenght = input_int();
            if (flenght <= 0) {
                puts("Некорректное значение!");
                continue;
            }
            printf("1. Ищем <%d\n", flenght);
            printf("2. Ищем >%d\n", flenght);
            int variant = input_int();
            switch (variant) {
                case FIRST:
                    tmp = f_list->head;
                    while (tmp) {
                        if (CUR_RIVER.length >= flenght) CUR_RIVER.length = -1;

                        tmp = tmp->next;
                    }
                    break;
                case SECOND:
                    tmp = f_list->head;
                    while (tmp) {
                        if (CUR_RIVER.length > 0 && CUR_RIVER.length < flenght)
                            CUR_RIVER.length = -1;

                        tmp = tmp->next;
                    }
                    break;
                default:
                    puts("Некорректное значение!");
                    continue;
            }

        }

        if (filters[2]) {
            puts("Введите значение минимальной глубины,"
                 " от которого будем считать");
            int fdepth = input_int();
            if (fdepth <= 0) {
                puts("Некорректное значение!");
                continue;
            }
            printf("1. Ищем <%d\n", fdepth);
            printf("2. Ищем >%d\n", fdepth);
            int variant = input_int();
            switch (variant) {
                case FIRST:
                    tmp = f_list->head;
                    while (tmp) {
                        if (CUR_RIVER.min_depth >= fdepth)
                            CUR_RIVER.length = -1;

                        tmp = tmp->next;
                    }
                    break;
                case SECOND:
                    tmp = f_list->head;
                    while (tmp) {
                        if (CUR_RIVER.min_depth > 0
                            && CUR_RIVER.min_depth < fdepth)
                            CUR_RIVER.length = -1;

                        tmp = tmp->next;
                    }
                    break;
                default:
                    puts("Некорректное значение!");
                    continue;
            }
        }
        if (filters[3]) {
            puts("1. Несудоходная");
            puts("2. Проходима для малых судов");
            puts("3. Проходима для крупных судов");
            int varinant = input_int();
            if (varinant < 1 || varinant > 3) {
                puts("Некорректное значение!");
                continue;
            }
            tmp = f_list->head;
            while (tmp) {
                if (CUR_RIVER.passability_lvl != (varinant - 1))
                    CUR_RIVER.length = -1;

                tmp = tmp->next;
            }
        }
        break;
    }
    print_rivers(f_list);
    delete_dblLinkedList(&f_list);
    free(filters);
}


int get_len(const DblLinkedList *list) {
    int size = 0;
    Node *tmp = list->head;
    while (tmp) {
        size++;
        tmp = tmp->next;
    }
    return size;
}


void swap(Node *node) {
    Node *prev = node->prev;
    node->prev = node->next;
    node->next = prev;
}


void reverse_DDL(DblLinkedList *list) {
    Node *prev = NULL;
    Node *curr = list->head;

    while (curr != NULL) {
        swap(curr);

        prev = curr;

        curr = curr->prev;
    }

    if (prev != NULL) {
        list->head = prev;
    }
}



void swap_with_next(DblLinkedList *list, Node *n1) {
    if (n1 == list->tail) return;
    Node *n0 = n1->prev;
    Node *n2 = n1->next;
    Node *n3 = n2->next;
    if (n0) n0->next = n2;
    else list->head = n2;

    n1->prev = n2;
    n1->next = n3;

    n2->prev = n0;
    n2->next = n1;

    if (n3) n3->prev = n1;
    else list->tail = n1;

}


void bubble_sort(DblLinkedList *list,
                 int (*cmp)(const river *, const river *)) {
    int len = (int) list->size;
    int sort = 1;
    int n = 0;
    while (sort) {
        sort = 0;
        for (int i = 0; i < len - 1 - n; i++) {
            Node *a_i = get_node(list, i);
            if (cmp(&(a_i->value), &(a_i->next->value)) > 0) {
                swap_with_next(list, a_i);
                sort = 1;
            }
        }
        n++;
    }
}


DblLinkedList *create_dlLinkedList() {
    DblLinkedList *tmp = (DblLinkedList *) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}


void delete_dblLinkedList(DblLinkedList **list) {
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(CUR_RIVER.name);
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}


Node *get_node(DblLinkedList *list, size_t index) {
    Node *tmp = list->head;
    size_t i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}


void add_river(int length, char *name, int depth, DblLinkedList *list) {
    river tmp_river;
    tmp_river.length = length;
    tmp_river.name = name;
    tmp_river.min_depth = depth;
    tmp_river.id = (int) list->size;
    if (depth < 2)
        tmp_river.passability_lvl = 0;
    else if (2 <= depth && depth < 4)
        tmp_river.passability_lvl = 1;
    else if (4 <= depth)
        tmp_river.passability_lvl = 2;

    Node *tmp = (Node *) malloc(sizeof(Node));

    tmp->value = tmp_river;
    tmp->next = NULL;
    tmp->prev = list->tail;

    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}


char *delete_river(DblLinkedList *list, size_t index) {
    Node *elm = NULL;
    elm = get_node(list, index - 1);
    if (elm == NULL) {
        puts("Некорректное значение");
        return "\0";
    }
    char* name = &(*(elm->value).name);
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }

    if (!elm->prev) {
        list->head = elm->next;
    }
    if (!elm->next) {
        list->tail = elm->prev;
    }

    free(elm);

    list->size--;
    return name;
}


void print_rivers(DblLinkedList *list) {
    if (list->size == 0) {
        puts("Не добавлено ни одной реки");
        return;
    }

    Node *tmp = list->head;
    int i = 0;

    while (tmp) {
//        int prev_id = -1;
//        if (tmp->prev) prev_id = tmp->prev->value.id;
//        int next_id = -1;
//        if (tmp->next) next_id = tmp->next->value.id;
//        printf("%d %d\n", prev_id, next_id);
        if (CUR_RIVER.length != -1) print_river(CUR_RIVER, i);
        tmp = tmp->next;
        ++i;
    }

}


void print_river(river river_tp, int num) {
    printf("Река №%d\n", num + 1);
    printf("\tНазвание %s\n", river_tp.name);
//    printf("\tid: %d\n", river_tp.id);
    printf("\tПротяженность: %d\n", river_tp.length);
    printf("\tМинимальная глубина: %d\n", river_tp.min_depth);
    if (river_tp.passability_lvl == 0)
        puts("\tНесудоходная");
    else if (river_tp.passability_lvl == 1)
        puts("\tПроходима для малых судов");
    else if (river_tp.passability_lvl == 2)
        puts("\tПроходима для крупных судов");
}


void save(DblLinkedList *list) {
    FILE *file = fopen("rivers_data.txt", "w");
    if (!list->head) {
        fclose(file);
        return;
    }
    fprintf(file, "%d\n", list->size);
    for (int i = 0; i < list->size; i++) {
        Node *cur_node = get_node(list, i);
        int prev_id = -1;
        if (cur_node->prev) prev_id = cur_node->prev->value.id;
        int next_id = -1;
        if (cur_node->next) next_id = cur_node->next->value.id;
        river cur_river = cur_node->value;
        fprintf(file, "%d║%d\n", prev_id, next_id);
        fprintf(file, "%d║%d║%d║%d║%s\n",
                cur_river.id, cur_river.length,
                cur_river.min_depth, cur_river.passability_lvl,
                cur_river.name);

    }
    fclose(file);
}


int line_len(FILE *file) {
    int len = 0;
    while (true) {
        char newc = getc(file);
        len++;
        if (newc == '\n') break;
    }

    fseek(file, -len - 1, SEEK_CUR);
    return len;
}


DblLinkedList *load() {
    FILE *file = fopen("rivers_data.txt", "r");
    DblLinkedList *new_list = create_dlLinkedList();

    int llen;
    fscanf(file, "%d\n", &llen);
    int prev_id, next_id;
    int id, length, depth, pass;


    for (int i = 0; i < llen; i++) {
        fscanf(file, "%d║%d\n", &prev_id, &next_id);
        fscanf(file, "%d║%d║%d║%d║", &id, &length, &depth, &pass);
        int len = line_len(file);
        char *name = malloc(sizeof(char) * len);
        fgets(name, len + 1, file);
        name[strcspn(name, "\n")] = '\0';
        add_river(length, name, depth, new_list);
    }
    return new_list;
}


int compare_names(const river *river1, const river *river2) {
    const char *name1 = river1->name;
    const char *name2 = river2->name;
    return strcmp(name1, name2);
}


int compare_lens(const river *river1, const river *river2) {
    const int len1 = river1->length;
    const int len2 = river2->length;
    return len1 - len2;
}


int compare_depths(const river *river1, const river *river2) {
    const int depth1 = river1->min_depth;
    const int depth2 = river2->min_depth;
    return depth1 - depth2;
}


int compare_pass(const river *river1, const river *river2) {
    const int pass1 = river1->passability_lvl;
    const int pass2 = river2->passability_lvl;
    return pass1 - pass2;
}