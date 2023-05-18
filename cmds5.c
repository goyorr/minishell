/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 06:33:10 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/16 06:33:11 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	my_pwd2(char **cmd)
{
	char	*pwd;
	int		save_out;
	int		file_d;

	pipe(fd);
	pwd = getcwd(NULL, 0);
	save_out = dup(fileno(stdout));
	dup2(fd[1], 1);
	printf ("%s\n", pwd);
	close(fd[1]);
	dup2(save_out, fileno(stdout));
}

void	my_pwd(char **cmd, int pi)
{
	char	*pwd;
	int		file_d;
	int		save_out;

	save_out = 0;
	file_d = 0;
	if (pi)
		my_pwd2(cmd);
	else
	{
		pwd = getcwd(NULL, 0);
		if (cmd[1])
		{
			if (cmd[1][0] != '>' || !cmd[2])
			{
				printf("parse error\n");
				return ;
			}
			if (cmd[1][1] == '>')
				file_d = open(cmd[2], O_CREAT | O_RDWR | O_APPEND);
			else
				file_d = open(cmd[2], O_CREAT | O_RDWR | O_TRUNC);
			save_out = dup(fileno(stdout));
			dup2(file_d, 1);
			ft_putstr_fd(pwd, file_d);
			dup2(save_out, fileno(stdout));
			close(file_d);
		}
		else
			printf ("%s\n", pwd);
	}
}

void	my_exit(void)
{
	exit (printf("exit\n"));
}
