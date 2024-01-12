#pragma once

#include <stddef.h>

/**
 * @brief Allocate memory and set it to 0
 *
 * @param count the number of elements
 * @param size  the size of each element
 * @return void* a pointer to the allocated memory
 */
void *ft_calloc(size_t count, size_t size);