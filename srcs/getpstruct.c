#include "pipex.h"

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
		bye(pstruct, NULL, 0);
	}
	pstruct->cmd1 = _strdup(av[2]);
	if (!pstruct->cmd1)
		bye(pstruct, NULL, 0);
	pstruct->cmd2 = _strdup(av[3]);
	if (!pstruct->cmd2)
		bye(pstruct, pstruct->cmd1, 0);
	getpaths(envp, pstruct);
}
