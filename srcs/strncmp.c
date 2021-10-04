#include "pipex.h"

int
_strncmp(s1, s2, len)
const char	*s1;
const char	*s2;
size_t		len;
{
  unsigned char u1, u2;
  while (len-- > 0)
    {
      u1 = (unsigned char) *s1++;
      u2 = (unsigned char) *s2++;
      if (u1 != u2)
        return u1 - u2;
      if (u1 == '\0')
        return 0;
    }
  return (0);
}
