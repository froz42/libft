#include <ft_rbtree.h>
#include <ft_test.h>

static int cmp_int(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

START_TEST(test_search_node, "Test that ft_rbtree_search finds a node")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);
	int value = 42;
	ft_rbtree_insert(tree, &value);
	ft_rbtree_node_t *node = ft_rbtree_search(tree, &value);
	assert_not_null(node);
	assert_equal(ACCESS_VALUE(node, int), 42);
	value = 43;
	ft_rbtree_insert(tree, &value);
	node = ft_rbtree_search(tree, &value);
	assert_not_null(node);
	assert_equal(ACCESS_VALUE(node, int), 43);
	ft_rbtree_destroy(tree);
}
END_TEST