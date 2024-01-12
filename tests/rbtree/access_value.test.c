#include <ft_rbtree.h>
#include <ft_test.h>
#include <stdlib.h>

static int cmp_int(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}

START_TEST(test_access_value_read, "test that ACCESS_VALUE read work")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);
	int value = 42;
	ft_rbtree_insert(tree, &value);
	ft_rbtree_node_t *node = ft_rbtree_search(tree, &value);
	assert_equal(ACCESS_VALUE(node, int), 42);
	ft_rbtree_destroy(tree);
}
END_TEST

START_TEST(test_access_value_write, "test that ACCESS_VALUE write work")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);
	int value = 42;
	ft_rbtree_insert(tree, &value);
	ft_rbtree_node_t *node = ft_rbtree_search(tree, &value);
	ACCESS_VALUE(node, int) = 21;
	assert_equal(ACCESS_VALUE(node, int), 21);
	ft_rbtree_destroy(tree);
}
END_TEST