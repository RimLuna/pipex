#include "pipex.h"

char	*_strjoin(s1, s2)
char	*s1;
char	*s2;
{
	char	*str;
	int		i;
	int		j;

	if (!(str = (char *)malloc((_strlen(s1) + _strlen(s2) + 1)
								* sizeof(char))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
