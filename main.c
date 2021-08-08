#include "main.h"

int	lexical_analysis(char *read)
{
	// t_cmd	*c;
	int		i;
	int		j;
	int		flg;
	flg = 0;
	// c = NULL;
	i = 0;
	while (read[i])
	{
		if (read[i] == '"')
		{
			j = 0;
			while (read[++i] != '"')
				j++;
			printf("%c", read[i]);
			flg++;
		}
		else if (read[i] == ';'
			|| (read[i] == '&' && read[i + 1] != '&'))
		{
			printf("%c\n", read[i]);
		}
		else if (read[i] == '|' && read[i + 1] != '|')
		{
			printf("<pipe>");
		}
		else if (read[i] == '<')
		{
			printf("<redirect_in>");
		}
		else if (read[i] == '>' && read[i + 1] != '>')
		{
			printf("<redirect_out>");
		}
		else if (read[i] == '>' && read[i + 1] == '>')
		{
			printf("<here_document>");
			i++;
		}
		else if (ft_strncmp(&read[i], "||", 2) == 0
			|| ft_strncmp(&read[i], "&&", 2) == 0)
		{
			printf("%c%c\n", read[i], read[i + 1]);
			i++;
		}
		else
		{
			printf("%c", read[i]);
		}
		i++;
	}

	// flg = 0;
	// if (read[i] == '"')
	// 	flg--;
	// printf("%c", read[i]);

	printf("\n");
	return (0);
}

static int	run_builtincmd(char *read, t_arg *arg)
{
	if (ft_strncmp("echo ", read, 5) == 0)
		buitincmd_echo(read);
	else if (ft_strncmp("export", read, 7) == 0)
		buitincmd_export(arg->envp);
	else if (ft_strncmp("pwd", read, 4) == 0)
		buitincmd_pwd();
	else if (ft_strncmp("cd ", read, 3) == 0)
		buitincmd_cd(read);
	else
		return (0);
	return (1);
}

static int	command_recog(char *read, t_arg *arg)
{
	pid_t	pid;
	int		status;

	// lexical_analysis(read);
	// return (0);

	// exec_command("echo a", arg);

	// char *x = malloc(sizeof(char) * 7);
	// x[0] = 'e';
	// x[1] = 'c';
	// x[2] = 'h';
	// x[3] = 'o';
	// x[4] = ' ';
	// x[5] = 'a';
	// x[6] = '\0';
	// exec_command(x, arg);
	// free(x);

	if (ft_strncmp("exit", read, 5) == 0)
		return (-1);
	else if (run_builtincmd(read, arg))
		;
	else
	{
		pid = fork();
		if (pid == -1)
			error_exit(ERR_FAILED_TO_FORK, arg);
		else if (pid == 0)
			exec_command(read, arg);
		waitpid(pid, &status, 0);
		free(arg->path[0]);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			return (0);
		else
			return (-1);
	}

	// else
	// 	printf("Command not found : %s\n", read);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*read;
	int		ret;
	t_arg	arg;

	arg.path[0] = NULL;
	init_arg(argc, argv, envp, &arg);
	while (1)
	{
		read = readline("minishell> ");
		ret = command_recog(read, &arg);
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
