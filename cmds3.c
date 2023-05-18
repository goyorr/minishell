/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:04 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 11:02:05 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	my_exec_cmd_e1(char **cmd, int pi)
{
	int		file_d;
	char	*ppp[4];
	int		save_out;

	ppp[0] = cmd[0];
	ppp[1] = cmd[1];
	ppp[2] = cmd[2];
	ppp[3] = NULL;
	file_d = 0;
	save_out = dup(fileno(stdout));
	if (cmd[3][1] == '\0')
		file_d = open(cmd[4], O_CREAT | O_RDWR | O_TRUNC);
	else
		file_d = open(cmd[4], O_CREAT | O_RDWR | O_APPEND);
	dup2(file_d, 1);
	if (!fork())
	{
		if (execve (cmd[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd[0]), ppp, NULL) == -1)
					printf("\e[0;31mminishell: command nt found\n");
			}
		}
	}
	close(file_d);
	dup2(save_out, fileno(stdout));
	wait(0);
}

//redirect filename with flag
void	my_exec_cmd_d1(char **cmd, int pi)
{
	int		file_d;
	char	*ppp[3];
	int		save_out;

	ppp[0] = cmd[0];
	ppp[1] = cmd[1];
	ppp[2] = NULL;
	file_d = 0;
	save_out = dup(fileno(stdout));
	if (cmd[2][1] == '\0')
		file_d = open(cmd[3], O_CREAT | O_RDWR | O_TRUNC);
	else
		file_d = open(cmd[3], O_CREAT | O_RDWR | O_APPEND);
	dup2(file_d, 1);
	if (!fork())
	{
		if (execve (cmd[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd[0]), ppp, NULL) == -1)
					printf("\e[0;31mminishell: command nt found\n");
			}
		}
	}
	close(file_d);
	dup2(save_out, fileno(stdout));
	wait(0);
}

void	my_exec_cmd(char **cmd, int pi)
{
	if (!cmd[1])
		my_exec_cmd_a1(cmd, pi);
	else if (!cmd[2])
		my_exec_cmd_b1(cmd, pi);
	else if (!cmd[3])
	{
		if (!ft_strncmp(cmd[1], "-", 1))
			my_exec_cmd_c1(cmd, pi);
		else
			my_exec_cmd_c2(cmd, pi);
	}
	else if (!cmd[4])
		my_exec_cmd_d1(cmd, pi);
	else if (!cmd[5])
		my_exec_cmd_e1(cmd, pi);
}

//command 											1

//command file_name									2
//command flag-------2

//command redirecit(trunc / append) file_name 		3
//command flag file_name 							3

//command flag redirecit(trunc / append) file_name  4

//command flag file_name redirect file_name			5
