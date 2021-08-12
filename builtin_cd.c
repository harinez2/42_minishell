#include "main.h"

void	builtincmd_cd(char *read)
{
	int		i;
	int		ret;

	i = 2;
	while (read[i] == ' ')
		i++;
	ret = chdir(&read[i]);
	if (ret)
		print_error(ERR_CD_INVALIDPATH, &read[i]);
	builtincmd_pwd();
}
