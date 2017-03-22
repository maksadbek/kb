typedef struct hash_entry_x hash_entry;
typedef hash_entry* hash_entry_ptr;

struct hash_entry_x {
     t   int data;
        int key;
        hash_entry_ptr next_entry;
};


typedef struct {
        int size;
        int hash;
        hash_entry_ptr *h;
} hash_table;


void htbl_init(hash_table *table, int n);
void htbl_free(hash_table *table);
int* htbl_find(hash_table *table, int key);
int* htbl_find_or_create(hash_table *table, int key);
void htbl_del(hash_table *table, int key);
