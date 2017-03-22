#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chaining.h"

int cnt = 0;

void htbl_init(hash_table *table, int n) {
       table->size = n; 
       table->hash = 0;

       table->h = malloc(sizeof(hash_entry*) * n);
       for(int i = 0; i< n; i++) {
               table->h[i] = NULL;
       }
}

// htbl_find search for key
// if not found returns NULL
int* htbl_find(hash_table *table, int key) {
        int i = (int)key % table->size;
        if (i<0) {
                i += table->size;
        }

        hash_entry *curr = table->h[i];

        while(curr != NULL) {
                if (curr->key == key) {
                        return &(curr->data);
                }
                curr = curr->next_entry;
        }

        return NULL;
}

// htbl_find_or_create search for a key
// if there is no such key, then it creates
int* htbl_find_or_create(hash_table *table, int key) {
        int i = (int)key % table->size;
        if (i<0) {
                i += table->size;
        }

        hash_entry *curr = table->h[i];

        while(curr != NULL) {
                if (curr->key == key) {
                        return &(curr->data);
                }
                curr = curr->next_entry;
        }

        curr = malloc(sizeof(hash_entry*));
        cnt++;
        curr->key = key;
        curr->data = 0;
        curr->next_entry = table->h[i];
        table->h[i] = curr;

        return &(curr->data);
}

int main(int argc, char **argv) {
        srand(time(NULL));

        hash_table *htbl = (hash_table*)malloc(sizeof(hash_table));
        htbl_init(htbl, 250);
        

        int key = 123345;
        for(int i = 0; i < 100000; i++) {
                int* v = htbl_find_or_create(htbl, key++);
                char *ch = "malafya";
                *(v) = (int)ch;
        }
        printf("cnt: %d \n", cnt);
        return 0;
}
