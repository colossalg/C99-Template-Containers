dict_of_<key_type>_and_<val_type>* dict_of_<key_type>_and_<val_type>_create(
    size_t num_slots,
    size_t  (*hash_func)    (const <key_type> key),
    bool    (*comparator)   (const <key_type> key_1, const <key_type> key_2),
    void    (*destroy_data) (<val_type> val)
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

    dict->hash_func     = hash_func;
    dict->comparator    = comparator;
    dict->destroy_data  = destroy_data;

    return dict;
}