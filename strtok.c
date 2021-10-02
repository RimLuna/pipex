#include "pipex.h"

static int
countok(s, delim)
char	*s;
char	*delim;
{
	int		i;
	int		count;

	count = 0;
	while (*s)
	{
		i = 0;
		while (delim[i])
			(*s == delim[i++]) ? count++ : 0;
		s++;
	}
	return (count + 1);
}

static int
countc(s, delim)
char	*s;
char	*delim;
{
	int		i;
	int		count;

	count = 0;
	while (s[count])
	{
		i = 0;
		while (delim[i])
		{
			if (s[count] == delim[i++])
				return (count);
		}
		count++;
	}
	return (count);
}

char **
_strtok(s, delim)
char	*s;
char	*delim;
{
	int		i;
	char	**tokens;
	int		ck;
	int		cc;
	int		j;

	ck = countok(s, delim);
	i = 0;
	tokens = (char **)_memalloc(sizeof(char *) * (ck + 1));
	while (i < ck)
	{
		j = 0;
		(s && !(cc = countc(s, delim))) ? s++ : 0;
		(s && cc) ? tokens[i] = _strnew(cc) : 0;
		while (*s && j < cc && cc > 0)
			tokens[i][j++] = *(s++);
		(tokens[i] || cc) ? i++ : 0;
		if (!*s)
			break;
	}
	tokens[i] = NULL;
	return (tokens);
}
