#include <ft_rbtree.h>
#include <ft_test.h>

static int cmp_int(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

START_TEST(test_insert_node, "Test that ft_rbtree_insert inserts a node")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);
	int value = 42;
	ft_rbtree_insert(tree, &value);
	assert_not_null(tree->root);
	assert_equal(tree->node_count, 1);
	assert_equal(*(int *)tree->root->variable_value, 42);
	ft_rbtree_destroy(tree);
}
END_TEST

START_TEST(test_insert_node2, "Test that ft_rbtree_insert inserts two nodes")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);
	int value = 42;
	ft_rbtree_insert(tree, &value);
	assert_not_null(tree->root);
	assert_equal(tree->node_count, 1);
	assert_equal(ACCESS_VALUE(tree->root, int), 42);
	value = 43;
	ft_rbtree_insert(tree, &value);
	assert_not_null(tree->root->right);
	assert_equal(tree->node_count, 2);
	assert_equal(ACCESS_VALUE(tree->root->right, int), 43);
	ft_rbtree_destroy(tree);
}
END_TEST

START_TEST(test_insert_node3, "Test that ft_rbtree_insert inserts three nodes")
{
	ft_rbtree_t *tree = ft_rbtree_new(sizeof(int), cmp_int);
	int value = 42;
	ft_rbtree_insert(tree, &value);
	assert_not_null(tree->root);
	assert_equal(tree->node_count, 1);
	assert_equal(*(int *)tree->root->variable_value, 42);
	value = 43;
	ft_rbtree_insert(tree, &value);
	assert_not_null(tree->root->right);
	assert_equal(tree->node_count, 2);
	value = 44;
	ft_rbtree_insert(tree, &value);
	assert_not_null(tree->root->left);
	assert_equal(tree->node_count, 3);

	assert_equal(ACCESS_VALUE(tree->root, int), 43);
	assert_equal(ACCESS_VALUE(tree->root->left, int), 42);
	assert_equal(ACCESS_VALUE(tree->root->right, int), 44);
	ft_rbtree_destroy(tree);
}
END_TEST