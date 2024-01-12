#include <ft_rbtree.h>
#include <ft_test.h>

static int cmp_int(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

START_TEST(test_delete_single_node, "test delete on single node")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);
	int value = 42;
	ft_rbtree_insert(tree, &value);
	ft_rbtree_delete(tree, tree->root);
	assert_null(tree->root);
	assert_equal(tree->node_count, 0);
	ft_rbtree_destroy(tree);
}
END_TEST

START_TEST(test_delete_10_nodes, "Test deleting 10 nodes")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);

	for (int i = 0; i < 10; i++)
		ft_rbtree_insert(tree, &i);

	for (int i = 0; i < 10; i++)
	{
		ft_rbtree_node_t *node = ft_rbtree_search(tree, &i);
		ft_rbtree_delete(tree, node);
		for (int j = i + 1; j < 10; j++)
		{
			ft_rbtree_node_t *node = ft_rbtree_search(tree, &j);
			if (node == NULL)
				fail("A node was not found");
		}
	}
	assert_null(tree->root);
	assert_equal(tree->node_count, 0);
	succeed();
	ft_rbtree_destroy(tree);
}
END_TEST