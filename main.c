#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct Person {
    char* name;
    int age;
} Person;

Person* newPerson(char* name, int age) {
    Person* p = malloc(sizeof(Person));
    p->name = name;
    p->age = age;
    return p;
}

void cleanPerson(Person* p) {
    free(p);
}

void greet(Person* personA, Person* personB) {
    printf("%s says: Hi there, %s! I'm %d years old.\n", personA->name, personB->name, personA->age);
}

int main() {
    Person* michael = newPerson("Michael", 36);
    Person* andreas = newPerson("Andreas", 33);
    Person* helena = newPerson("Helena", 16);
    Person* people[3] = {michael, andreas, helena};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != j) {
                greet(people[i], people[j]);
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        cleanPerson(people[i]);
    }

    return 0;
}