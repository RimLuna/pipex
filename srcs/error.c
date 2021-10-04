#include "pipex.h"

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
