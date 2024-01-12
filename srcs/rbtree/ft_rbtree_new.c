#include <ft_rbtree.h>

/**
 * @brief Creates a new red-black tree.
 *
 * @param value_size the size of the value to store in the tree
 * @param cmp the function to compare two values
 * @return ft_rbtree_t* the new tree or NULL if an error occurred
 */
ft_rbtree_t *ft_rbtree_new(size_t value_size, void *cmp)
{
	ft_rbtree_t *tree = malloc(sizeof(ft_rbtree_t));
	if (tree == NULL)
		return NULL;
	tree->root = NULL;
	tree->value_size = value_size;
	tree->cmp = (cmp_f)cmp;
	tree->node_count = 0;
	return tree;
}
