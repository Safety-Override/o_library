/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_avl_set.h"
#include "o_avl_set_private.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "o_functions.h"

static void* node_get_key(o_avl_set_t* set, o_avl_set_node_t* node) {
    return (char*)node + set->offsetof_key;
}

static unsigned char height(o_avl_set_node_t* node) {
    return node ? node->height : 0;
}

static int bfactor(o_avl_set_node_t* node) {
    return (int)height(node->right) - (int)height(node->left);
}

static void fix_height(o_avl_set_node_t* node) {
    unsigned char left_height = height(node->left);
    unsigned char right_height = height(node->right);
    node->height = (left_height > right_height ? right_height : left_height) + 1;
}

static o_avl_set_node_t* rotate_right(o_avl_set_node_t* p_node) {
    o_avl_set_node_t* q_node = p_node->left;
    q_node->parent = p_node->parent;
    p_node->left = q_node->right;
    if (p_node->left) {
        p_node->left->parent = p_node;
    }
    q_node->right = p_node;
    q_node->right->parent = q_node;
    fix_height(p_node);
    fix_height(q_node);
    return q_node;
}

static o_avl_set_node_t* rotate_left(o_avl_set_node_t* q_node) {
    o_avl_set_node_t* p_node = q_node->right;
    p_node->parent = q_node->parent;
    q_node->right = p_node->left;
    if (q_node->right) {
        q_node->right->parent = q_node;
    }
    p_node->left = q_node;
    p_node->left->parent = p_node;
    fix_height(q_node);
    fix_height(p_node);
    return p_node;
}

