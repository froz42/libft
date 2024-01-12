#include <ft_rbtree.h>
#include <ft_test.h>

static int cmp_int(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

START_TEST(test_new_rbtree, "Test that ft_rbtree_new returns a valid tree")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);
	assert_not_null(tree);
	assert_null(tree->root);
	assert_equal(tree->value_size, sizeof(int));
	assert_equal(tree->node_count, 0);
	assert_equal(tree->cmp, cmp_int);
	ft_rbtree_destroy(tree);
}
END_TEST