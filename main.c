#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

//Vector implementation

typedef struct vector {
    int size;
    int count;
    char *array;
} vector;

int count_vector(vector *v) {
    return v->count;
}

char vector_get(vector *v, int index) {
    assert(index < v->count);
    return v->array[index];
}

void vector_add(vector *v, char c) {
    if (v->size == 0) {
        v->size = 10;
        v->array = malloc(sizeof(char) * v->size);
    }

    if (v->size == v->count) {
        v->size *= 2;
        v->array = realloc(v->array, sizeof(char) * v->size);
    }

    v->array[v->count] = c;
    v->count++;
}

void init_vector(vector *v) {
    v->array = NULL;
    v->count = 0;
    v->size = 0;
}

void free_vector(vector *v) {
    free(v->array);
}

typedef struct v_vector {
    int size;
    int count;
    vector *array;
} v_vector;

int count_v_vector(v_vector *v) {
    return v->count;
}

vector v_vector_get(v_vector *v, int index) {
    assert(index < v->count);
    return v->array[index];
}

void v_vector_add(v_vector *v, vector c) {
    if (v->size == 0) {
        v->size = 10;
        v->array = malloc(sizeof(vector) * v->size);
    }

    if (v->size == v->count) {
        v->size *= 2;
        v->array = realloc(v->array, sizeof(vector) * v->size);
    }

    v->array[v->count] = c;
    v->count++;
}

void init_v_vector(v_vector *v) {
    v->array = NULL;
    v->count = 0;
    v->size = 0;
}

void free_v_vector(v_vector *v) {
    for (int i = 0; i < v->count; ++i)free_vector(&(v->array[i]));
    free(v->array);
}

//Function returning line of input

vector Read_Line() {
    vector line;
    init_vector(&line);
    char c = getchar();
    while (c != '\n') {
        vector_add(&line, c);
        c = getchar();
    }
    return line;
}

v_vector Sort_Vector(int size, v_vector *v){
    int Bool_Tab[v->count];
    for(int i = 0; i < v->count; ++i)Bool_Tab[i] = 0;
    v_vector Sorted;
    init_v_vector(&Sorted);
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < v->count; ++j){
            if(v->array[j].array[i] != '_' && Bool_Tab[j] == 0){
                v_vector_add(&Sorted, v->array[j]);
                Bool_Tab[j] = 1;
            }
        }
    }
    return Sorted;
}

//Function printing cover according to filter

void print(v_vector cov, vector flt) {
    for (int k = 0; k < flt.count; ++k) {
        for (int i = 0; i < cov.count; ++i) {
            if (flt.array[k] == '+' && cov.array[i].array[k] != '_')putchar(cov.array[i].array[k]);
        }
    }
    putchar('\n');
}

//Function determining if

int is_valid(int *tab, vector v){
    for(int i = 0; i < v.count; ++i){
        if(v.array[i] != '_' && tab[i] == 1)return 0;
    }
    return 1;
}

//Function updating mask which is array of 0s and 1s, where 1 on i-th cell means that our current cover already has there element

void Mask_update(int *tab, vector v){
    for(int i = 0; i < v.count; ++i){
        if(v.array[i] != '_')tab[i] = 1;
    }
}

void Mask_unupdate(int *tab, vector v){
    for(int i = 0; i < v.count; ++i){
        if(v.array[i] != '_')tab[i] = 0;
    }
}

//Function counting elements of line not equal '_'

int count_elements(vector v){
    int count = 0;
    for(int i = 0; i < v.count; ++i){
        if(v.array[i] != '_')count++;
    }
    return count;
}

//Recursive function returning exact covers

void Validate(int counter, int *mask, int column, v_vector rows, v_vector cover, vector filter){
    if(counter == 0)print(cover, filter);
    else{
        if(mask[column] == 1)Validate(counter, mask, column + 1, rows, cover, filter);
        else{
            for(int i = 0; i < rows.count; ++i){
                if(rows.array[i].array[column] != '_' && is_valid(mask, rows.array[i])) {
                    v_vector_add(&cover, rows.array[i]);
                    counter -= count_elements(rows.array[i]);
                    Mask_update(mask, rows.array[i]);
                    Validate(counter, mask, column, rows, cover, filter);
                    counter += count_elements(rows.array[i]);
                    cover.count--;
                    Mask_unupdate(mask, rows.array[i]);
                }
            }
        }
    }
}

int main() {
    vector filter;
    filter = Read_Line();
    v_vector Rows;
    init_v_vector(&Rows);
    char c = getchar();
    while (c != EOF) {
        ungetc(c, stdin);
        vector r = Read_Line();
        v_vector_add(&Rows, r);
        c = getchar();
    }
    Rows = Sort_Vector(filter.size, &Rows);
    v_vector Cover;
    init_v_vector(&Cover);
    int Mask[filter.count];
    for(int i = 0; i < filter.count; ++i)Mask[i] = 0;
    Validate(filter.count, Mask, 0, Rows, Cover, filter);
    free_v_vector(&Rows);
    free_vector(&filter);
    return 0;
}
