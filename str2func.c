#include "main.h"

/**
 * mem_cpy - function that copies memory area.
 * @str:  memory area.
 * @mem: memory .
 * @b: bytes to be copied.
 * Return: str.
 */

char *mem_cpy(char *str, char *mem, unsigned int b)
{
	unsigned int i;

	for (i = 0; i < b; i++)
	{
		str[i] = mem[i];
	}
	return (str);
}

/**
* str_cat - concatenate 
*
* @str: string
* @cat: source srting
* Return: str
*/
char *str_cat(char *str, char *cat)
{
	int i = 0;
	int c = 0;

	while (str[i] != '\0')
	{
		i++;
	}
	while (cat[c] != '\0')
	{
		str[i] = cat[c];
		i++;
		c++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * str_cpy - copys str to another
 * @str:  string
 * @cpy:  copy
 *
 * Return: the pointer to dst
 */

char *str_cpy(char *str, char *cpy)
{
	int i = 0;

	while (*(cpy + i))
	{
		*(str + i) = *(cpy + i);
		i++;
	}
	*(str + i) = '\0';

	return (str);
}
int _strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}
/**
 * str_dup - duplicate str
 * @str: ptr to be duplicated.
 * Return: NULL or str1.
 */

char *str_dup(char *str)
{
	char *str1;
	unsigned int len;

	if (str == 0)
	{
		return (NULL);
	}
	len = _strlen(str) + 1;
	str1 = (char *)malloc(sizeof(char) * len);
	if (str1 == 0)
	{
		return (NULL);
	}
	mem_cpy(str1, str, len);
	return (str1);
}
