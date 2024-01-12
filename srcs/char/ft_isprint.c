/**
 * @brief Checks if the character is printable
 *
 * @param c The character to check
 * @return int 1 if the character is printable, 0 otherwise
 */
int ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}