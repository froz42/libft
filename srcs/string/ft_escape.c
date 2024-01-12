#include <ft_char.h>
#include <ft_misc.h>
#include <ft_printf.h>
#include <ft_string.h>
#include <stddef.h>

/**
 * @brief Compute the number of digits of a number in base 10
 *
 * @param n The number
 * @return int The number of digits of the number
 */
static int compute_number_of_digits(int n)
{
	int digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return digits + 1;
}

typedef struct
{
	const char char_to_escape;
	const char *escaped_equivalent;
} escaped_char_t;

static const escaped_char_t escaped_chars[] = {
	{'\a', "\\a"}, {'\b', "\\b"}, {'\f', "\\f"},  {'\n', "\\n"},  {'\r', "\\r"},
	{'\t', "\\t"}, {'\v', "\\v"}, {'\"', "\\\""}, {'\\', "\\\\"},
};

/**
 * @brief Get the escaped equivalent of a character
 *
 * @param c The character to escape
 * @return const char* The escaped equivalent of the character
 */
static const char *get_escaped_equivalent(char c)
{
	for (size_t i = 0; i < sizeof(escaped_chars) / sizeof(escaped_char_t); i++)
	{
		if (escaped_chars[i].char_to_escape == c)
			return escaped_chars[i].escaped_equivalent;
	}
	return NULL;
}

/**
 * @brief Compute the size of the escaped string
 *
 * @param str The string to escape
 * @param size The size of the string
 * @return size_t The size of the escaped string
 */
static size_t compute_escaped_size(const char *str, size_t size)
{
	size_t size_computed = 0;
	for (size_t i = 0; i < size; i++)
	{
		const char *escaped_equivalent = get_escaped_equivalent(str[i]);
		if (escaped_equivalent != NULL)
			size_computed += ft_strlen(escaped_equivalent);
		else if (ft_isprint(str[i]))
			size_computed++;
		else
			size_computed += 1 + compute_number_of_digits(str[i]);
	}
	return size_computed + 1;
}

/**
 * @brief Escape a memory
 *
 * @param str The string to escape
 * @param size The size of the string
 * @return char* The escaped string
 */
char *ft_escape(const char *str, size_t size)
{
	size_t escaped_size = compute_escaped_size(str, size);
	char *escaped_str = ft_calloc(escaped_size + 1, sizeof(char));
	if (escaped_str == NULL)
		return NULL;
	size_t j = 0;
	for (size_t i = 0; i < size; i++)
	{
		const char *escaped_equivalent = get_escaped_equivalent(str[i]);
		if (escaped_equivalent != NULL)
		{
			int added = ft_snprintf(escaped_str + j, escaped_size - j, "%s", escaped_equivalent);
			if (added < 0)
			{
				free(escaped_str);
				return NULL;
			}
			j += added;
		}
		else if (ft_isprint(str[i]))
			escaped_str[j++] = str[i];
		else
		{
			int added =
				ft_snprintf(escaped_str + j, escaped_size - j, "\\%u", (unsigned char)str[i]);
			if (added < 0)
			{
				free(escaped_str);
				return NULL;
			}
			j += added;
		}
	}
	return escaped_str;
}