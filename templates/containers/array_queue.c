#include "<template_header>"

#include <stdio.h>

<additional_abs_headers>
<additional_rel_headers>

array_queue_optional_<typename> array_queue_of_<typename>_dequeue(array_queue_of_<typename>* queue)
{
    array_queue_optional_<typename> result;
    result.has_value = false;

    if (queue->size <= 0) {
        return result;
    }

    result.has_value = true;
    result.value     = queue->elements[queue->head];

    queue->size--;
    queue->head = (queue->head + 1) % (queue->max_size + 1);

    return result;
}

bool array_queue_of_<typename>_enqueue(array_queue_of_<typename>* queue, <typename> data)
{
    if (queue->size >= queue->max_size) {
        return false;
    }

    queue->elements[queue->tail] = data;
    queue->size++;
    queue->tail = (queue->tail + 1) % (queue->max_size + 1);

    return true;
}

void array_queue_of_<typename>_clear(array_queue_of_<typename>* queue)
{
    size_t curr  = queue->head;
    while (curr != queue->tail) {
        queue->destroy_data(queue->elements[curr]);
        curr = (curr + 1) % (queue->max_size + 1);
    }
}

void array_queue_of_<typename>_destroy(array_queue_of_<typename>* queue)
{
    queue->clear(queue);
    free(queue->elements);
    free(queue);
}

void array_queue_of_<typename>_destroy_data_default(<typename> data) {}

array_queue_of_<typename>* array_queue_of_<typename>_create(size_t max_size)
{
    // We allocate an extra slot so queue->head != queue->tail unless
    // the queue is empty. This makes iterating the queue much easier.
    <typename>* elements = malloc(sizeof(<typename>) * (max_size + 1));
    if (NULL == elements) {
        return NULL;
    }

    array_queue_of_<typename>* queue = malloc(sizeof(array_queue_of_<typename>));
    if (NULL == queue) {
        free(elements);
        return NULL;
    }

    queue->max_size = max_size;
    queue->size     = 0;
    queue->head     = 0;
    queue->tail     = 0;
    queue->elements = elements;

    queue->dequeue  = &array_queue_of_<typename>_dequeue;
    queue->enqueue  = &array_queue_of_<typename>_enqueue;
    queue->clear    = &array_queue_of_<typename>_clear;
    queue->destroy  = &array_queue_of_<typename>_destroy;

    queue->destroy_data = &array_queue_of_<typename>_destroy_data_default;

    return queue;
}
