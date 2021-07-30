#include "main.h"

static char	**create_paramarry(char *cmd_with_param, t_arg *arg)
{
	int		i;
	int		pcnt;
	char	**newparams;

	i = 0;
	pcnt = 0;
	while (cmd_with_param[i] != '\0')
		if (cmd_with_param[i++] == ' ')
			pcnt++;
	newparams = malloc(sizeof(char *) * (pcnt + 2));
	if (!newparams)
		error_exit(ERR_FAILED_TO_MALLOC, arg);
	return (newparams);
}

static char	*create_oneparam(char *cmd_with_param, char *path, int *i)
{
	int		len;
	int		syspathlen;
	char	*newparam;

	len = 0;
	while (cmd_with_param[*i + len] != ' ' && cmd_with_param[*i + len] != '\0')
		len++;
	syspathlen = 0;
	if (*i == 0)
		syspathlen = ft_strlen(path) + 1;
	newparam = malloc(sizeof(char) * (syspathlen + len + 1));
	if (!newparam)
		return (NULL);
	if (*i == 0)
	{
		ft_strlcpy(&newparam[0], path, ft_strlen(path) + 1);
		ft_strlcpy(&newparam[syspathlen - 1], "/", 2);
	}
	ft_strlcpy(&newparam[syspathlen], &cmd_with_param[*i], len + 1);
	*i += len;
	return (newparam);
}

static char	**create_params(char *cmd_with_param, char *path, t_arg *arg)
{
	int		i;
	int		pcnt;
	char	**newparams;

	newparams = create_paramarry(cmd_with_param, arg);
	pcnt = 0;
	i = 0;
	while (1)
	{
		newparams[pcnt] = create_oneparam(cmd_with_param, path, &i);
		if (!newparams[pcnt])
		{
			while (pcnt > 0)
				free(newparams[--pcnt]);
			free(newparams);
			error_exit(ERR_FAILED_TO_MALLOC, arg);
		}
		pcnt++;
		if (cmd_with_param[i] == '\0')
			break ;
		i++;
	}
	newparams[pcnt] = NULL;
	return (newparams);
}

void	free_param(char **cmd_with_param)
{
	int		i;

	i = 0;
	while (cmd_with_param[i] != NULL)
		free(cmd_with_param[i++]);
	free(cmd_with_param);
	cmd_with_param = NULL;
}

void	exec_command(char *cmd, t_arg *arg)
{
	int		ret;
	char	**new_param;
	int		i;

	i = 0;
	ret = -1;
	while (ret != 0 && arg->path[i] != NULL)
	{
		new_param = create_params(cmd, arg->path[i], arg);
		ret = access(new_param[0], X_OK);
		if (ret == 0)
			ret = execve(new_param[0], new_param, NULL);
		free_param(new_param);
		i++;
	}
	if (ret != 0)
		error_exit(ERR_FAILED_TO_EXEC, arg);
}
