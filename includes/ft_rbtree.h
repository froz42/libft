#ifndef FT_RBTREE_H
#define FT_RBTREE_H

#include <stdlib.h>

typedef int (*cmp_f)(const void *, const void *);
typedef void (*foreach_f)(void *);
typedef void (*foreach_arg_f)(void *, void *);

typedef struct ft_rbtree_node_s
{
	struct ft_rbtree_node_s *parent;
	struct ft_rbtree_node_s *left;
	struct ft_rbtree_node_s *right;
	int color;
	char variable_value[];
} ft_rbtree_node_t;

#define ACCESS_VALUE(node, type) (*((type *)node->variable_value))

typedef struct
{
	ft_rbtree_node_t *root;
	size_t value_size;
	size_t node_count;
	cmp_f cmp;
} ft_rbtree_t;

#define RBT_RED 1
#define RBT_BLACK 0

/**
 * @brief Creates a new red-black tree.
 *
 * @param value_size the size of the value to store in the tree
 * @param cmp the function to compare two values
 * @return ft_rbtree_t* the new tree or NULL if an error occurred
 */
ft_rbtree_t *ft_rbtree_new(size_t value_size, void *cmp);

/**
 * @brief Insert a node into the red-black tree.
 *
 * @param tree the tree to insert into
 * @param value the value to insert
 * @return ft_rbtree_node_t* the new node or NULL if an error occurred
 */
ft_rbtree_node_t *ft_rbtree_insert(ft_rbtree_t *tree, void *value);

/**
 * @brief Destroys a red-black tree and its nodes and calls a function on each node's value.
 *
 * @param tree the tree to destroy
 * @param f the function to call on each node's value
 */
void ft_rbtree_destroy_foreach(ft_rbtree_t *tree, void *f);

/**
 * @brief Destroys a red-black tree and its nodes.
 *
 * @param tree the tree to destroy
 */
void ft_rbtree_destroy(ft_rbtree_t *tree);

/**
 * @brief Searches a red-black tree for a value.
 *
 * @param tree the tree to search
 * @param value_to_match the value to search for
 * @return ft_rbtree_node_t* the node containing the value or NULL if not found
 */
ft_rbtree_node_t *ft_rbtree_search(ft_rbtree_t *tree, void *value_to_match);

/**
 * @brief Frees a red-black tree node and its value. And fixes the tree.
 *
 * @param tree the tree to delete from
 * @param to_delete the node to delete
 */
void ft_rbtree_delete(ft_rbtree_t *tree, ft_rbtree_node_t *to_delete);

/**
 * @brief Applies a function to each node's value in a red-black tree.
 *
 * @param tree the tree to iterate over
 * @param f the function to apply to each node's value
 */
void ft_rbtree_foreach(ft_rbtree_t *tree, void *f);

/**
 * @brief Applies a function to each node's value in a red-black tree.
 *
 * @param tree the tree to iterate over
 * @param f the function to apply to each node's value with an argument
 * @param arg an argument to pass to the function
 */
void ft_rbtree_foreach_arg(ft_rbtree_t *tree, void *f, void *arg);

#endif