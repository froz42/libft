#include <ft_rbtree.h>

/**
 * @brief Destroys a red-black tree and its nodes and calls a function on each node's value.
 *
 * @param tree the tree to destroy
 * @param f the function to call on each node's value
 */
void ft_rbtree_destroy_foreach(ft_rbtree_t *tree, void *f)
{
	if (tree == NULL)
		return;
	ft_rbtree_node_t *buff_root = tree->root;
	while (buff_root != NULL)
	{
		if (buff_root->left != NULL)
		{
			ft_rbtree_node_t *left = buff_root->left;
			buff_root->left = NULL;
			buff_root = left;
		}
		else if (buff_root->right != NULL)
		{
			ft_rbtree_node_t *right = buff_root->right;
			buff_root->right = NULL;
			buff_root = right;
		}
		else
		{
			if (f != NULL)
				((foreach_f)f)(buff_root->variable_value);
			ft_rbtree_node_t *parent = buff_root->parent;
			free(buff_root);
			buff_root = parent;
		}
	}
	free(tree);
}

/**
 * @brief Destroys a red-black tree and its nodes.
 *
 * @param tree the tree to destroy
 */
void ft_rbtree_destroy(ft_rbtree_t *tree)
{
	ft_rbtree_destroy_foreach(tree, NULL);
}
