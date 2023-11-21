#ifndef COLOSSALG_ARRAY_QUEUE_OF_<typename>_H
#define COLOSSALG_ARRAY_QUEUE_OF_<typename>_H

#include <stdbool.h>
#include <stdlib.h>

<additional_abs_headers>
<additional_rel_headers>

struct array_queue_of_<typename>;
struct array_queue_optional_<typename>;

typedef struct array_queue_of_<typename> array_queue_of_<typename>;
typedef struct array_queue_optional_<typename> array_queue_optional_<typename>;

struct array_queue_of_<typename> {
    size_t max_size;
    size_t size;
    size_t head;
    size_t tail;
    <typename>* elements;

    array_queue_optional_<typename> (*dequeue) (array_queue_of_<typename>* queue);
    bool (*enqueue)  (array_queue_of_<typename>* queue, <typename> data);
    void (*clear)    (array_queue_of_<typename>* queue);
    void (*destroy)  (array_queue_of_<typename>* queue);

    void (*destroy_data)(<typename> data);
};

struct array_queue_optional_<typename> {
    bool has_value;
    <typename> value;
};

array_queue_of_<typename>* array_queue_of_<typename>_create(size_t max_size);

#endif // COLOSSALG_ARRAY_QUEUE_OF_<typename>_H