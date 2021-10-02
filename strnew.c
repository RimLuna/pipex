#include "pipex.h"

char *
_strnew(size)
size_t size;
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	_memset((char*)str, (int)'\0', size + 1);
	return (str);
}