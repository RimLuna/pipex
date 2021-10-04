#include "pipex.h"

char
*_getenv(env, name)
char **env;
const char *name;
{
	const char	*np;
	char		**p;
	char		*envptr;
	int			len;

	np = name;
	while (*np && *np != '=')
		np++;
	len = np - name;
	p = env;
	while ((envptr = *p) != NULL)
	{
		if (_strncmp(envptr, name, len) == 0 && envptr[len] == '=')
		{
			return (_strdup(envptr + len + 1));
		}
		p++;
	}
	return (NULL);
}
