#include "main.h"

void	builtincmd_cd(t_arg *arg, char *read)
{
	int		i;
	int		ret;

	i = 2;
	while (read[i] == ' ')
		i++;
	ret = chdir(&read[i]);
	if (ret)
		print_error(ERR_CD_INVALIDPATH, &read[i]);
	if (arg->dbg == 1)
		builtincmd_pwd();
}
