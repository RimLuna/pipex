#include "pipex.h"

int
_strlen(s)
const char	*s;
{
	int		i;

	i = -1;
	while(s[++i])
		;
	return (i);
}
