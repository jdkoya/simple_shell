#include "getline.h"
#include "string.h"

/**
 * _realloc - This func allocates for buffer
 * @old: a pointer arg.
 * @old_size: The current buff size
 * @new_size: to alternate thru buffer size
 * Return: returns NULL ptr
 */
static void *_realloc(void *old, size_t old_size, size_t new_size)
{
	void *n = 0;

	if (old)
	{
		if (new_size)
		{
			n = malloc(new_size);
			if (n)
			{
				_memcpy(n, old, old_size < new_size ? old_size : new_size);
				free(old);
			}
		}
		else
		{
			free(old);
		}
	}
	return (n);
}
/**
 * _getline_next - Retrieve a line of input using a helper funct
 * @buf: buffer ptr
 * @line: An address to ptr
 * @size: The ptr size
 * @n: copies number of characters from buff
 * Return: returns line ptr or NULL
 */
static char *_getline_next(buf_t *buf, char **line, size_t *size, size_t n)
{
	char *tmp = 0;

	if (*line)
		tmp = _realloc(*line, *size, *size + n);
	else
		tmp = malloc(n + 1);

	if (tmp)
	{
		*line = tmp;

		if (*size)
			*size -= 1;

		_memcpy(*line + *size, buf->next, n);
		*size += n;

		(*line)[*size] = '\0';
		*size += 1;
	}
	else
	{
		free(*line);
		*line = 0;
		*size = 0;
	}
	return (*line);
}

/**
 * _getline_buf - generates, retrieves and removes a func
 * @table: input argument
 * @fd: The file descriptor
 * Return: returns a buffer  ptr or NULL
 */
static buf_t *_getline_buf(buf_table_t *table, const int fd)
{
	buf_table_node_t *list = 0;
	size_t i = fd % GETLINE_TABLE_SIZE;

	if (table)
	{
		if (fd < 0)
		{
			for (i = 0; i < GETLINE_TABLE_SIZE; i += 1)
			{
				while ((list = (*table)[i]))
				{
					(*table)[i] = (*list).next;
					free(list);
				}
			}
		}
		else
		{
			list = (*table)[i];
			while (list && (*list).fd != fd)
				list = (*list).next;
			if (!list)
			{
				list = malloc(sizeof(*list));
				if (list)
				{
					(*list).fd = fd;
					list->buf.next = NULL;
					list->buf.remaining = 0;
					(*list).next = (*table)[i];
					(*table)[i] = list;
				}
			}
		}
	}
	return (list ? &list->buf : 0);
}

/**
 * _getline - a function to read input
 * @fd: a uniq num to describe a file
 * Return: returns NULL value
 */
char *_getline(const int fd)
{
	static buf_table_t tab;
	buf_t *buff = _getline_buf(&tab, fd);
	char *line = 0;
	size_t size = 0;
	ssize_t i = 0;
	ssize_t _read = 0;

	if (buff)
	{
		do {
			if ((*buff).remaining == 0)
				(*buff).next = (*buff).buffer;
			if (_read)
				(*buff).remaining = _read;
			if ((*buff).remaining)
			{
				i = _memchr((*buff).next, '\n', (*buff).remaining);
				if (i == -1)
				{
					if (_getline_next(buff, &line, &size, (*buff).remaining))
						(*buff).next += (*buff).remaining, (*buff).remaining = 0;
					else
						break;
				}
				else
				{
					if (_getline_next(buff, &line, &size, i + 1))
						(*buff).next += i + 1, (*buff).remaining -= i + 1;
					break;
				}
			}
		} while ((_read = read(fd, (*buff).buffer, GETLINE_BUFFER_SIZE)) > 0);
		if (_read == -1)
		{
			free(line);
			line = 0;
			size = 0;
		}
	}
	return (line);
}
