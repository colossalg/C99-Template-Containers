struct list_of_<typename>;
struct list_of_<typename>_item;

typedef struct list_of_<typename> list_of_<typename>;
typedef struct list_of_<typename>_item list_of_<typename>_item;

struct list_of_<typename> {
    size_t size;
    list_of_<typename>_item* head;
    list_of_<typename>_item* tail;

    bool (*insert_at_head)  (list_of_<typename>* list, <typename> data);
    void (*remove_head)     (list_of_<typename>* list);
    bool (*insert_at_tail)  (list_of_<typename>* list, <typename> data);
    void (*remove_tail)     (list_of_<typename>* list);
    bool (*insert_before)   (list_of_<typename>_item* item, <typename> data);
    bool (*insert_after)    (list_of_<typename>_item* item, <typename> data);
    void (*remove)          (list_of_<typename>_item* item);
    void (*clear)           (list_of_<typename>* list);
    void (*destroy)         (list_of_<typename>* list);

    void (*destroy_data)(<typename> data);
};

struct list_of_<typename>_item {
    list_of_<typename>* list;
    <typename> data;
    list_of_<typename>_item* prev;
    list_of_<typename>_item* next;
};

list_of_<typename>* list_of_<typename>_create();