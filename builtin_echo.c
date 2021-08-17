#include "main.h"

void	builtincmd_echo(t_arg *arg, char *read)
{
	if (arg->dbg == 1)
		printf("<<< builtin cmd echo >>>\n");
	printf("%s\n", read + 5);
}
