#include <ft_rbtree.h>
#include <ft_string.h>

/**
 * @brief Create a new node
 *
 * @param value the value to insert
 * @param value_size the size of the value
 * @param parent the parent of the node
 * @return ft_rbtree_node_t* the new node
 */
static ft_rbtree_node_t *new_node(void *value, size_t value_size, ft_rbtree_node_t *parent)
{
	ft_rbtree_node_t *node = malloc(sizeof(ft_rbtree_node_t) + value_size);
	if (node == NULL)
		return NULL;
	void *value_ptr = node->variable_value;
	ft_memcpy(value_ptr, value, value_size);
	node->color = RBT_RED;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return node;
}

/**
 * @brief Check the node after insertion to see if it violates any of the red-black tree properties.
 *
 * @param node The node to check.
 */
static void check_node(ft_rbtree_node_t *node)
{
	if (node == NULL || node->parent == NULL)
		return;
	ft_rbtree_node_t *child = node;

	if (node->color == RBT_BLACK || (node->parent)->color == RBT_BLACK)
		return;
	ft_rbtree_node_t *parent = node->parent;
	ft_rbtree_node_t *grand_parent = parent->parent;
	if (grand_parent == NULL)
	{
		parent->color = RBT_BLACK;
		return;
	}

	if (grand_parent->right != NULL && (grand_parent->right)->color == RBT_RED &&
		grand_parent->left != NULL && (grand_parent->left)->color == RBT_RED)
	{
		(grand_parent->right)->color = RBT_BLACK;
		(grand_parent->left)->color = RBT_BLACK;
		grand_parent->color = RBT_RED;
		return;
	}
	else
	{
		ft_rbtree_node_t *great_grand_parent = grand_parent->parent;
		if (grand_parent->right == parent)
		{
			if (parent->right == node)
			{
				grand_parent->right = parent->left;
				if (parent->left != NULL)
				{
					(parent->left)->parent = grand_parent;
				}
				parent->left = grand_parent;
				grand_parent->parent = parent;

				parent->parent = great_grand_parent;
				if (great_grand_parent != NULL)
				{
					if (great_grand_parent->left != NULL &&
						great_grand_parent->left == grand_parent)
						great_grand_parent->left = parent;
					else
						great_grand_parent->right = parent;
				}

				parent->color = RBT_BLACK;
				grand_parent->color = RBT_RED;
			}
			else
			{
				parent->left = child->right;
				if (child->right != NULL)
				{
					(child->right)->parent = parent;
				}
				child->right = parent;
				parent->parent = child;

				grand_parent->right = child->left;
				if (child->left != NULL)
				{
					(child->left)->parent = grand_parent;
				}
				child->left = grand_parent;
				grand_parent->parent = child;

				child->parent = great_grand_parent;
				if (great_grand_parent != NULL)
				{
					if (great_grand_parent->left != NULL &&
						great_grand_parent->left == grand_parent)
						great_grand_parent->left = child;
					else
						great_grand_parent->right = child;
				}

				child->color = RBT_BLACK;
				grand_parent->color = RBT_RED;
			}
		}
		else
		{
			if (parent->left == node)
			{
				grand_parent->left = parent->right;
				if (parent->right != NULL)
				{
					(parent->right)->parent = grand_parent;
				}
				parent->right = grand_parent;
				grand_parent->parent = parent;

				parent->parent = great_grand_parent;
				if (great_grand_parent != NULL)
				{
					if (great_grand_parent->left != NULL &&
						great_grand_parent->left == grand_parent)
						great_grand_parent->left = parent;
					else
						great_grand_parent->right = parent;
				}

				parent->color = RBT_BLACK;
				grand_parent->color = RBT_RED;
			}
			else
			{
				parent->right = child->left;
				if (child->left != NULL)
					(child->left)->parent = parent;
				child->left = parent;
				parent->parent = child;

				grand_parent->left = child->right;
				if (child->right != NULL)
				{
					(child->right)->parent = grand_parent;
				}
				child->right = grand_parent;
				grand_parent->parent = child;

				child->parent = great_grand_parent;
				if (great_grand_parent != NULL)
				{
					if (great_grand_parent->left != NULL &&
						great_grand_parent->left == grand_parent)
						great_grand_parent->left = child;
					else
						great_grand_parent->right = child;
				}

				child->color = RBT_BLACK;
				grand_parent->color = RBT_RED;
			}
		}
	}
}

/**
 * @brief Insert a node into the red-black tree.
 *
 * @param tree the tree to insert into
 * @param value the value to insert
 * @return ft_rbtree_node_t* the new node or NULL if an error occurred
 */
ft_rbtree_node_t *ft_rbtree_insert(ft_rbtree_t *tree, void *value)
{
	if (tree->root == NULL)
	{
		tree->root = new_node(value, tree->value_size, NULL);
		if (tree->root == NULL)
			return NULL;
		tree->root->color = RBT_BLACK;
		tree->node_count++;
		return tree->root;
	}
	ft_rbtree_node_t *buff_root = tree->root;
	ft_rbtree_node_t *to_insert = NULL;
	while (buff_root)
	{
		if (tree->cmp(value, buff_root->variable_value) < 0)
		{
			// Go left
			if (buff_root->left != NULL)
				buff_root = buff_root->left;
			else
			{
				// Insert The ft_rbtree_node_t
				to_insert = new_node(value, tree->value_size, buff_root);
				if (to_insert == NULL)
					return NULL;
				buff_root->left = to_insert;
				buff_root = to_insert;

				// Check For Double Red Problems
				break;
			}
		}
		else
		{
			// Go right
			if (buff_root->right != NULL)
				buff_root = buff_root->right;
			else
			{
				// Insert The ft_rbtree_node_t
				to_insert = new_node(value, tree->value_size, buff_root);
				if (to_insert == NULL)
					return NULL;
				buff_root->right = to_insert;
				buff_root = to_insert;

				// Check For Double Red Problems
				break;
			}
		}
	}

	while (buff_root != tree->root)
	{
		check_node(buff_root);
		if (buff_root->parent == NULL)
		{
			tree->root = buff_root;
			break;
		}
		buff_root = buff_root->parent;
		if (buff_root == tree->root)
			buff_root->color = RBT_BLACK;
	}
	tree->node_count++;
	return to_insert;
}
