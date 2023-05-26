/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 11:02:59 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	all_cmd(t_arg *cmd, t_list *export_list, t_list *env_list)
{
	if (!ft_strncmp(cmd->cmd, "pwd\0", 4))
		my_pwd();
	else if (!ft_strncmp(cmd->cmd, "exit\0", 5))
		my_exit();
	else if (!ft_strncmp(cmd->cmd, "echo\0", 5))
		my_echo(cmd);
	else if (!ft_strncmp(cmd->cmd, "cd\0", 3))
		my_cd(cmd);
	else if (!ft_strncmp(cmd->cmd, "env\0", 4))
		my_env(env_list);
	else if (!ft_strncmp(cmd->cmd, "export\0", 6))
		my_export(export_list, env_list, cmd->arg[1]);
	else if (!ft_strncmp(cmd->cmd, "unset\0", 6))
		my_unset(cmd, export_list, env_list);
	else
	{
		if (execve(cmd->cmd, cmd->arg, NULL) == -1)
			if (execve(ft_strjoin("/bin/", cmd->cmd), cmd->arg, NULL) == -1)
				if (execve(ft_strjoin("/usr/bin/", cmd->cmd), cmd->arg, NULL)
					== -1)
					printf("\e[0;31mminishell: command not found\n");
	}
	exit (0);
}

void	rd_line(t_list *export_list, t_list *env_list)
{
	char	*tmp;
	char	*str;

	str = readline("\e[0;32mminishell ➜ \e[m");
	if (str[0])
	{
		add_history(str);
		tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
		ft_strlcpy(tmp, str, ft_strlen(str) + 1);
		if (!ft_parsing(tmp) || !token_line(str, export_list, env_list))
			write(1, "syntax error\n", 13);
		free(str);
	}
}

int	main(int ac, char **av, char *env[])
{
	t_list	*env_list;
	t_list	*export_list;
	int		i;

	(void)av;
	(void)ac;
	signal(3, sighandler);
	i = -1;
	while (env[++i])
		ft_lstadd_back(&env_list, ft_lstnew(env[i]));
	i = -1;
	while (env[++i])
		ft_lstadd_back(&export_list, ft_lstnew(env[i]));
	while (1)
		rd_line(export_list, env_list);
}
