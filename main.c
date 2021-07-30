#include "main.h"

static void	buitincmd_echo(char *read)
{
	printf("%s\n", read + 5);
}

static int	command_recog(char *read)
{
	if (ft_strncmp("exit", read, 5) == 0)
		return (-1);
	else if (ft_strncmp("echo ", read, 5) == 0)
		buitincmd_echo(read);
	else
		printf("Command not found : %s\n", read);
	return (0);
}

int	main(void)
{
	char	*read;
	int		ret;

	while (1)
	{
		read = readline("minishell> ");
		ret = command_recog(read);
		if (ret == -1)
			break ;
		secure_free(read);
	}
	secure_free(read);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	pid_t	pid;
// 	int		status;
// 	t_arg	arg;

// 	arg.path[0] = NULL;
// 	init_arg(argc, argv, envp, &arg);
// 	if (argc < 5)
// 		error_exit(ERR_NOT_ENOUGH_PARAM, &arg);
// 	pid = fork();
// 	if (pid == -1)
// 		error_exit(ERR_FAILED_TO_FORK, &arg);
// 	else if (pid == 0)
// 		pipe_and_runcommand(&arg, 0);
// 	waitpid(pid, &status, 0);
// 	free(arg.path[0]);
// 	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
// 		return (0);
// 	else
// 		return (-1);
// }
