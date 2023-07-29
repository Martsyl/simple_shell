#include "dash.h"

/**
 * _realloc - reallocates memory block
 * @ptr: pointer to the previous memory
 * @size_before: the old size
 * @size_after: the new size
 *
 * Return: a pointer to the newly allocated memory
 */
void *_realloc(void *ptr, unsigned int size_before, unsigned int size_after)
{
	void *result;

    /* If the new size is the same as the old size, no need to reallocate. */
	if (size_after == size_before)
		return (ptr);

    /* If the newsize is 0 and the ptr is not NULL, free mem and return NULL */
	if (size_after == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}

	/* Allocate memory for the result with the new size. */
	result = malloc(size_after);
	if (!result)
		return (NULL);

	/* If the pointer is NULL, fill the new memory block with null bytes. */
	if (!ptr)
	{
		_memset(result, '\0', size_after);
		free(ptr);
	}
	else
	{
		/* Copy the contents from the old memory block to the new one. */
		_memcpy(result, ptr, size_before);
		free(ptr);
	}
	return (result);
}

/**
 * _memset - fills a memory with a constant byte
 * @s: pointer to memory area
 * @n: number of bytes to fill
 * @byt: constant byte
 *
 * Return: A pointer to the character
 */
char *_memset(char *s, char byt, unsigned int n)
{
	unsigned int i;

    /* Fill the memory area pointed by 's' with 'byt' for 'n' bytes. */
	for (i = 0; i < n; i++)
	{
		s[i] = byt;
	}
	return (s);
}

/**
 * free_data - frees data
 * @data: the data structure
 *
 * Return: (Success) positive number
 * ------- (Fail) negative number
 */
int free_data(das_h *data)
{
    /* Free the allocated mem for each data field and set the ptr to NULL. */
	free(data->line);
	data->line = NULL;
	free(data->args);
	data->args = NULL;
	free(data->cmd);
	data->cmd = NULL;
	free(data->error_msg);
	data->error_msg = NULL;

	return (0);
}

/**
 * _memcpy - copies memory area
 * @dest: Destination memory area
 * @src: Source memory area
 * @n: Amount of memory bytes to copy
 *
 * Return: A pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;
	/* Copy 'n' bytes from the source mem area to the destination mem area. */
	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}
