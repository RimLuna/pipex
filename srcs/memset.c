#include "pipex.h"

void *
_memset(b, c, len)
void	*b;
int		c;
size_t	len;
{
	unsigned char *str;

	str = (unsigned char*)b;
	while (len-- > 0)
	{
		*str++ = (unsigned char)c;
	}
	return (b);
}