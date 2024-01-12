#include <ft_string.h>
#include <ft_test.h>

START_TEST(test_ft_escape, "Test ft_escape when nothing needs to be escaped")
{
	char *str_to_escape = "Hello World";
	char *str = ft_escape(str_to_escape, strlen(str_to_escape));
	assert_string_equal(str, "Hello World");
	free(str);
}
END_TEST

START_TEST(test_ft_escape_2, "Test ft_escape with \\t")
{
	char *str_to_escape = "Hello\tWorld";
	char *str = ft_escape(str_to_escape, strlen(str_to_escape));
	assert_string_equal(str, "Hello\\tWorld");
	free(str);
}
END_TEST

START_TEST(test_ft_escape_3, "Test ft_escape with \\n")
{
	char *str_to_escape = "Hello\nWorld";
	char *str = ft_escape(str_to_escape, strlen(str_to_escape));
	assert_string_equal(str, "Hello\\nWorld");
	free(str);
}
END_TEST

START_TEST(test_ft_escape_4, "Test ft_escape with \\r")
{
	char *str_to_escape = "Hello\rWorld";
	char *str = ft_escape(str_to_escape, strlen(str_to_escape));
	assert_string_equal(str, "Hello\\rWorld");
	free(str);
}
END_TEST

START_TEST(test_ft_escape_5, "Test ft_escape with \\0")
{
	char *str_to_escape = "Hello\0World";
	char *str = ft_escape(str_to_escape, 11);
	assert_string_equal(str, "Hello\\0World");
	free(str);
}
END_TEST