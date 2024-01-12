#include <bool_t.h>
#include <ft_rbtree.h>
#include <ft_string.h>

static ft_rbtree_node_t *left_rotate(ft_rbtree_node_t *node)
{
	ft_rbtree_node_t *parent = node->parent;
	ft_rbtree_node_t *grand_parent = parent->parent;

	parent->right = node->left;
	if (node->left != NULL)
	{
		node->left->parent = parent;
	}
	node->parent = grand_parent;
	parent->parent = node;
	node->left = parent;
	if (grand_parent != NULL)
	{
		if (grand_parent->right == parent)
			grand_parent->right = node;
		else
			grand_parent->left = node;
	}
	return node;
}

static ft_rbtree_node_t *right_rotate(ft_rbtree_node_t *node)
{
	ft_rbtree_node_t *parent = node->parent;
	ft_rbtree_node_t *grand_parent = parent->parent;

	parent->left = node->right;
	if (node->right != NULL)
		node->right->parent = parent;
	node->parent = grand_parent;
	parent->parent = node;
	node->right = parent;
	if (grand_parent != NULL)
	{
		if (grand_parent->right == parent)
			grand_parent->right = node;
		else
			grand_parent->left = node;
	}
	return node;
}

static void check_for_case2(ft_rbtree_node_t *to_delete, int delete, int fromDirection,
							ft_rbtree_node_t **root)
{
	if (to_delete == (*root))
	{
		(*root)->color = RBT_BLACK;
		return;
	}

	if (!delete &&to_delete->color == RBT_RED)
	{
		if (!fromDirection)
		{
			if (to_delete->right != NULL)
				to_delete->right->color = RBT_RED;
		}
		else
		{
			if (to_delete->left != NULL)
				to_delete->left->color = RBT_RED;
		}
		to_delete->color = RBT_BLACK;
		return;
	}

	// Get the sibling for further inspection
	ft_rbtree_node_t *sibling;
	ft_rbtree_node_t *parent = to_delete->parent;
	int locate_child = 0; // 0 if to_deleted is left of its parent else 1
	if (parent->right == to_delete)
	{
		sibling = parent->left;
		locate_child = 1;
	}
	else
		sibling = parent->right;

	// Case 2.1. i.e. if the any children of the sibling is red
	if ((sibling->right != NULL && sibling->right->color == RBT_RED) ||
		(sibling->left != NULL && sibling->left->color == RBT_RED))
	{
		if (sibling->right != NULL && sibling->right->color == RBT_RED)
		{
			if (locate_child == 1)
			{
				int par_color = parent->color;
				sibling = left_rotate(sibling->right);
				parent = right_rotate(sibling);
				if (parent->parent == NULL)
					*root = parent;
				parent->color = par_color;
				parent->left->color = RBT_BLACK;
				parent->right->color = RBT_BLACK;
				if (delete)
				{
					if (to_delete->left != NULL)
						to_delete->left->parent = parent->right;
					parent->right->right = to_delete->left;
					free(to_delete);
				}
			}
			else
			{
				int par_color = parent->color;
				parent = left_rotate(sibling);

				if (parent->parent == NULL)
					*root = parent;

				parent->color = par_color;
				parent->left->color = RBT_BLACK;
				parent->right->color = RBT_BLACK;

				if (delete)
				{
					if (to_delete->right != NULL)
						to_delete->right->parent = parent->left;
					parent->left->left = to_delete->left;
					free(to_delete);
				}
			}
		}
		else
		{
			// Sibling is right and child is left. i.e. RIGHT LEFT ROTATION
			if (locate_child == 0)
			{
				int par_color = parent->color;
				sibling = right_rotate(sibling->left);
				parent = left_rotate(sibling);
				if (parent->parent == NULL)
					*root = parent;

				parent->color = par_color;
				parent->left->color = RBT_BLACK;
				parent->right->color = RBT_BLACK;

				// Delete the node (present at parent->left->left)
				if (delete)
				{
					if (to_delete->right != NULL)
						to_delete->right->parent = parent->left;
					parent->left->left = to_delete->right;
					free(to_delete);
				}
			}
			else
			{
				int par_color = parent->color;

				parent = right_rotate(sibling);

				if (parent->parent == NULL)
					*root = parent;

				// Update Colors
				parent->color = par_color;
				parent->left->color = RBT_BLACK;
				parent->right->color = RBT_BLACK;

				// Delete the node (present at parent->right->right)
				if (delete)
				{
					if (to_delete->left != NULL)
						to_delete->left->parent = parent->right;
					parent->right->right = to_delete->left;
					free(to_delete);
				}
			}
		}
	}
	else if (sibling->color == 0)
	{
		sibling->color = RBT_RED;

		// Delete if necessary
		if (delete)
		{
			if (locate_child)
			{
				to_delete->parent->right = to_delete->left;
				if (to_delete->left != NULL)
					to_delete->left->parent = to_delete->parent;
			}
			else
			{
				to_delete->parent->left = to_delete->right;
				if (to_delete->right != NULL)
					to_delete->right->parent = to_delete->parent;
			}
			free(to_delete);
		}

		check_for_case2(parent, 0, locate_child, root);
	}
	else
	{
		if (locate_child)
		{
			to_delete->parent->right = to_delete->left;
			if (to_delete->left != NULL)
				to_delete->left->parent = to_delete->parent;

			parent = right_rotate(sibling);

			// Check if the root is rotated
			if (parent->parent == NULL)
				*root = parent;

			parent->color = RBT_BLACK;
			parent->right->color = RBT_RED;
			check_for_case2(parent->right, 0, 1, root);
		}
		else
		{ // Left Rotate

			to_delete->parent->left = to_delete->right;
			if (to_delete->right != NULL)
				to_delete->right->parent = to_delete->parent;
			parent = left_rotate(sibling);

			// Check if the root is rotated
			if (parent->parent == NULL)
				*root = parent;
			parent->color = RBT_BLACK;
			parent->left->color = RBT_RED;
			check_for_case2(parent->left, 0, 0, root);
		}
		if (delete)
			free(to_delete);
	}
}

