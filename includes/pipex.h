/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:08:30 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 11:36:05 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include<sys/wait.h>
# define EMPTY_ARGS 2
# define INVALID_ARGS 1
# define COMMAND_NOT_FOUND 3

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	*cmd2;
	char	*cmd1path;
	char	*cmd2path;
}				t_pipex;

char	**_split(char const *s, char c);
char	*_strdup(const char *s);
int		_strcmp(const char *s1, const char *s2);
int		_strncmp(const char *s1, const char *s2, size_t n);
char	*_strjoin(char *s1, char *s2);
int		_strlen(const char	*s);
void	*_memset(void *b, int c, size_t len);
void	_bzero(void *s, size_t n);
char	*_strnew(size_t size);
void	*_memalloc(size_t size);
void	bye(t_pipex *pstruct, char *p, int cmderr);
void	usage(void);
void	usagecode(int code);
void	_strerror(char *msg, int _strlen);
void	cmd404(char *cmd);
void	dcmd(char **cmd);
void	dcmds(char **cmd1, char **cmd2);
void	dstruct(t_pipex *pstruct);
void	argcheck(int ac, char **av);
char	*_getenv(char **env, const char *name);
void	pathmdlwr(char **c1p, char **c2p, t_pipex *ps, char **pi);
void	getpaths(char **envp, t_pipex *pstruct);
void	getpstruct(char **av, char **envp, t_pipex *pstruct);
void	pipex(t_pipex pstruct, char **envp);
int		main(int ac, char **av, char **envp);
#endif
