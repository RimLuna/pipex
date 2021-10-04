#include "pipex.h"

char
*_strdup (s)
const char *s;
{
	char	*p;
	char	*k;

	p = (char *)malloc((_strlen(s) + 1) * sizeof(char));
	if (!p)
    	return (NULL);
	k = p;
	while(s && *s)
		*p++ = *s++;
	*p = '\0';
	return (k);
}
