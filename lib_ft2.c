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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	int		i;
	char	*t;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(t = malloc(sizeof(char) * (s1len + s2len + 1))))
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		t[i] = s1[i];
		i++;
	}
	while (i < (s1len + s2len))
	{
		t[i] = s2[i - s1len];
		i++;
	}
	t[i] = '\0';
	return (t);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		srclen;
	size_t		dstlen;
	size_t		i;
	char		*t;

	srclen = (size_t)ft_strlen(s);
	if ((size_t)start < srclen)
	{
		dstlen = len;
		if ((size_t)start + len > srclen)
			dstlen = srclen - (size_t)start;
	}
	else
		dstlen = 0;
	if (!(t = malloc(sizeof(char) * (dstlen + 1))))
		return (NULL);
	i = 0;
	while (i < dstlen)
	{
		t[i] = s[(size_t)start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
