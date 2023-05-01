
typedef struct {
    int id;
    int length;
    char *name;
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
} filter_menu_enum;

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


/*!
 * \brief печать и взаимодействие с меню сортировки
 * \details Вывод меню сортировки с последующим выбором поля,
    по которому будем сортировать и сама сортировка
 * \param list список для сортировки
*/
void sort_menu(DblLinkedList *list);

/*!
 * \brief создание списка
 * \return созданный пустой двусвязный список
 */
DblLinkedList *create_dlLinkedList();

/*!
 * \brief разворот ноды
 * \details меняет местами prev и next ноды
 * \param node нода для разворота
*/
void swap(Node *node);

/*!
 * \brief разворот списка
 * \param list список для разворота
 */

void reverse_DDL(DblLinkedList *list);

/*!
 * \brief меню выбора фильтров
 * \details меню для выбора фильтров, позволяет выбирать несколько
 * и очищать выбранные фильтры
 * \return массив содержащий 4 char элемента, каждый из которых
 * 1 если фильтр выбран 0 если не выбран
*/
unsigned char *pick_ffields();

/*!
 * \brief вывод отфильтрофанного списка по выбранным данным
 * \details собирает дополнительную информацию для выбранных
 * фильтров и выводит отфильтрованный список
 * \param filters массив содержащий 4 char элемента, каждый из которых
 * 1 если фильтр выбран 0 если не выбран
 * \param list список для фильтрации
*/
void print_filters(unsigned char *filters, DblLinkedList *list);

/*!
 * \brief удаляет список, очищая память занятую им
 * \details последовательно удаляет каждую ноду,
 * также очищая память занятую ее value
 * \param list список для удаления
 */
void delete_dblLinkedList(DblLinkedList **list);

/*!
 * \brief удаляет ноду из списка
 * \details при удаленни ноды, отвязывает ее от остальных
 * и очищает память занятую ее value
 * \param list список из которого удаляем
 * \param index индекс ноды в списке (нумерация с единицы)
 * \return имя удаленной ноды
 */
char *delete_river(DblLinkedList *list, size_t index);

/*!
 * \brief возвращает длину списка
 * \details проходится по всем нодам списка, считая их ко-во
 * \param list список для подсчета длины
 * \return длина списка
 */
int get_len(const DblLinkedList *list);

/*!
 * \brief добавляет ноду в список по значениям value
 * \details создает экземпляр river и заполняет его входными значениями,
 * добавляет в список ноду, value которой - экземпляр river
 * \param length длина реки
 * \param name название реки
 * \param depth мин. глубина реки
 * \param list список в который добавляем ноду
 */
void add_river(int length, char *name, int depth, DblLinkedList *list);


/*!
 * \brief полностью меняет текущую и следующую ноды местами
 * \details меняет ноды при этом изменяя связи
 * предыдущей и следующей нод для двух нод которые мы меняем
 * \param list список в котором мы меняем ноды
 * \param n1 нода, которую мы меняем со следующей
 */
void swap_with_next(DblLinkedList *list, Node *n1);

/*!
 * \brief сортирует список пузырьком
 * \details производит сортировку спискапузырьком, сравнивание элементов
 * производится компаратором, переданным в аргументах
 * \param list список для сортировки
* \param cmp компаратор, сравнивающий два value ноды
 */
void bubble_sort(DblLinkedList *list, int (*cmp)(const river *, const river *));

/// \brief компаратор для имени
int compare_names(const river *river1, const river *river2);

/// \brief компаратор для длины реки
int compare_lens(const river *river1, const river *river2);

/// \brief компаратор для мин. глубины реки
int compare_depths(const river *river1, const river *river2);

/// \brief компаратор для проходимости реки
int compare_pass(const river *river1, const river *river2);

/*!
 * \brief возвращает ноду из списка по индексу
 * \param list список из которого хотим получить ноду
 * \param index индекс ноды в списке
 * \return нода, индекс которой был на входе
 */
Node *get_node(DblLinkedList *list, size_t index);

/*!
 * \brief сохраняет список в файл rivers_data.txt
 * \param list список для сохранения
 */
void save(DblLinkedList *list);

/*!
 * \brief возвращает длину до конца строки
 * \details счиает длину строки от текущего положения SEEK_CUR до \n
 * и переводит SEEK_CUR в начальное положение
 * \param file файл, дляну строки в котором мы вычисляем
 * \return длина строки до \n
 */
int line_len(FILE *file);

/*!
 * \brief читает список из файла и возвращает его
 * \details считывает поля для value каждой ноды из списка,
 * сохраненного в файле rivers_data.txt
 * \return список, прочитанный из файла rivers_data.txt
 */
DblLinkedList *load();

/*!
 * \brief выводит все реки из списка
 * \param list список содержащий реки для вывода
 */
void print_rivers(DblLinkedList *list);

/*!
 * \brief красиво печатает реку
 * \param river_tp река для печати
 * \param ее номер в списке
 */
void print_river(river river_tp, int num);