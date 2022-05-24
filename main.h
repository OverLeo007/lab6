typedef struct {
    int id;
    int length;
    char * name;
    int min_depth;
    int passability_lvl;
} river;


typedef enum {
    FIRST = 1,
    SECOND
} filter_opts_enum;


typedef enum {
    ADD_RIVER = 1,
    DEL_RIVER,
    PRINT_RIVERS,
    SORT_MENU,
    FILTER_MENU,
    SAVE,
    LOAD,
    REVERSE,
    LIST_LEN,
    EXIT
} main_menu_enum;


typedef enum {
    SORT_NAME = 1,
    SORT_LEN,
    SORT_DEPTH,
    SORT_PASS,
    SORT_EXIT
} sort_menu_enum;

typedef enum {
    FILTER_NAME = 1,
    FILTER_LEN,
    FILTER_DEPTH,
    FILTER_PASS,
    FILTER_CLEAR,
    FILTER_EXIT
}filter_menu_enum;

typedef struct _Node {
    river value;
    struct _Node *next;
    struct _Node *prev;
} Node;



typedef struct _DblLinkedList {
    size_t size;
    Node *head;
    Node *tail;
} DblLinkedList;

/* Вывод меню сортировки с последующим выбором поля,
 * по которому будем сортировать и сама сортировка */
void sort_menu(DblLinkedList *list);

/* Создание списка */
DblLinkedList* create_dlLinkedList();

/* Меняет местами следующую и пердыдущую ноды*/
void swap(Node* node);

/* Разворот списка */
void reverse_DDL(DblLinkedList *list);

/*Меню выбора фильтров для передачи в функцию фильтрации*/
unsigned char *pick_ffields();

/* Сбор данных по выбранным фильтрам и вывод отфильтрованного списка */
void print_filters(unsigned char *filters, DblLinkedList *list);

/* Удаление списка */
void delete_dblLinkedList(DblLinkedList **list);

/* Удаляет элемент из списка по индексу */
char *delete_river(DblLinkedList *list, size_t index);

/* Получение длины списка */
int get_len(const DblLinkedList *list);

/* Добавляет элемент в список */
void add_river(int length, char *name, int depth, DblLinkedList *list);

/* Меняет местами текущую и следующую ноды, заменяя все связи */
void swap_with_next(DblLinkedList *list, Node *n1);

/* Сортировка списка пузырьком, по выбранному критерию,
 * за который отвечает компаратор*/
void bubble_sort(DblLinkedList *list, int (*cmp)(const river*, const river*));

/* Компаратор имени */
int compare_names(const river* river1, const river* river2);

/* Компаратор длины */
int compare_lens(const river* river1, const river* river2);

/* Компаратор глубины */
int compare_depths(const river* river1, const river* river2);

/* Компаратор проходимости */
int compare_pass(const river* river1, const river* river2);

/* Возвращает ноду по ее индексу*/
Node* get_node(DblLinkedList *list, size_t index);

/* Сохраняет список в файл */
void save(DblLinkedList *list);

/* Возвращает длину строки от SEEK_CUR до первого \n*/
int line_len(FILE *file);

/* Загрузка сохраненного списка в программу*/
DblLinkedList *load();

/* Выводит все реки из списка */
void print_rivers(DblLinkedList *list);

/* Вывод реки */
void print_river(river river_tp, int num);