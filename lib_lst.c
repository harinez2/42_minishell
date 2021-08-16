#include "main.h"

void	lst_print(t_cmd *c)
{
	int			i;
	t_param		*ptmp;

	printf("---lst_print_start---\n");
	i = 0;
	while (c != NULL)
	{
		printf("[%d]\n", i);
		printf("  cmd      : %s\n", c->cmd);
		if (c->param != NULL)
		{
			ptmp = c->param;
			while (ptmp != NULL)
			{
				printf("    param  : %s\n", ptmp->p);
				ptmp = ptmp->next;
			}
		}
		else
			printf("    param  : <NULL>\n");
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
	c->param = NULL;
	c->nxtcmd_relation = 0;
	c->redir_in = NULL;
	c->redir_out = NULL;
	c->next = NULL;
	return (c);
}

void	lst_addlast(t_arg *arg, char *cmdtxt, int len)
{
	t_cmd	*newnode;
	t_cmd	*ctmp;

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

void	lst_destroy(t_arg *arg)
{
	t_cmd	*c;

	while (arg->cmdlst != NULL)
	{
		c = arg->cmdlst;
		arg->cmdlst = arg->cmdlst->next;
		if (c->param != NULL)
			secure_free(c->param);
		if (c->redir_in != NULL)
			secure_free(c->redir_in);
		if (c->redir_out != NULL)
			secure_free(c->redir_out);
		secure_free(c->cmd);
		secure_free(c);
	}
}
