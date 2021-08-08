#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# define	MAX_ENVP				100

# define	PP_READ					0
# define	PP_WRITE				1
# define	ERR_ENV_INVALID			-1
# define	ERR_NOT_ENOUGH_PARAM	-2
# define	ERR_FAILED_TO_OPEN_FILE	-3
# define	ERR_PIPE				-4
# define	ERR_FAILED_TO_FORK		-5
# define	ERR_FAILED_TO_EXEC		-6
# define	ERR_FAILED_TO_MALLOC	-7

typedef struct s_arg
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*path[100];
	int		path_cnt;
}	t_arg;

typedef struct	s_cmd
{
	struct s_cmd	*next;
	int				argc;
	char			**argv;
	int				op;
}	t_cmd;

// error.c
void	error_exit(int errcode, t_arg *arg);
// lib_ft.c
size_t	ft_strlen(const char *str);
void	ft_putchars(char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// lib_ft2.c
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
// lib_util.c
void	copy_array(int *to, int *from, int len, int offset_to);
void	secure_free(void *p);
void	init_arg(int argc, char **argv, char **envp, t_arg *arg);
// cmd_exec.c
void	free_param(char **cmd_with_param);
void	exec_command(char *cmd, t_arg *arg);
// cmd_pipe.c
void	pipe_and_runcommand(t_arg *arg, int nestcnt);
// builtin_echo.c
void	buitincmd_echo(char *read);
// builtin_export.c
void	buitincmd_export(char **envp);
// builtin_pwd.c
void	buitincmd_pwd(char **envp);

#endif
