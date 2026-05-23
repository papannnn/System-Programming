#include "dll.hpp"
#include <iostream>
#include <string>

struct Employee {
    std::string name;
    int age;
    GlueNodeDLL node;
};

Employee* initEmployee() {
    Employee *emp = reinterpret_cast<Employee*>(malloc(sizeof(Employee)));
    glueDLLNodeInit(&emp->node);
    return emp;
}

int main () {
    GlueDLL *list = reinterpret_cast<GlueDLL*>(malloc(sizeof(GlueDLL)));
    glueDLLInit(list, offsetof(Employee, node));

    Employee *a = initEmployee();
    a->name = "Taufan";
    a->age = 26;

    Employee *b = initEmployee();
    b->name = "Jokowi";
    b->age = 64;

    Employee *c = initEmployee();
    c->name = "Prabowo";
    c->age = 74;

    glueDLLAdd(list, &a->node);
    glueDLLAdd(list, &b->node);
    glueDLLAdd(list, &c->node);

    glueDLLForEach(list, [] (void *data) {
        Employee *emp = reinterpret_cast<Employee*>(data);
        std::cout << emp->name << " " << emp->age << std::endl;
    });

    glueDLLRemove(list, &b->node);
    glueDLLForEach(list, [] (void *data) {
        Employee *emp = reinterpret_cast<Employee*>(data);
        std::cout << emp->name << " " << emp->age << std::endl;
    });
}