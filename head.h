typedef struct {
    int id;
    int length;
    char * name;
    int min_depth;
    int passability_lvl;
} river;


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

void sort_menu();

DblLinkedList* create_dlLinkedList();

void swap(Node* node);

void reverse_DDL(DblLinkedList *list);

unsigned char *pick_ffields();

void print_filters(unsigned char *filters, DblLinkedList *list);

void delete_dblLinkedList(DblLinkedList **list);

char *delete_river(DblLinkedList *list, size_t index);

int get_len(const DblLinkedList *list);

void add_river(int length, char *name, int depth, DblLinkedList *list);

void swap_with_next(DblLinkedList *list, Node *n1);

void bubble_sort(DblLinkedList *list, int (*cmp)(const river*, const river*));

int compare_names(const river* river1, const river* river2);

int compare_lens(const river* river1, const river* river2);

int compare_depths(const river* river1, const river* river2);

int compare_pass(const river* river1, const river* river2);

Node* get_node(DblLinkedList *list, size_t index);

void save(DblLinkedList *list);

int line_len(FILE *file);

DblLinkedList *load();

void print_rivers(DblLinkedList *list);

void print_river(river river_tp, int num);