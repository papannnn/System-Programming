#include "dll.hpp"
#include <stdlib.h>
#include <iostream>

void glueDLLInit(GlueDLL *list, unsigned int offset) {
    list->head = nullptr;
    list->offset = offset;
}

void glueDLLAdd(GlueDLL *list, GlueNodeDLL *curr) {
    if (list == nullptr) {
        return;
    }
    
    if (curr == nullptr) {
        std::cout << "HELLO" << std::endl;
        return;
    }

    curr->left = nullptr;
    curr->right = nullptr;
    if (list->head == nullptr) {
        list->head = curr;
        return;
    }

    list->head->left = curr;
    curr->right = list->head;
    list->head = curr;
}

void glueDLLRemove(GlueDLL *list, GlueNodeDLL *curr) {
    if (list == nullptr) {
        return;
    }

    if (curr == nullptr) {
        return;
    }

    if (curr == list->head) {
        list->head = curr->right;
        return;
    }

    if (curr->left != nullptr) {
        curr->left->right = curr->right;
    }

    if (curr->right != nullptr) {
        curr->right->left = curr->left;
    }
    curr->left = nullptr;
    curr->right = nullptr;
}

void glueDLLNodeInit(GlueNodeDLL *node) {
    node->left = nullptr;
    node->right = nullptr;
}

void glueDLLForEach(GlueDLL *list, void (*callback) (void* data)) {
    if (list == nullptr) {
        return;
    }

    GlueNodeDLL *curr = list->head;
    while (curr != nullptr) {
        void *ptr = reinterpret_cast<char*>(curr) - list->offset;
        callback(ptr);
        curr = curr->right;
    }
}