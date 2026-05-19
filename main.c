#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    int size;
    int capacity;
}Vector;

void init_vector(Vector *vector){
    vector->size = 0;
    vector->capacity = 4;
    vector->items = (int*)malloc(vector->capacity * sizeof(int));

    if (vector->items == NULL) {
        printf("Memory Allocation Failed\n");
        exit(1);
    }
}

void reserve_capacity(Vector *vector){
    vector->capacity *= 2;
    int *temporary = realloc(vector->items, vector->capacity * sizeof(int));
    if (temporary == NULL) {
        printf("Reallocation Failed\n");
        exit(1);
    }
    vector->items = temporary;
}

void push_back(Vector *vector, int data){
    if (vector->size >= vector->capacity) {
        reserve_capacity(vector);
    }

    vector->items[vector->size] = data;
    vector->size++;

}

void pop_back(Vector *vector){
    if (vector->size == 0) {
        printf("Vector is Empty\n");
        return;
    }
    vector->size--;
}

void set(Vector *vector, int index, int data){
    if (index < 0 || index >= vector->size) {
        printf("Invalid Index\n");
        return;
    }
    vector->items[index] = data;
}

int get(Vector *vector, int index){
    if (index < 0 || index >= vector->size) {
        printf("Invalid Index\n");
        return -1;
    }

    return vector->items[index];

}

int front(Vector *vector){
    if (vector->size == 0) {
        printf("Vector is Empty\n");
        return -1;
    }
    return vector->items[0];
}

int back(Vector *vector){
    if (vector->size == 0) {
        printf("Vector is Empty\n");
        return -1;
    }
    return vector->items[vector->size-1];
}

int isEmpty(Vector *vector){
    if (vector->size == 0){ 
        return 1; 
    }else
    { 
        return -1;
    }
}

void delete_at_index(Vector *vector, int index) {
    if (index < 0 || index >= vector->size) {
        printf("Invalid Index\n");
        return;
    }

    for (int i = index; i < vector->size - 1; i++) {
        vector->items[i] = vector->items[i + 1];
    }
    vector->size--;
}

void insert_at_index(Vector *vector, int index, int new_element){
    if (index < 0 || index > vector->size) {
        printf("Invalid Index\n");
        return;
    }

    if (vector->size >= vector->capacity) {
        reserve_capacity(vector);
    }

    for (int i = vector->size - 1; i >= index; i--) {
        vector->items[i + 1] = vector->items[i];
    }

    vector->items[index] = new_element;
    vector->size++;
}

void clear(Vector *vector) {

    /*
       Real std::vector::clear()
       removes all elements
       but keeps capacity
    */

    vector->size = 0;
}

void display(Vector *vector){

     if (vector->size == 0) {
        printf("Vector is Empty\n");
        return;
    }

    for (int i = 0; i < vector->size; i++) {
        printf("%d \n", vector->items[i]);
    }
    printf("\n");
}

void free_vector(Vector *vector) {

    free(vector->items);

    vector->items = NULL;
    vector->size = 0;
    vector->capacity = 0;
}

int main(){
    Vector vector;

    init_vector(&vector);

    push_back(&vector, 10);
    push_back(&vector, 20);
    push_back(&vector, 30);
    push_back(&vector, 40);
    push_back(&vector, 50);

    printf("Vector Elements:\n");
    display(&vector);

    printf("Front: %d\n", front(&vector));
    printf("Back: %d\n", back(&vector));

    insert_at_index(&vector, 2, 100);

    printf("\nAfter Insert:\n");
    display(&vector);

    delete_at_index(&vector, 1);

    printf("\nAfter Delete:\n");
    display(&vector);

    set(&vector, 0, 999);

    printf("\nAfter Set:\n");
    display(&vector);

    printf("\nGet Index 2: %d\n", get(&vector, 2));

    pop_back(&vector);

    printf("\nAfter Pop:\n");
    display(&vector);

    clear(&vector);

    printf("\nAfter Clear:\n");
    display(&vector);

    printf("Size: %d\n", vector.size);
    printf("Capacity: %d\n", vector.capacity);

    free_vector(&vector);
    return 0;
}
