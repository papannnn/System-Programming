struct dll_node_ {
    void* data;
    struct dll_node_ *left;
    struct dll_node_ *right;
};

struct dll_ {
    dll_node_ *head;
};

dll_* get_new_dll();

int add_data_to_dll(dll_ *dll, void *app_data);