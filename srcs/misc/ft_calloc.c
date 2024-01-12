#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocate memory and set it to 0
 *
 * @param count the number of elements
 * @param size  the size of each element
 * @return void* a pointer to the allocated memory
 */
void *ft_calloc(size_t count, size_t size)
{
	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	void *ptr = malloc(count * size);
	if (ptr == NULL)
		return NULL;
	for (size_t i = 0; i < count * size; i++)
		((char *)ptr)[i] = 0;
	return ptr;
}