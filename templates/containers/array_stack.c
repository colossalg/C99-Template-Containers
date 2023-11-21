#include "<template_header>"

#include <stdio.h>

<additional_abs_headers>
<additional_rel_headers>

array_stack_optional_<typename> array_stack_of_<typename>_pop(array_stack_of_<typename>* stack)
{
    array_stack_optional_<typename> result;
    result.has_value = false;

    if (stack->size <= 0) {
        return result;
    }

    result.has_value = true;
    result.value     = stack->elements[stack->head];

    stack->head--;
    stack->size--;

    return result;
}

bool array_stack_of_<typename>_push(array_stack_of_<typename>* stack, <typename> data)
{
    if (stack->size >= stack->max_size) {
        return false;
    }

    stack->size++;
    stack->head++;
    stack->elements[stack->head] = data;

    return true;
}

void array_stack_of_<typename>_clear(array_stack_of_<typename>* stack)
{
    for (size_t i = 0; i < stack->size; ++i) {
        stack->destroy_data(stack->elements[i]);
    }
}

void array_stack_of_<typename>_destroy(array_stack_of_<typename>* stack)
{
    stack->clear(stack);
    free(stack->elements);
    free(stack);
}

void array_stack_of_<typename>_destroy_data_default(<typename> data) {}

array_stack_of_<typename>* array_stack_of_<typename>_create(size_t max_size)
{
    <typename>* elements = malloc(sizeof(<typename>) * max_size);
    if (NULL == elements) {
        return NULL;
    }

    array_stack_of_<typename>* stack = malloc(sizeof(array_stack_of_<typename>));
    if (NULL == stack) {
        free(elements);
        return NULL;
    }

    stack->max_size = max_size;
    stack->size     =  0;
    stack->head     = -1;
    stack->elements = elements;

    stack->pop      = &array_stack_of_<typename>_pop;
    stack->push     = &array_stack_of_<typename>_push;
    stack->clear    = &array_stack_of_<typename>_clear;
    stack->destroy  = &array_stack_of_<typename>_destroy;

    stack->destroy_data = &array_stack_of_<typename>_destroy_data_default;

    return stack;
}
