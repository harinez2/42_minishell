#include "main.h"
extern char **environ;
void	buitincmd_env(void)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
		printf("%s\n", environ[i++]);
}
