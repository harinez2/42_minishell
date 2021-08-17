#include "main.h"
extern char **environ;
void	builtincmd_env(t_arg *arg)
{
	int		i;

	if (arg->dbg == 1)
		printf("<<< builtin cmd env >>>\n");
	i = 0;
	while (environ[i] != NULL)
		printf("%s\n", environ[i++]);
}
