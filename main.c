#include "main.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

static int	is_delim_or_redir(char c)
{
	if (c == ';' || c == '|' || c == '&' || c == '>' || c == '<' || c == '"' || c == '\'')
		return (1);
	else
		return (0);
}

static void	skip_whitespace(char *read, int *i)
{
	while (is_whitespace(read[*i]))
		(*i)++;
}

// lexer
int	get_token(char *read, int *i)
{
	int		ret;

	if (read[*i] == '"')
	{
		while (read[++(*i)] != '"')
			;
		ret = TKN_DBLQUOTE;
	}
	else if (read[*i] == '\'')
	{
		while (read[++(*i)] != '\'')
			;
		ret = TKN_SGLQUOTE;
	}
	else if (read[*i] == ';')
		ret = TKN_COLON;
	else if (read[*i] == '&' && read[*i + 1] != '&')
		ret = TKN_AMP;
	else if (read[*i] == '|' && read[*i + 1] != '|')
		ret = TKN_SINGLE_OR;
	else if (read[*i] == '<')
		ret = TKN_REDIR_LEFT;
	else if (read[*i] == '>' && read[*i + 1] != '>')
		ret = TKN_REDIR_RIGHT;
	else if (read[*i] == '>' && read[*i + 1] == '>')
	{
		(*i)++;
		ret = TKN_HEREDOC;
	}
	else if (ft_strncmp(&read[*i], "||", 2) == 0
		|| ft_strncmp(&read[*i], "&&", 2) == 0)
	{
		(*i)++;
		ret = TKN_DBLANDOR;
	}
	else
	{
		while (!is_whitespace(read[*i]) && read[*i] != '\0' && !is_delim_or_redir(read[*i]))
			(*i)++;
		return (TKN_CHAR);
	}
	(*i)++;
	return (ret);
}

static void	print_token_type(int type)
{
	if (type == TKN_DBLQUOTE)
		printf("<dbl quote>");
	else if (type == TKN_SGLQUOTE)
		printf("<sgl quote>");
	else if (type == TKN_COLON)
		printf("<colon    >");
	else if (type == TKN_AMP)
		printf("<amp      >");
	else if (type == TKN_SINGLE_OR)
		printf("<single or>");
	else if (type == TKN_REDIR_LEFT)
		printf("<rdr left >");
	else if (type == TKN_REDIR_RIGHT)
		printf("<rdr right>");
	else if (type == TKN_HEREDOC)
		printf("<heredoc  >");
	else if (type == TKN_DBLANDOR)
		printf("<dbl andor>");
	else if (type == TKN_CHAR)
		printf("<char     >");
}

static int	run_builtincmd(char *read, t_arg *arg)
{
	if (ft_strncmp("echo ", read, 5) == 0)
		builtincmd_echo(read);
	else if (ft_strncmp("export", read, 7) == 0)
		builtincmd_export(arg->envp);
	else if (ft_strncmp("env", read, 3) == 0)
		builtincmd_env();
	else if (ft_strncmp("pwd", read, 4) == 0)
		builtincmd_pwd();
	else if (ft_strncmp("cd ", read, 3) == 0)
		builtincmd_cd(arg, read);
	else
		return (0);
	return (1);
}

static void		add_tree(t_arg *arg, int type, char *cmdtxt, int len)
{
	if (type == TKN_DBLQUOTE)
		lst_addlast(arg, PNT_PARAM, cmdtxt, len);
	else if (type == TKN_SGLQUOTE)
		;
	else if (type == TKN_COLON)
		;
	else if (type == TKN_AMP)
		;
	else if (type == TKN_SINGLE_OR)
		;
	else if (type == TKN_REDIR_LEFT)
		;
	else if (type == TKN_REDIR_RIGHT)
		;
	else if (type == TKN_HEREDOC)
		;
	else if (type == TKN_DBLANDOR)
		;
	else if (type == TKN_CHAR)
	{
		lst_addlast(arg, PNT_CMD, cmdtxt, len);
	}
}

static int	command_recog(char *read, t_arg *arg)
{
	pid_t	pid;
	int		status;
	int		i;
	int		token_type;
	int		starti;

	run_builtincmd(read, arg);
	
	i = 0;
	token_type = 1;
	while (token_type)
	{
		skip_whitespace(read, &i);
		if (read[i] == '\0')
			break ;
		starti = i;
		token_type = get_token(read, &i);
		if (arg->dbg)
		{
			print_token_type(token_type);
			char *s = ft_substr(read, starti, i - starti);
			printf(" %2d-%2d : %s\n", starti, i, s);
			secure_free(s);
		}
		add_tree(arg, token_type, &read[starti], i - starti);
	}
	if (arg->dbg == 1)
		lst_print(arg->cmdlst);
	lst_destroy(arg);

	return (0);

	// exec_command("echo a", arg);

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
		secure_free(arg->path[0]);
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
	if (argc >= 2 && ft_strncmp("-d", argv[1], 3) == 0)
		arg.dbg = 1;
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
