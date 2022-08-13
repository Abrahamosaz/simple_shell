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
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * print_str - print string to STDOUT
 * @args: string
 *
 * Return: return void
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
 * _isalpha - check if a number is alphabetical
 * @str: value to check
 *
 * Return: return 0 if True and 1 othewise
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

	size = _strlen(str);
	string = malloc(sizeof(char) * (size + 1));
	while (*str)
	{
		string[i] = *str;
		i++;
		str++;
	}
	string[i] = '\0';
	if (string[0] == '-')
	{
		sign = -1;
		j = 1;
	}
	while (string[j])
	{
		if ((string[j] - '0') < 0 || (string[j] - '0') > 9)
			return (0);
		value = (value * 10) + (string[j] - '0');
		j++;
	}
	free(string);
	return (sign * value);
}
/**
 * args_count - count the number of arguments enter by the user
 * @args: array of pointers of arguments
 *
 * Return: return the count
 */
size_t args_count(char **args)
{
	size_t i = 0, count = 0;

	while (args[i++])
		count++;
	return (count);
}
