#include "main.h"

void	buitincmd_pwd(void)
{
	char	path[MAX_PATH];

	getcwd(path, MAX_PATH);
	printf("%s\n", path);
}
