struct dict_of_<key_type>_and_<val_type>;

typedef struct dict_of_<key_type>_and_<val_type> dict_of_<key_type>_and_<val_type>;

struct dict_of_<key_type>_and_<val_type> {
    size_t num_slots;
    list_of_pair_of_<key_type>_and_<val_type>** slots;

    bool (*insert) (dict_of_<key_type>_and_<val_type>* dict, const <key_type> key, <val_type> val);
    void (*remove) (dict_of_<key_type>_and_<val_type>* dict, const <key_type> key, bool destroy);
    optional_pair_of_<key_type>_and_<val_type> (*find) (dict_of_<key_type>_and_<val_type>* dict, const <key_type> key);
    void (*clear)  (dict_of_<key_type>_and_<val_type>* dict);
    void (*destroy)(dict_of_<key_type>_and_<val_type>* dict);

    size_t  (*hash_func)    (const <key_type> key);
    bool    (*comparator)   (const <key_type> key_1, const <key_type> key_2);
    void    (*destroy_data) (pair_of_<key_type>_and_<val_type> slot_item);
};

dict_of_<key_type>_and_<val_type>* dict_of_<key_type>_and_<val_type>_create(
    size_t num_slots,
    size_t  (*hash_func)    (const <key_type> key),
    bool    (*comparator)   (const <key_type> key_1, const <key_type> key_2),
    void    (*destroy_data) (pair_of_<key_type>_and_<val_type> slot_item)
);