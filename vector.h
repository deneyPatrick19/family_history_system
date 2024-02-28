#pragma once
#include<string.h>

struct student {
    char name[20];
    char number[20];
};
typedef student T;
typedef struct vector {
    T *elements;
    int capacity;
    int size;
}Vector;

enum variant { initSize = 0, initcpacity = 4 };

Vector *new_vector();
void vector_push_back(Vector *v, const T *t);
T vector_pop_back(Vector *v);
bool Vector_at(Vector *v,T *ret, int i);
void Vector_insert(Vector *v, const T *t,int i);
void Vector_delete(Vector *v, const T *t);
