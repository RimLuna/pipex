#include "pipex.h"

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

char
*_getenv(env, name)
char **env;
const char *name;
{
	const char	*np;
	char		**p;
	char		*envptr;
	int			len;
	int			*offset;

	np = name;
	while (*np && *np != '=')
		np++;
	len = np - name;
	p = env;
	while ((envptr = *p) != NULL)
	{
		if (_strncmp(envptr, name, len) == 0 && envptr[len] == '=')
		{
			offset = (int *)(p - env);
			return (_strdup(envptr + len + 1));
		}
		p++;
	}
	return (NULL);
}

void
getpaths (envp, pstruct)
char	**envp;
t_pipex	*pstruct;
{
	char	**paths;
	char	*path;
	char	*cmd1path;
	char	*cmd2path;
	int		i;
	struct stat statbuf;

	paths = _strtok(_getenv(envp, "PATH"), ":");
	i = -1;
	while (paths && paths[++i])
	{
		path = paths[i];
		path = _strjoin(path, "/");
		cmd1path = _strjoin(path, pstruct->cmd1);
		cmd2path = _strjoin(path, pstruct->cmd2);
		// printf("%s %s %s %s\n", cmd1path, cmd2path, pstruct->cmd1, pstruct->cmd2);
		if (stat(cmd1path, &statbuf) != -1)
			pstruct->cmd1path = _strdup(cmd1path);
		if (stat(cmd2path, &statbuf) != -1)
			pstruct->cmd2path = _strdup(cmd2path);
	}
	if (pstruct->cmd1path == NULL)
	{
		_strerror("Error: \n", 7);
		_strerror(pstruct->cmd1, _strlen(pstruct->cmd1));
		_strerror(": command not found\n", 20);
	}
	if (pstruct->cmd2path == NULL)
	{
		_strerror("Error: \n", 7);
		_strerror(pstruct->cmd2,  _strlen(pstruct->cmd2));
		_strerror(": command not found\n", 20);
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
	printf("%s %s\n", pstruct->cmd1, pstruct->cmd2);
	getpaths(envp, pstruct);
	printf("%s %s\n", pstruct->cmd1path, pstruct->cmd2path);
}

int
main (ac, av, envp)
int		ac;
char	**av;
char	**envp;
{
	t_pipex	pstruct;

	pstruct = (t_pipex){0};
	argcheck(ac, av);
	getpstruct(av, envp, &pstruct);
	printf("%s %s %d %d \n", pstruct.cmd1, pstruct.cmd2, pstruct.fd1, pstruct.fd2);
	// pipex(pstruct);
	close(pstruct.fd1);
	close(pstruct.fd2);
}