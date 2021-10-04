#include "pipex.h"

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
	pipex(pstruct, envp);
	dstruct(&pstruct);
	return (0);
}
