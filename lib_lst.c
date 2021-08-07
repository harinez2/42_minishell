#include "main.h"

void	lst_addlast(t_cmd *cmd, char *s, int len)
{
	t_cmd	*c;
	int		i;

	c = cmd;
	while (c != NULL)
		c = cmd->next;
	c = malloc(sizeof(t_cmd));
	if (!c)
		error_exit();
	c->argv = malloc(sizeof(char) * (len + 1));
	if (!c->argv)
		error_exit();
	i = 0;
	while (i < len)
	{
		c->argv[i] = s[i];
		i++;
	}
	c->argv[i] = '\0';
	c->next = NULL;
}
