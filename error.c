#include "main.h"

void	print_error(int errcode, char *txt)
{
	if (errcode == ERR_CD_INVALIDPATH)
	{
		write(2, "Error : ", 8);
		write(2, txt, ft_strlen(txt));
		perror(" ");
	}
}

void	error_exit(int errcode, t_arg *arg)
{
	if (errcode == ERR_ENV_INVALID)
		perror("Error");
	else if (errcode == ERR_NOT_ENOUGH_PARAM)
		perror("Error");
	else if (errcode == ERR_FAILED_TO_OPEN_FILE)
		perror("Error");
	else if (errcode == ERR_PIPE)
		perror("Error");
	else if (errcode == ERR_FAILED_TO_FORK)
		perror("Error");
	else if (errcode == ERR_FAILED_TO_EXEC)
		perror("Error");
	else if (errcode == ERR_FAILED_TO_MALLOC)
		perror("Error");
	else
		perror("Error");
	if (arg != NULL)
		free(arg->path[0]);
	exit(-1);
}
