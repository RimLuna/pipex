#include "pipex.h"

void
dstruct(pstruct)
t_pipex	*pstruct;
{
	if (pstruct->cmd1)
		free(pstruct->cmd1);
	if (pstruct->cmd2)
		free(pstruct->cmd2);
	if (pstruct->cmd1path)
		free(pstruct->cmd1path);
	if (pstruct->cmd2path)
		free(pstruct->cmd2path);
}

void
bye (pstruct, p)
t_pipex	*pstruct;
char	*p;
{
	free(p);
	dstruct(pstruct);
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
dcmd(cmd)
char	**cmd;
{
	int	i;

	i = -1;
	while(cmd[++i])
		free(cmd[i]);
	free(cmd);
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
	char	*pathenv;
	char	*slashpath;

	pathenv = _getenv(envp, "PATH"),
	paths = _split(pathenv, ':');
	free(pathenv);
	i = -1;
	while (paths && paths[++i])
	{
		path = _strdup(paths[i]);
		free(paths[i]);
		if (path[_strlen(path) - 2 != '/'])
			slashpath = _strjoin(path, "/");
		cmd1 = _split(pstruct->cmd1, ' ');
		cmd2 = _split(pstruct->cmd2, ' ');
		base_cmd1 = _strdup(cmd1[0]);
		dcmd(cmd1);
		base_cmd2 = _strdup(cmd2[0]);
		dcmd(cmd2);
		cmd1path = _strjoin(slashpath, base_cmd1);
		cmd2path = _strjoin(slashpath, base_cmd2);
		free(base_cmd1);
		free(base_cmd2);
		free(path);
		free(slashpath);
		if (stat(cmd1path, &statbuf) != -1)
			pstruct->cmd1path = _strdup(cmd1path);
		free(cmd1path);
		if (stat(cmd2path, &statbuf) != -1)
			pstruct->cmd2path = _strdup(cmd2path);
		free(cmd2path);
	}
	free(paths);
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
		bye(pstruct, NULL);
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
		bye(pstruct, NULL);
	}
	pstruct->cmd1 = _strdup(av[2]);
	if (!pstruct->cmd1)
		bye(pstruct, NULL);
	pstruct->cmd2 = _strdup(av[3]);
	if (!pstruct->cmd2)
		bye(pstruct, pstruct->cmd1);
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
	{
		dcmd(cmd);
		bye(&pstruct, NULL);
	}
	// printf("dup2 %d \n", pstruct.fd1);
	dup2(pstruct.fd1, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(pstruct.fd1);
	// printf("executing %s \n", pstruct.cmd1);
	if (execve(pstruct.cmd1path, cmd, envp) < 0)
	{
		dcmd(cmd);
		bye(&pstruct, NULL);
	}
	dcmd(cmd);
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

	cmd = _split(pstruct.cmd2, ' ');
	if (pstruct.fd2 == -1)
	{
		dcmd(cmd);
		bye(&pstruct, NULL);
	}
	dup2(pstruct.fd2, STDOUT_FILENO);
	dup2(p[0], STDIN_FILENO);
	close(p[1]);
	close(pstruct.fd2);
	if (execve(pstruct.cmd2path, cmd, envp) < 0)
	{
		dcmd(cmd);
		printf("all: %s %s %s %s\n", pstruct.cmd1, pstruct.cmd2, pstruct.cmd1path, pstruct.cmd2path);
		bye(&pstruct, NULL);
	}
	dcmd(cmd);
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
	bye(&pstruct, NULL);
	// close(pstruct.fd1);
	// close(pstruct.fd2);
}