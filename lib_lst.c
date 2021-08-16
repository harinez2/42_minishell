#include "main.h"

void	lst_print(t_cmd *c)
{
	int			i;
	int			j;
	// t_param		*ptmp;

	printf("---lst_print_start---\n");
	i = 0;
	while (c != NULL)
	{
		printf("[%d]\n", i);
		printf("  cmd      : %s\n", c->cmd);
		if (c->param_cnt == 0)
			printf("    param  : <NULL>\n");
		else
		{
			j = 0;
			while (j < c->param_cnt)
				printf("    param  : %s\n", c->param[j++]);
		}
		printf("  nxtrel   : %d\n", c->nxtcmd_relation);
		if (c->redir_in == NULL)
			printf("  redir_in : <NULL>\n");
		else
			printf("  redir_in : %s\n", *(c->redir_in));
		if (c->redir_out == NULL)
			printf("  redir_out: <NULL>\n");
		else
			printf("  redir_out: %s\n", *(c->redir_out));
		c = c->next;
		i++;
	}
	printf("---lst_print_end---\n");
}

t_cmd	*create_cmdnode(t_arg *arg, char *cmdtxt, int len)
{
	t_cmd	*c;
	int		i;

	c = malloc(sizeof(t_cmd));
	if (!c)
		error_exit(ERR_FAILED_TO_MALLOC, arg);
	c->cmd = malloc(sizeof(char) * (len + 1));
	if (!c->cmd)
		error_exit(ERR_FAILED_TO_MALLOC, arg);
	i = 0;
	while (i < len)
	{
		(c->cmd)[i] = cmdtxt[i];
		i++;
	}
	(c->cmd)[i] = '\0';
	c->param[0] = NULL;
	c->param_cnt = 0;
	c->nxtcmd_relation = 0;
	c->redir_in = NULL;
	c->redir_out = NULL;
	c->next = NULL;
	return (c);
}

t_cmd	*lst_get_last_cmdnode(t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

int	lst_addlast(t_arg *arg, int addpoint, char *cmdtxt, int len)
{
	t_cmd	*newnode;
	t_cmd	*ctmp;

	if (addpoint == PNT_CMD)
	{
		newnode = create_cmdnode(arg, cmdtxt, len);
		if (arg->cmdlst == NULL)
			arg->cmdlst = newnode;
		else
		{
			ctmp = arg->cmdlst;
			while (ctmp->next != NULL)
				ctmp = ctmp->next;
			ctmp->next = newnode;
		}
	}
	else if (addpoint == PNT_PARAM)
	{
		newnode = malloc(sizeof(char) * (len + 1));
		if (!newnode)
			error_exit(ERR_FAILED_TO_MALLOC, arg);
		ctmp = lst_get_last_cmdnode(arg->cmdlst);
		if (ctmp == NULL)
			return (-1);//parsing error
		else
		{
			ctmp->param[ctmp->param_cnt++] = ft_substr(cmdtxt, 0, len);
			ctmp->param[ctmp->param_cnt] = NULL;
		}
	}
	return (0);
}

void	lst_destroy(t_arg *arg)
{
	t_cmd	*c;
	int		i;

	while (arg->cmdlst != NULL)
	{
		c = arg->cmdlst;
		arg->cmdlst = arg->cmdlst->next;
		i = 0;
		while (i < c->param_cnt)
			secure_free(c->param[i++]);
		if (c->redir_in != NULL)
			secure_free(c->redir_in);
		if (c->redir_out != NULL)
			secure_free(c->redir_out);
		secure_free(c->cmd);
		secure_free(c);
	}
}
