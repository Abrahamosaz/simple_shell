#include "shell.h"
/**
 * _strcat - concatenate two string
 * @dest: destination
 * @src: passed string
 *
 * Return: return pointer of dest string
 */
char *_strcat(char *dest, char *src)
{
	unsigned int i = 0, j = 0;

	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
