/**
 * delete_newline - removes newline
 * @string: string parameter
 * Return: newstring
 */
char *delete_newline(char *string)
{
        int i, len;

        len = strlen(string);
        char *newstring;

        newstring = (char *)malloc(len - 1);

        for (i = 0; i < len - 1; i++)
        {
                newstring[i] = string[i];
        }
        return (newstring);
}
