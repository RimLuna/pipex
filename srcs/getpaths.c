#include "pipex.h"

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
