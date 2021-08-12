#include "main.h"

static int	get_bigger_len(char *s1, char *s2)
{
	int		ret;

	ret = ft_strlen(s1);
	if (ret < (int)ft_strlen(s2))
		ret = ft_strlen(s2);
	return (ret);
}

static void	mergesort_merge_envp(int *envp_i, char **envp, int start, int end)
{
	int		i;
	int		j;
	int		mid;
	int		sorted[MAX_ENVP];
	int		s;

	mid = start + (end - start) / 2;
	i = start;
	j = mid;
	s = 0;
	while (i < mid && j < end)
	{
		if (ft_strncmp(envp[envp_i[i]], envp[envp_i[j]],
				get_bigger_len(envp[envp_i[i]], envp[envp_i[j]])) < 0)
			sorted[s++] = envp_i[i++];
		else
			sorted[s++] = envp_i[j++];
	}
	if (i == mid)
		while (j < end)
			sorted[s++] = envp_i[j++];
	else
		while (i < mid)
			sorted[s++] = envp_i[i++];
	copy_array(envp_i, sorted, s, start);
}

static void	mergesort_envp(int *envp_i, char **envp, int start, int end)
{
	int		mid;

	if (start == end || start + 1 == end)
		return ;
	mid = start + (end - start) / 2;
	mergesort_envp(envp_i, envp, start, mid);
	mergesort_envp(envp_i, envp, mid, end);
	mergesort_merge_envp(envp_i, envp, start, end);
}

void	builtincmd_export(char **envp)
{
	int		cnt;
	int		i;
	int		envp_i[MAX_ENVP];

	cnt = 0;
	while (envp[cnt] != NULL)
	{
		envp_i[cnt] = cnt;
		cnt++;
	}
	mergesort_envp(envp_i, envp, 0, --cnt);
	i = 0;
	while (i < cnt)
		printf("%s\n", envp[envp_i[i++]]);
}
