dict_of_<key_type>_and_<val_type>* dict_of_<key_type>_and_<val_type>_create(
    size_t num_slots,
    size_t  (*hash_func)    (const <key_type> key),
    bool    (*comparator)   (const <val_type> val_1, const <val_type> val_2),
    void    (*destroy_data) (<val_type> val)
)
{
    return NULL;
}