static o_avl_set_node_t* balance(o_avl_set_node_t* node) {
    fix_height(node);
    if (bfactor(node) == 2)
    {
        if (bfactor(node->right) < 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }
    if (bfactor(node) == -2)
    {
        if (bfactor(node->left) > 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }
    return node;
}

static o_avl_set_node_t* create_node_from_key(o_avl_set_t* set, o_avl_set_node_t* parent, const void* key) {
    o_avl_set_node_t* node = calloc(1, set->node_size);
    node->parent = parent;
    memcpy(node_get_key(set, node), key, set->sizeof_key);
    fix_height(node);
    return node;
}

static o_avl_set_node_t* insert(o_avl_set_t* set, o_avl_set_node_t* node, const void* key, o_avl_set_insert_result_t* result) {
    if (!node) {
        set->size += 1;
        *result = (o_avl_set_insert_result_t){.node = create_node_from_key(set, node, key), .insertion_took_place = true};
        return result->node;
    }
    int key_compare_result = set->key_cmp(key, o_avl_set_node_get_key(set, node));
    if (key_compare_result < 0) {
        node->left = insert(set, node->left, key, result);
    } else if (key_compare_result > 0) {
        node->right = insert(set, node->right, key, result);
    } else {
        *result = (o_avl_set_insert_result_t){.node = node, .insertion_took_place = false};
        return result->node;
    }
    return balance(node);
}

static o_avl_set_node_t* find_min_node(o_avl_set_node_t* node) {
    return node->left ? find_min_node(node->left) : node;
}

static o_avl_set_node_t* remove_min_node(o_avl_set_node_t* node) {
    if (!node->left) {
        return node->right;
    }
    node->left = remove_min_node(node->left);
    if (node->left) {
        node->left->parent = node;
    }
    return balance(node);
}

static o_avl_set_node_t* erase(o_avl_set_t* set, o_avl_set_node_t* node, const void* key) {
    if (!node) {
        return NULL;
    }
    int key_compare_result = set->key_cmp(key, o_avl_set_node_get_key(set, node));
    if (key_compare_result < 0) {
        node->left = erase(set, node->left, key);
    } else if (key_compare_result > 0) {
        node->right = erase(set, node->right, key);	
    } else {
        o_avl_set_node_t* parent = node->parent;
        o_avl_set_node_t* left = node->left;
        o_avl_set_node_t* right = node->right;
        free(node);
        set->size -= 1;
        if (!right) {
            if (left) {
                left->parent = parent;
            }
            return left;
        }
        node = find_min_node(right);
        node->parent = parent;
        node->right = remove_min_node(right);
        if (node->right) {
            node->right->parent = node;
        }
        node->left = left;
        if (node->left) {
            node->left->parent = node;
        }
    }
    return balance(node);
}

o_avl_set_t* o_avl_set_create_f(o_compare_func_t key_cmp, size_t node_size, size_t offsetof_key, size_t sizeof_key) {
    o_avl_set_t* set = calloc(1, sizeof(o_avl_set_t));
    set->key_cmp = key_cmp;
    set->size = 0;
    set->node_size = node_size;
    set->offsetof_key = offsetof_key;
    set->sizeof_key = sizeof_key;
    return set;
}

bool o_avl_set_empty(const o_avl_set_t* set) {
    return !set->size;
}

void o_avl_set_clear(o_avl_set_t* set) {
    o_avl_set_node_t* current_node = set->root;
    while (current_node != NULL) {
        while (current_node->left) {
            current_node = current_node->left;
        }
        while (current_node->right) {
            current_node = current_node->right;
        }
        o_avl_set_node_t* parent_node = current_node->parent;
        free(current_node);
        current_node = parent_node;
    }
    set->root = NULL;
    set->size = 0;
}

o_avl_set_insert_result_t o_avl_set_insert(o_avl_set_t* set, const void* key) {
    o_avl_set_insert_result_t result;
    set->root = insert(set, set->root, key, &result);
    return result;
}

void o_avl_set_erase(o_avl_set_t* set, const void* key) {
    set->root = erase(set, set->root, key);
}

void o_avl_set_delete(o_avl_set_t* set) {
    o_avl_set_clear(set);
    free(set);
}

void o_avl_set_swap(o_avl_set_t* first_set, o_avl_set_t* second_set) {
    o_swap(*first_set, *second_set);
}

o_avl_set_node_t* o_avl_set_find(o_avl_set_t* set, const void* key) {
    o_avl_set_node_t* current_node = set->root;
    while (current_node != NULL) {
        int key_compare_result = set->key_cmp(key, o_avl_set_node_get_key(set, current_node));
        if (key_compare_result < 0) {
            current_node = current_node->left;
        } else if (key_compare_result > 0) {
            current_node = current_node->right;
        } else {
            return current_node;
        }
    }
    return NULL;
}

bool o_avl_set_contains(const o_avl_set_t* set, const void* key) {
    return o_avl_set_find((o_avl_set_t*)set, key) != o_avl_set_cend(set);
}

o_avl_set_node_t* o_avl_set_lower_bound(o_avl_set_t* set, const void* key) {
    o_avl_set_node_t* current_node = set->root;
    o_avl_set_node_t* parent_node = o_avl_set_end(set);
    while (current_node) {
        parent_node = current_node;
        int key_compare_result = set->key_cmp(key, o_avl_set_node_get_key(set, current_node));
        if (key_compare_result < 0) {
            current_node = current_node->left;
        } else if (key_compare_result > 0) {
            current_node = current_node->right;
        } else {
            return current_node;
        }
    }
    if (!parent_node) {
        return o_avl_set_end(set);
    }
    int key_compare_result = set->key_cmp(key, o_avl_set_node_get_key(set, parent_node));
    if (key_compare_result < 0) {
        return parent_node;
    }
    return o_avl_set_node_get_next(set, parent_node);
}

o_avl_set_node_t* o_avl_set_upper_bound(o_avl_set_t* set, const void* key) {
    o_avl_set_node_t* current_node = set->root;
    o_avl_set_node_t* parent_node = o_avl_set_end(set);
    while (current_node) {
        parent_node = current_node;
        int key_compare_result = set->key_cmp(key, o_avl_set_node_get_key(set, current_node));
        if (key_compare_result < 0) {
            current_node = current_node->left;
        } else if (key_compare_result > 0) {
            current_node = current_node->right;
        } else {
            return o_avl_set_node_get_next(set, current_node);
        }
    }
    if (!parent_node) {
        return o_avl_set_end(set);
    }
    int key_compare_result = set->key_cmp(key, o_avl_set_node_get_key(set, parent_node));
    if (key_compare_result < 0) {
        return parent_node;
    }
    return o_avl_set_node_get_next(set, parent_node);
}

o_avl_set_node_t* o_avl_set_begin(o_avl_set_t* set) {
    return set->root ? find_min_node(set->root) : NULL;
}

o_avl_set_node_t* o_avl_set_end(o_avl_set_t* set) {
    return NULL;
}

const o_avl_set_node_t* o_avl_set_cbegin(const o_avl_set_t* set) {
    return o_avl_set_begin((o_avl_set_t*)set);
}

const o_avl_set_node_t* o_avl_set_cend(const o_avl_set_t* set) {
    return o_avl_set_end((o_avl_set_t*)set);
}

o_avl_set_node_t* o_avl_set_node_get_next(o_avl_set_t* set, o_avl_set_node_t* node) {
    if (node->parent && node->parent->left == node) {
        return node->parent;
    } 
    return node->right ? find_min_node(node->right) : NULL;
}

const o_avl_set_node_t* o_avl_set_cnode_get_next(const o_avl_set_t* set, const o_avl_set_node_t* node) {
    return o_avl_set_node_get_next((o_avl_set_t*)set, (o_avl_set_node_t*)node);
}

const void* o_avl_set_node_get_key(const o_avl_set_t* set, const o_avl_set_node_t* node) {
    return node_get_key((o_avl_set_t*)set, (o_avl_set_node_t*)node);
}

void o_avl_set_node_erase(o_avl_set_t* set, o_avl_set_node_t* node) {
    // TODO: erase pointer without erase call.
    const void* key = o_avl_set_node_get_key(set, node); 
    o_avl_set_erase(set, key);
}

size_t o_avl_set_size(const o_avl_set_t* set) {
    return set->size;
}