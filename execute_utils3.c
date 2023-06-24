#include "minishell.h"

void	no_cmd_inpt(t_arg *tmp, t_list *export_list, t_list *env_list)
{
	int	i;

	i = -1;
	if (tmp->next && tmp->next->arg[1])
	{
		tmp->next->cmd = ft_strdup(tmp->next->arg[1]);
		while (tmp->next->arg[++i])
			tmp->next->arg[i] = tmp->next->arg[i + 1];
		all_cmd(tmp->next, export_list, env_list);
	}
	else
		exit (0);
}

void	close_file(int file_d, int fd[2])
{
	if (file_d)
		close(file_d);
	close(fd[1]);
	close(fd[0]);
}
