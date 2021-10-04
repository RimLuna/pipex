#include "pipex.h"

void
bye (void)
{
	perror("Error");
	exit(EXIT_FAILURE);
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
argcheck (ac, av)
int		ac;
char	**av;
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
	char	**cmd1, **cmd2;
	char	*base_cmd1, *base_cmd2;
	int		i;
	struct stat statbuf;

	paths = _strtok(_getenv(envp, "PATH"), ":");
	i = -1;
	while (paths && paths[++i])
	{
		path = paths[i];
		if (path[_strlen(path) - 2 != '/'])
			path = _strjoin(path, "/");
		cmd1 = _split(pstruct->cmd1, ' ');
		// printf("|%s| ,|%s|\n", cmd1[0], cmd1[1]);
		cmd2 = _split(pstruct->cmd2, ' ');
		// printf("|%s| ,|%s|\n", cmd2[0], cmd2[1]);
		base_cmd1 = cmd1[0];
		base_cmd2 = cmd2[0];
		cmd1path = _strjoin(path, base_cmd1);
		cmd2path = _strjoin(path, base_cmd2);
		// printf("%s %s\n", cmd1path, cmd2path);
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
		exit(COMMAND_NOT_FOUND);
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
	// printf("%s %s\n", pstruct->cmd1, pstruct->cmd2);
	getpaths(envp, pstruct);
	// printf("%s %s\n", pstruct->cmd1path, pstruct->cmd2path);
}

void
child(pstruct, p, envp)
t_pipex	pstruct;
int		*p;
char	**envp;
{
	char	**cmd;

	// cmd = _split(pstruct.cmd1, " ");
	cmd = _split(pstruct.cmd1, ' ');
	// printf("haha %s %s %s\n", pstruct.cmd1, cmd[0], cmd[1]);
	if (pstruct.fd1 == -1)
		bye();
	// printf("dup2 %d \n", pstruct.fd1);
	dup2(pstruct.fd1, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(pstruct.fd1);
	// printf("executing %s \n", pstruct.cmd1);
	if (execve(pstruct.cmd1path, cmd, envp) == -1)
		bye();
	exit(EXIT_SUCCESS);
}

void
child1(pstruct, p, envp)
t_pipex	pstruct;
int		*p;
char	**envp;
{
	char	**cmd;
	int		status;

	// waitpid(-1, &status, 0);
	cmd = _split(pstruct.cmd2, ' ');
	if (pstruct.fd2 == -1)
		bye();
	// printf("%s\n", cmd);
	dup2(pstruct.fd2, STDOUT_FILENO);
	// close(STDIN_FILENO);
	dup2(p[0], STDIN_FILENO);
	close(p[1]);
	close(pstruct.fd2);
	// printf("executing %s %s %s\n", pstruct.cmd2, cmd[0], cmd[1]);
	if (execve(pstruct.cmd2path, cmd, envp) == -1)
		bye();
	// printf("success\n");
	exit(EXIT_SUCCESS);
}

void
pipex (pstruct, envp)
t_pipex	pstruct;
char	**envp;
{
	int		p[2];
	pid_t	pid1;
	pid_t	pid2;
	int   status;

	if (pipe(p) == -1)
	{
		_strerror("Error: \n", 7);
		perror("pipe");
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		_strerror("Error: \n", 7);
		perror("fork");
	}
	if (pid1 == 0)
		child(pstruct, p, envp);
	pid2 = fork();
	if (pid2 == -1)
	{
		_strerror("Error: \n", 7);
		perror("fork");
	}
	if (pid2 == 0)
		child1(pstruct, p, envp);
	waitpid(pid1, &status, 0);
    // waitpid(pid2, &status, 0);
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
	// printf("%s %s %d %d %s %s\n", pstruct.cmd1, pstruct.cmd2, pstruct.fd1, pstruct.fd2, pstruct.cmd1path, pstruct.cmd2path);
	pipex(pstruct, envp);
	// close(pstruct.fd1);
	// close(pstruct.fd2);
}