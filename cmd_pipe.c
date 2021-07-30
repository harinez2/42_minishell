#include "main.h"

static void	connect_pipe(int old, int new, t_arg *arg)
{
	int		ret;

	ret = dup2(old, new);
	if (ret == -1)
		error_exit(ERR_PIPE, arg);
	ret = close(old);
	if (ret == -1)
		error_exit(ERR_PIPE, arg);
}

static int	open_infile(char *filename, t_arg *arg)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_FAILED_TO_OPEN_FILE, arg);
	return (fd);
}

static int	open_outfile(char *filename, t_arg *arg)
{
	int		fd;
	char	outfilepath[300];

	ft_strlcpy(outfilepath, "./", 3);
	ft_strlcat(outfilepath, filename, ft_strlen(filename) + 3);
	fd = open(outfilepath, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		error_exit(ERR_FAILED_TO_OPEN_FILE, arg);
	return (fd);
}

void	pipe_and_runcommand(t_arg *arg, int nestcnt)
{
	pid_t	pid;
	int		pp[2];

	pipe(pp);
	pid = fork();
	if (pid == -1)
		error_exit(ERR_FAILED_TO_FORK, arg);
	else if (pid == 0)
	{
		close(pp[PP_READ]);
		connect_pipe(pp[PP_WRITE], 1, arg);
		if (nestcnt >= arg->argc - 5)
		{
			connect_pipe(open_infile(arg->argv[1], arg), 0, arg);
			exec_command(arg->argv[2], arg);
		}
		pipe_and_runcommand(arg, nestcnt + 1);
	}
	close(pp[PP_WRITE]);
	connect_pipe(pp[PP_READ], 0, arg);
	if (nestcnt == 0)
		connect_pipe(open_outfile(arg->argv[arg->argc - 1], arg), 1, arg);
	exec_command(arg->argv[arg->argc - 2 - nestcnt], arg);
}
