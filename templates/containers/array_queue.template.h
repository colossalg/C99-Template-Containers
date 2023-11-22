struct array_queue_of_<typename>;

typedef struct array_queue_of_<typename> array_queue_of_<typename>;

struct array_queue_of_<typename> {
    size_t max_size;
    size_t size;
    size_t head;
    size_t tail;
    <typename>* elements;

    bool                (*enqueue)  (array_queue_of_<typename>* queue, <typename> data);
    optional_<typename> (*dequeue)  (array_queue_of_<typename>* queue);
    void                (*clear)    (array_queue_of_<typename>* queue);
    void                (*destroy)  (array_queue_of_<typename>* queue);

    void (*destroy_data)(<typename> data);
};

array_queue_of_<typename>* array_queue_of_<typename>_create(size_t max_size);