#include "pipex.h"

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