/**
 * @brief Frees a red-black tree node and its value. And fixes the tree.
 *
 * @param tree the tree to delete from
 * @param to_delete the node to delete
 */
void ft_rbtree_delete(ft_rbtree_t *tree, ft_rbtree_node_t *to_delete)
{
	ft_rbtree_node_t *buff_root = to_delete;
	// Look for the leftmost of right node or right most of left node
	if (to_delete->left != NULL)
	{
		to_delete = to_delete->left;
		while (to_delete->right != NULL)
			to_delete = to_delete->right;
	}
	else if (to_delete->right != NULL)
	{
		to_delete = to_delete->right;
		while (to_delete->left != NULL)
			to_delete = to_delete->left;
	}

	if (to_delete == tree->root)
	{
		free(to_delete);
		tree->root = NULL;
		tree->node_count--;
		return;
	}

	ft_memcpy(buff_root->variable_value, to_delete->variable_value, tree->value_size);
	ft_memcpy(to_delete->variable_value, buff_root->variable_value, tree->value_size);

	// Checking for case 1
	if (to_delete->color == RBT_RED ||
		(to_delete->left != NULL && to_delete->left->color == RBT_RED) ||
		(to_delete->right != NULL && to_delete->right->color == RBT_RED))
	{
		// if it is a leaf
		if (to_delete->left == NULL && to_delete->right == NULL)
		{
			// Delete instantly
			if (to_delete->parent->left == to_delete)
				to_delete->parent->left = NULL;
			else
				to_delete->parent->right = NULL;
		}
		else
		{
			if (to_delete->left != NULL)
			{
				to_delete->parent->right = to_delete->left;
				to_delete->left->parent = to_delete->parent;
				to_delete->left->color = RBT_RED;
			}
			else
			{
				to_delete->parent->left = to_delete->right;
				to_delete->right->parent = to_delete->parent;
				to_delete->right->color = RBT_RED;
			}
		}

		free(to_delete);
	}
	else
		check_for_case2(to_delete, 1, ((to_delete->parent->right == to_delete)), &(tree->root));
	tree->node_count--;
}