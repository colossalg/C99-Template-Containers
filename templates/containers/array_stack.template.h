struct array_stack_of_<typename>;

typedef struct array_stack_of_<typename> array_stack_of_<typename>;

struct array_stack_of_<typename> {
    size_t max_size;
    size_t size;
    size_t head;
    <typename>* elements;

    bool                (*push)     (array_stack_of_<typename>* stack, <typename> data);
    optional_<typename> (*pop)      (array_stack_of_<typename>* stack);
    void                (*clear)    (array_stack_of_<typename>* stack);
    void                (*destroy)  (array_stack_of_<typename>* stack);

    void (*destroy_data)(<typename> data);
};

array_stack_of_<typename>* array_stack_of_<typename>_create(size_t max_size);