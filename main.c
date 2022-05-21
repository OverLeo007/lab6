//
// Created by leva on 14.05.2022. 19:38
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inoutput_funcs.h"
#include "head.h"

#define MAX_RIVERS 1000
#define RSIZE sizeof(river);

int main(void) {
    DblLinkedList *list = create_dlLinkedList();

    srand(time(NULL));
    system("chcp 65001 > nul");

    char name[5][10] = {"aboba", "abiba", "atata", "akunamata", "dababy?"};
    for (int i = 0; i < 5; i++) {
        add_river(rand() % 1000, name[i], rand() % 5, list);

    }
    print_rivers(list);
    puts("");
    bubble_sort(list, compare_lens);
//    swap_with_next(list, get_node(list, 4));

    print_rivers(list);

    delete_dblLinkedList(&list);
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
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
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

void push_front(DblLinkedList *list, river new_river) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->value = new_river;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}


river pop_front(DblLinkedList *list) {
    Node *prev;
    river tmp;
    if (list->head == NULL) {
        exit(2);
    }

    prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    tmp = prev->value;
    free(prev);

    list->size--;
    return tmp;
}

void push_back(DblLinkedList *list, river value) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->value = value;
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

void insert_before_element(DblLinkedList *list, Node *elm, river value) {
    Node *ins = NULL;
    if (elm == NULL) {
        exit(6);
    }

    if (!elm->prev) {
        push_front(list, value);
        return;
    }
    ins = (Node *) malloc(sizeof(Node));
    ins->value = value;
    ins->prev = elm->prev;
    elm->prev->next = ins;
    ins->next = elm;
    elm->prev = ins;

    list->size++;
}



void swap_with_next(DblLinkedList *list, Node *n1){
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

void bubble_sort(DblLinkedList *list, int (*cmp)(const river *, const river *)) {
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


Node *get_node(DblLinkedList *list, size_t index) {
    Node *tmp = list->head;
    size_t i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}


void delete_river(DblLinkedList *list, size_t index) {
    Node *elm = NULL;
    elm = get_node(list, index);
    if (elm == NULL) {
        puts("Некорректное значение");
        return;
    }
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
        print_river(tmp->value, i);
        tmp = tmp->next;
        ++i;
    }

}


void print_river(river river_tp, int num) {
    printf("Река №%d\n", num + 1);
    printf("\tНазвание %s\n", river_tp.name);
    printf("\tid: %d\n", river_tp.id);
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
    while (1) {
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