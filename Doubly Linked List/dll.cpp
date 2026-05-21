#include "dll.hpp"
#include <stdlib.h>

dll_ *get_new_dll() {
    dll_ *dll = reinterpret_cast<dll_*>(malloc(sizeof(dll_)));
    dll->head = NULL;
    return dll;
}

int add_data_to_dll(dll_ *dll, void *app_data) {
    if (!dll || !app_data) {
        return -1;
    }

    dll_node_ *node = reinterpret_cast<dll_node_*>(malloc(sizeof(dll_node_)));
    node->data = app_data;
    node->left = nullptr;
    node->right = nullptr;

    if (dll->head == nullptr) {
        dll->head = node;
        return 0;
    }

    dll->head->left = node;
    node->right = dll->head;
    dll->head = node;
    return 0;
}