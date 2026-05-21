#include "dll.hpp"
#include <iostream>
#include <string>

struct Person {
    std::string name;
    int age;
    int weight;

    Person(std::string name_, int age_, int weight_) : name(name_), age(age_), weight(weight_) { }
};

void traverse_dll(dll_ *dll) {
    if (dll == nullptr) {
        return;
    }

    dll_node_ *curr = dll->head;
    while (curr != nullptr) {
        Person *person = reinterpret_cast<Person*>(curr->data);
        std::cout << person->name << " " << person->age << " " << person->weight << std::endl;
        curr = curr->right;
    }
}

int main () {
    dll_ *dll = get_new_dll();

    Person *a = new Person("Pan", 26, 70);
    Person *b = new Person("Jokowi", 60, 80);
    Person *c = new Person("Prabowo", 80, 100);
    
    add_data_to_dll(dll, a);
    add_data_to_dll(dll, b);
    add_data_to_dll(dll, c);

    traverse_dll(dll);
}