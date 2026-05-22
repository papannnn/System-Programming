struct dll_node_ {
    void* data;
    struct dll_node_ *left;
    struct dll_node_ *right;
};

struct dll_ {
    dll_node_ *head;
    int (*keymatch) (void*, void*);
    int (*comparison_fn) (void*, void*);
};

dll_* get_new_dll();

int add_data_to_dll(dll_ *dll, void *app_data);

int remove_data_from_dll_by_data_ptr(dll_ *dll, void *app_data);

int is_dll_empty(dll_ *dll);

void drain_dll(dll_ *dll);

void register_key_match_callback(dll_ *dll, int (*) (void *, void *));

void* dll_search_by_key(dll_ *dll, void *key);

void register_comparison_callback(dll_ *dll, int (*) (void*, void*));

int dll_priority_insert_data(dll_ *dll, void *data);