#include "main.h"

void	lst_addlast(t_arg *arg, t_cmd *cmd, char *cmdtxt, int len)
{
	t_cmd	*c;
	int		i;

	c = cmd;
	while (c != NULL)
		c = c->next;
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
	c->cmd[i] = '\0';
	c->nxtcmd_relation = 0;
	c->redir_in = NULL;
	c->redir_out = NULL;
	c->next = NULL;
	cmd->next = c;
}
