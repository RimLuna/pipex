#include "pipex.h"

char
*_strdup (s)
const char *s;
{
	char	*p;
	char	*k;

	p = (char *)malloc(sizeof(char));
	if (p == (char*) 0)
    	return (char*) 0;
	k = p;
	while(s && *s)
		*p++ = *s++;
	*p = '\0';
	return (k);
}

void
usage (void)
{
	write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
}

void
usagecode (code)
int		code;
{
	write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	exit(code);
}

void
_strerror (msg, _strlen)
char	*msg;
int		_strlen;
{
	write(2, msg, _strlen);
}

void
argcheck (ac, av, pstruct)
int		ac;
char	**av;
t_pipex	*pstruct;
{
	int	i;

	if (ac != 5)
		usagecode(INVALID_ARGS);
	i = -1;
	while (av[++i])
		if (av[i][0] == '\0')
		{
			_strerror("Error: empty argument\n", 24);
			usagecode(EMPTY_ARGS);
		}
}

void
getpstruct (av, envp, pstruct)
char	**av;
char	**envp;
t_pipex	*pstruct;
{
	if ((pstruct->fd1 = open(av[1], O_RDONLY)) < 0)
	{
		_strerror("Error: \n", 7);
		perror(av[1]);
	}
	if ((pstruct->fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644)) < 0)
	{
		_strerror("Error: \n", 7);
		perror(av[4]);
	}
	pstruct->cmd1 = _strdup(av[2]);
	pstruct->cmd2 = _strdup(av[3]);
}

int
main (ac, av, envp)
int		ac;
char	**av;
char	**envp;
{
	t_pipex	pstruct;

	argcheck(ac, av);
	getpstruct(av, envp, &pstruct);
	printf("%s %s %d %d \n", pstruct.cmd1, pstruct.cmd2, pstruct.fd1, pstruct.fd2);
	// pipex(pstruct);
	close(pstruct.fd1);
	close(pstruct.fd2);
}