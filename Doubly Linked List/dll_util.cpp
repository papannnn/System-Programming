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