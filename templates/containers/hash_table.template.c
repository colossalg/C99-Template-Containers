bool dict_of_<key_type>_and_<val_type>_insert(
    dict_of_<key_type>_and_<val_type>* dict,
    const <key_type> key,
    <val_type> val
) {
    size_t hash = dict->hash_func(key) % dict->num_slots;

    if (NULL == dict->slots[hash]) {
        list_of_pair_of_<key_type>_and_<val_type>* new_slot_list
            = list_of_pair_of_<key_type>_and_<val_type>_create();
        if (NULL == new_slot_list) {
            return false;
        }
        new_slot_list->destroy_data = dict->destroy_data;

        dict->slots[hash] = new_slot_list;
    }
   
    list_of_pair_of_<key_type>_and_<val_type>* slot_list = dict->slots[hash];
    list_of_pair_of_<key_type>_and_<val_type>_item* item = slot_list->head;
    while (item != NULL) {
        if (dict->comparator(key, item->data.value_1)) {
            break;
        }
        item = item->next;
    }

    if (NULL == item) {
        pair_of_<key_type>_and_<val_type> pair;
        pair.value_1 = key;
        pair.value_2 = val;
        slot_list->insert_at_tail(slot_list, pair);
    } else {
        item->data.value_2 = val;
    }

    return true;
}

void dict_of_<key_type>_and_<val_type>_remove(
    dict_of_<key_type>_and_<val_type>* dict,
    const <key_type> key,
    bool destroy
) {
    size_t hash = dict->hash_func(key) % dict->num_slots;

    list_of_pair_of_<key_type>_and_<val_type>* slot_list = dict->slots[hash];
    list_of_pair_of_<key_type>_and_<val_type>_item* item = slot_list->head;
    while (item != NULL) {
        if (dict->comparator(key, item->data.value_1)) {
            slot_list->remove(item, destroy);
            break;
        }
        item = item->next;
    }
}

optional_pair_of_<key_type>_and_<val_type> dict_of_<key_type>_and_<val_type>_find(
    dict_of_<key_type>_and_<val_type>* dict,
    const <key_type> key
) {
    optional_pair_of_<key_type>_and_<val_type> result;
    result.has_value = false;

    size_t hash = dict->hash_func(key) % dict->num_slots;

    list_of_pair_of_<key_type>_and_<val_type>* slot_list = dict->slots[hash];
    list_of_pair_of_<key_type>_and_<val_type>_item* item = slot_list->head;
    while (item != NULL) {
        if (dict->comparator(key, item->data.value_1)) {
            result.has_value    = true;
            result.value        = item->data;
            break;
        }
        item = item->next;
    }

    return result;
}

void dict_of_<key_type>_and_<val_type>_clear(dict_of_<key_type>_and_<val_type>* dict)
{
    for (size_t i = 0; i < dict->num_slots; ++i) {
        dict->slots[i]->clear(dict->slots[i]);
    }
}

void dict_of_<key_type>_and_<val_type>_destroy(dict_of_<key_type>_and_<val_type>* dict)
{
    for (size_t i = 0; i < dict->num_slots; ++i) {
        dict->slots[i]->destroy(dict->slots[i]);
    }
    free(dict->slots);
    free(dict);
}

dict_of_<key_type>_and_<val_type>* dict_of_<key_type>_and_<val_type>_create(
    size_t num_slots,
    size_t  (*hash_func)    (const <key_type> key),
    bool    (*comparator)   (const <key_type> key_1, const <key_type> key_2),
    void    (*destroy_data) (pair_of_<key_type>_and_<val_type> item)
)
{
    list_of_pair_of_<key_type>_and_<val_type>** slots 
        = calloc(num_slots, sizeof(list_of_pair_of_<key_type>_and_<val_type>*));
    if (NULL == slots) {
        return NULL;
    }

    dict_of_<key_type>_and_<val_type>* dict = malloc(sizeof(dict_of_<key_type>_and_<val_type>));
    if (NULL == dict) {
        free(slots);
        return NULL;
    }

    dict->num_slots = num_slots;
    dict->slots     = slots;

    dict->insert    = &dict_of_<key_type>_and_<val_type>_insert;
    dict->remove    = &dict_of_<key_type>_and_<val_type>_remove;
    dict->find      = &dict_of_<key_type>_and_<val_type>_find;
    dict->clear     = &dict_of_<key_type>_and_<val_type>_clear;
    dict->destroy   = &dict_of_<key_type>_and_<val_type>_destroy;

    dict->hash_func     = hash_func;
    dict->comparator    = comparator;
    dict->destroy_data  = destroy_data;

    return dict;
}