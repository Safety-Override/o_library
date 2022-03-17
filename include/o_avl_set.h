#include <stddef.h>
#include "o_functions.h"

typedef struct o_avl_s o_avl_set_t;
typedef struct o_avl_node_s o_avl_set_node_t;

o_avl_set_t* o_avl_set_create_t(size_t data_type_size, o_compare_func_t data_cmp);

#define o_avl_set_create(K, data_cmp)        \
({                                          \
    o_avl_set_create_t(sizeof(K), data_cmp); \
})
 
bool o_avl_set_empty(const o_avl_set_t set);

void o_avl_set_clear(o_avl_set_t set);

void o_avl_set_insert(o_avl_set_t set, const void* data);

void o_avl_set_delete(o_avl_set_t set, void* pos);

void o_avl_set_swap(o_avl_set_t first_set, o_avl_set_t second_set);

void* o_avl_set_find(const o_avl_set_t set, const void* data);

bool o_avl_set_contains(const o_avl_set_t set, const void* data);

void* o_avl_set_lower_bound(const o_avl_set_t set, const void* data);

void* o_avl_set_upper_bound(const o_avl_set_t set, const void* data);

void o_avl_set_destroy(o_avl_set_t set);

void* o_avl_set_begin(const o_avl_set_t set);

void* o_avl_set_end(const o_avl_set_t set);

o_avl_set_node_t* o_avl_set_node_get_next(const o_avl_set_t set, o_avl_set_node_t node);

void* o_avl_set_node_get_data(const o_avl_set_t set, const o_avl_set_node_t node);

size_t o_avl_set_size(const o_avl_set_t set);