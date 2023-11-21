#ifndef COLOSSALG_ARRAY_STACK_OF_<typename>
#define COLOSSALG_ARRAY_STACK_OF_<typename>

#include <stdbool.h>
#include <stdlib.h>

<additional_abs_headers>
<additional_rel_headers>

struct array_stack_of_<typename>;
struct array_stack_optional_<typename>;

typedef struct array_stack_of_<typename> array_stack_of_<typename>;
typedef struct array_stack_optional_<typename> array_stack_optional_<typename>;

struct array_stack_of_<typename> {
    size_t max_size;
    size_t size;
    size_t head;
    <typename>* elements;

    array_stack_optional_<typename> (*pop) (array_stack_of_<typename>* stack);
    bool (*push)     (array_stack_of_<typename>* stack, <typename> data);
    void (*clear)    (array_stack_of_<typename>* stack);
    void (*destroy)  (array_stack_of_<typename>* stack);

    void (*destroy_data)(<typename> data);
};

struct array_stack_optional_<typename> {
    bool has_value;
    <typename> value;
};

array_stack_of_<typename>* array_stack_of_<typename>_create(size_t max_size);

#endif // COLOSSALG_ARRAY_STACK_OF_<typename>