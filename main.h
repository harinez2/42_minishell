#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# define	MAX_ENVP				100
# define	MAX_PATH				1024

# define	PP_READ					0
# define	PP_WRITE				1

# define	ERR_ENV_INVALID			-1
# define	ERR_NOT_ENOUGH_PARAM	-2
# define	ERR_FAILED_TO_OPEN_FILE	-3
# define	ERR_PIPE				-4
# define	ERR_FAILED_TO_FORK		-5
# define	ERR_FAILED_TO_EXEC		-6
# define	ERR_FAILED_TO_MALLOC	-7
# define	ERR_CD_INVALIDPATH		-8

# define	TKN_DBLQUOTE			11
# define	TKN_SGLQUOTE			12
# define	TKN_COLON				13
# define	TKN_AMP					14
# define	TKN_SINGLE_OR			15
# define	TKN_REDIR_LEFT			16
# define	TKN_REDIR_RIGHT			17
# define	TKN_HEREDOC				18
# define	TKN_DBLANDOR			19
# define	TKN_CHAR				20

typedef struct	s_param
{
	char			*p;
	struct s_param	*next;
}	t_param;

typedef struct	s_cmd
{
	struct s_cmd	*next;
	char			*cmd;
	t_param			*param;
	int				nxtcmd_relation;
	char			**redir_in;
	char			**redir_out;
}	t_cmd;

typedef struct s_arg
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*path[100];
	int		path_cnt;
	t_cmd	*cmdlst;
	int		dbg;
}	t_arg;

// error.c
void	print_error(int errcode, char *txt);
void	error_exit(int errcode, t_arg *arg);
// lib_ft.c
size_t	ft_strlen(const char *str);
void	ft_putchars(char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// lib_ft2.c
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// lib_util.c
void	copy_array(int *to, int *from, int len, int offset_to);
void	secure_free(void *p);
void	init_arg(int argc, char **argv, char **envp, t_arg *arg);
// lib_lst.c
void	lst_print(t_cmd *c);
void	lst_addlast(t_arg *arg, char *cmdtxt, int len);
void	lst_destroy(t_arg *arg, t_cmd *cmd);
// cmd_exec.c
void	free_param(char **cmd_with_param);
void	exec_command(char *cmd, t_arg *arg);
// cmd_pipe.c
void	pipe_and_runcommand(t_arg *arg, int nestcnt);
// builtin_cd.c
void	builtincmd_cd(char *read);
// builtin_echo.c
void	builtincmd_echo(char *read);
// builtin_env.c
void	builtincmd_env(void);
// builtin_export.c
void	builtincmd_export(char **envp);
// builtin_pwd.c
void	builtincmd_pwd(void);

#endif
