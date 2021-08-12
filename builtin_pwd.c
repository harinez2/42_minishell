#include "main.h"

void	builtincmd_pwd(void)
{
	char	path[MAX_PATH];

	getcwd(path, MAX_PATH);
	printf("%s\n", path);
}
