#include "pipex.h"

void *
_memalloc(size)
size_t	size;
{
	unsigned char *mem;

	mem = (unsigned char*)malloc(sizeof(size_t) * size);
	if (mem == NULL)
		return (NULL);
	_bzero(mem, size);
	return (mem);
}