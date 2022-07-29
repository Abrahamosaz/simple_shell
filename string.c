#include "string.h"
/**
 * _strncmp - compare n charcaters of two string
 * @dest: first string
 * @src: second string
 * @n: number of bytes to compare
 *
 * Return: return 0 on success
 */
int _strncmp(char *dest, char *src, size_t n)
{
	size_t i = 0;

	for (i; i < n; i++)
	{
		if (dest[i] != src[i])
			return (dest[i] - src[i]);
	}
	return (0);
}
