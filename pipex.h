#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# define EMPTY_ARGS 2
# define INVALID_ARGS 1

typedef	struct	s_pipex
{
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	*cmd2;
}				t_pipex;


void	pipex(t_pipex pstruct);

#endif
