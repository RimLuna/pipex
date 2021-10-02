#include "pipex.h"

char
*_strdup (s)
const char *s;
{
	char	*p;
	char	*k;

	p = (char *)malloc(_strlen(s) * sizeof(char));
	if (p == (char*) 0)
    	return (char*) 0;
	k = p;
	while(s && *s)
		*p++ = *s++;
	*p = '\0';
	return (k);
}
