#include "dll.hpp"
#include <stdlib.h>

int remove_data_from_dll_by_data_ptr(dll_ *dll, void *app_data) {
    if (dll == nullptr || app_data == nullptr) {
        return -1;
    }

    if (dll->head == nullptr) {
        return -1;
    }

    if (dll->head->data == app_data) {
        dll_node_ *head = dll->head;
        dll->head = dll->head->right;
        if (dll->head != nullptr) {
            dll->head->left = nullptr;
        }
        
        free(head);
        return 0;
    }

    dll_node_ *curr = dll->head;
    while (curr != nullptr) {
        if (curr->data == app_data) {
            break;
        }
        curr = curr->right;
    }

    if (curr == nullptr) {
        return -1;
    }

    curr->left->right = curr->right;
    if (curr->right != nullptr) {
        curr->right->left = curr->left;
    }
    free(curr);
    return 0;
}

int is_dll_empty(dll_ *dll) {
    if (dll == nullptr) {
        return 0;
    }

    if (dll->head == nullptr) {
        return -1;
    }

    return 0;
}

void drain_dll(dll_ *dll) {
    if (dll == nullptr) {
        return;
    }

    dll_node_ *curr = dll->head;
    while (curr != nullptr) {
        dll_node_ *next = curr->right;
        free(curr);
        curr = next;
    }
    dll->head = nullptr;
}

void register_key_match_callback(dll_ *dll, int (*keymatch) (void * , void *)) {
    dll->keymatch = keymatch;
}

void* dll_search_by_key(dll_ *dll, void *key) {
    if (dll == nullptr || dll->keymatch == nullptr || dll->head == nullptr) {
        return nullptr;
    }

    dll_node_ *curr = dll->head;
    while (curr != nullptr) {
        int found = dll->keymatch(curr->data, key);
        if (found) {
            return curr->data;
        }
        curr = curr->right;
    }
    return nullptr;
}

void register_comparison_callback(dll_ *dll, int (*comparison_fn) (void*, void*)) {
    dll->comparison_fn = comparison_fn;
}

int dll_priority_insert_data(dll_ *dll, void *data) {
    if (dll == nullptr || dll->comparison_fn == nullptr || data == nullptr) {
        return -1;
    }

    dll_node_ *curr = reinterpret_cast<dll_node_*>(malloc(sizeof(dll_node_)));
    curr->data = data;
    curr->left = nullptr;
    curr->right = nullptr;

    // No data
    if (dll->head == nullptr) {
        dll->head = curr;
        return 0;
    }

    // 1 data only
    if (dll->head != nullptr && dll->head->right == nullptr) {
        // Insert head
        if (dll->comparison_fn(data, dll->head->data) == -1) {
            dll->head->left = curr;
            curr->right = dll->head;
            dll->head = curr;
        } else {
            dll->head->right = curr;
            curr->left = dll->head;
        }
        return 0;
    }

    if (dll->comparison_fn(data, dll->head->data) == -1) {
        dll->head->left = curr;
        curr->right = dll->head;
        dll->head = curr;
        return 0;
    }

    dll_node_ *prev = dll->head;
    while (prev->right != nullptr) {
        if (dll->comparison_fn(data, prev->right->data) == -1) {
            curr->left = prev;
            curr->right = prev->right;
            prev->right->left = curr;
            prev->right = curr;
            return 0;
        }
        prev = prev->right;
    }

    prev->right = curr;
    curr->left = prev;
    return 0;
}