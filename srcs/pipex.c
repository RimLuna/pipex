#include "pipex.h"

void
child(pstruct, p, envp)
t_pipex	pstruct;
int		*p;
char	**envp;
{
	char	**cmd;

	cmd = _split(pstruct.cmd1, ' ');
	if (pstruct.fd1 == -1)
	{
		dcmd(cmd);
		bye(&pstruct, NULL);
	}
	dup2(pstruct.fd1, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(pstruct.fd1);
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
