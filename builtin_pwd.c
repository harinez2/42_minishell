#include "main.h"

void	buitincmd_pwd(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PWD=", envp[i], 4) == 0)
		{
			printf("%s\n", &envp[i][4]);
			break ;
		}
		i++;
	}
}
