#include "main.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	while (i + 1 < dstsize)
	{
		dst[i] = src[i];
		if (src[i] == '\0')
			break ;
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	while (s1[i] != '\0')
		i++;
	p = (void *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	j = 0;
	while (j < i)
	{
		p[j] = s1[j];
		j++;
	}
	p[j] = '\0';
	return (p);
}
