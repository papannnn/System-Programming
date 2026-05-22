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

    auto callback = [] (void *data, void *key) -> int {
        Person *person = reinterpret_cast<Person*>(data);
        int* age = reinterpret_cast<int*>(key);
        if (person->age == *age) {
            return 1;
        }
        return 0;
    };

    register_key_match_callback(dll, callback);
    std::unique_ptr<int> key(new int(80));
    void *search = dll_search_by_key(dll, key.get());
    if (search != nullptr) {
        Person *searchPerson = reinterpret_cast<Person*>(search);
        std::cout << "Searched person: " << searchPerson->name << std::endl;
    }
}