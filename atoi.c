#include "shell.h" 
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
/**
 * main - holds code
 * Return: 0
 */
int main(void)
{
	char *str = "-23872";
	int value = _atoi(str);
	printf("%d\n", value);
	return (0);
}
