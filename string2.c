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
/**
 *
 *
 */
void print_str(char *args)
{
	size_t i = 0;

	while (args[i])
	{
		write(STDOUT_FILENO, &args[i], 1);
		i++;
	}
	write(STDOUT_FILENO, "\n", 2);
}
/**
 *
 *
 *
 */
ssize_t _isalpha(char str)
{
	if (str >= 48 && str <= 57)
		return (0);
	return (-1);
}
/**
 * _atoi - converts string to integer
 * @str: string parameter
 * Return: integer value
 */
int _atoi(char *str)
{
        int sign = 1, value = 0, i = 0, j = 0;
        size_t size;
        char *string = NULL;

        size = strlen(str);
        string = malloc(sizeof(char) * size);
        while (*str)
        {
                string[i] = *str;
                i++;
                str++;
        }
        if (string[0] == '-')
        {
                sign = -1;
                j = 1;
        }
        while (string[j] != '\0')
        {
                if ((string[j] - '0') < 0 || (string[j] - '0') > 9)
                        return (0);
                value = (value * 10) + (string[j] - '0');
                j++;
        }
        return (sign * value);
}
