#include "main.h"

void	secure_free(void *p)
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
}

void	init_arg(int argc, char **argv, char **envp, t_arg *arg)
{
	int		i;

	arg->argc = argc;
	arg->argv = argv;
	i = 0;
	arg->path_cnt = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			arg->path[arg->path_cnt++] = ft_strdup(&envp[i][5]);
		i++;
	}
	if (arg->path_cnt != 1)
		error_exit(ERR_ENV_INVALID, NULL);
	i = 0;
	while (arg->path[0][i] != '\0')
	{
		if (arg->path[0][i] == ':')
		{
			arg->path[0][i++] = '\0';
			arg->path[arg->path_cnt++] = &arg->path[0][i];
		}
		i++;
	}
	arg->path[arg->path_cnt] = NULL;
}
