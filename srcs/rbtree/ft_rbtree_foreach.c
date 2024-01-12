#include <ft_rbtree.h>

static ft_rbtree_node_t *ft_rbtree_next(ft_rbtree_node_t *node)
{
	if (node->right != NULL)
	{
		node = node->right;
		while (node->left != NULL)
			node = node->left;
		return (node);
	}

	ft_rbtree_node_t *parent = node->parent;
	while (parent != NULL && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}
	return (parent);
}

/**
 * @brief Applies a function to each node's value in a red-black tree.
 *
 * @param tree the tree to iterate over
 * @param f the function to apply to each node's value
 */
void ft_rbtree_foreach(ft_rbtree_t *tree, void *f)
{
	if (tree == NULL || tree->root == NULL)
		return;

	ft_rbtree_node_t *node = tree->root;
	while (node->left != NULL)
		node = node->left;
	while (node != NULL)
	{
		((foreach_f)f)(node->variable_value);
		node = ft_rbtree_next(node);
	}
}

/**
 * @brief Applies a function to each node's value in a red-black tree.
 *
 * @param tree the tree to iterate over
 * @param f the function to apply to each node's value with an argument
 * @param arg an argument to pass to the function
 */
void ft_rbtree_foreach_arg(ft_rbtree_t *tree, void *f, void *arg)
{
	if (tree == NULL || tree->root == NULL)
		return;

	ft_rbtree_node_t *node = tree->root;
	while (node->left != NULL)
		node = node->left;
	while (node != NULL)
	{
		((foreach_arg_f)f)(node->variable_value, arg);
		node = ft_rbtree_next(node);
	}
}