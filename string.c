#include "string.h"
/**
 * _strlen - To get the length of a string
 * @str: string
 *
 * Return: return the length count
 */
int _strlen(char *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	return (i);
}
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

	if (n)
	{
		for (i; i < n; i++)
		{
			if (dest[i] != src[i])
				return (dest[i] - src[i]);
		}
		return (0);
	}
	for (i; dest[i] || src[i]; i++)
	{
		if (dest[i] != src[i])
			return (dest[i] - src[i]);
	}
	return (0);
}
/**
 * strtoken - tokenize the string for execve call
 * @buffer: string gotten from getline function
 *
 * Return: return a array of argument pointers
 */
char **strtoken(char *buffer)
{
	size_t j = 0, i = 0, count;
	char *token = NULL, *delim = " \n", *buffer_cpy = NULL;
	char **string_tokenize = NULL;

	while (buffer[i])
		i++;
	buffer_cpy = malloc(sizeof(char) * i);
	if (!buffer_cpy)
		return (NULL);
	_strcpy(buffer_cpy, buffer);
	count = _strword(buffer, delim);
	string_tokenize = malloc(sizeof(char *) * count + 1);
	if (!string_tokenize)
		return (NULL);
	token = strtok(buffer_cpy, delim);
	for (j = 0; token; j++)
	{
		string_tokenize[j] = malloc(sizeof(char) * _strlen(token));
		_strcpy(string_tokenize[j], token);
		token = strtok(NULL, delim);
	}
	string_tokenize[j] = NULL;
	free(buffer_cpy);
	return (string_tokenize);
}
/**
 * _strword - return the number of string
 * @str: string from getline function
 * @delim: delim use to tokenize the string
 *
 * Return: return the string count
 */
int _strword(char *str, char *delim)
{
	char *token;
	int count = 0;

	token = strtok(str, delim);
	while (token)
	{
		count++;
		token = strtok(NULL, delim);
	}
	return (count);
}
/**
 * _strcpy - copy the string from src to dest
 * @dest: destination
 * @src: source of string
 *
 * Return: return a pointer to dest string
 */
char *_strcpy(char *dest, char *src)
{
	size_t i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
