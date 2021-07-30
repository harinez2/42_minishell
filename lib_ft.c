#include "main.h"

size_t	ft_strlen(const char *str)
{
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchars(char *s)
{
	write(1, s, ft_strlen(s));
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				diff;

	i = 0;
	while (i < n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff)
			return (diff);
		if (s1[i] == '\0' || s2[i] == '\0')
			return (diff);
		i++;
	}
	return (0);
}

static size_t	calc_ret(size_t di_init, size_t si, size_t di, size_t dstsize)
{
	if (di <= dstsize)
		return (di_init + si);
	else
		return (di_init + si - di + dstsize);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		di;
	size_t		di_init;
	size_t		si;

	di = ft_strlen(dst);
	di_init = di;
	si = 0;
	while (di + 1 < dstsize)
	{
		dst[di] = src[si];
		if (src[si] == '\0')
			break ;
		di++;
		si++;
	}
	if (dstsize > 0)
		dst[di] = '\0';
	return (calc_ret(di_init, ft_strlen(src), di, dstsize));
}
