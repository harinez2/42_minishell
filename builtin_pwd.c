#include "main.h"

void	builtincmd_pwd(t_arg *arg)
{
	char	path[MAX_PATH];

	if (arg->dbg == 1)
		printf("<<< builtin cmd pwd >>>\n");
	getcwd(path, MAX_PATH);
	printf("%s\n", path);
}
