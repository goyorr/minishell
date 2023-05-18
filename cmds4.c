/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:02:09 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 11:02:17 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//command only
void	my_exec_cmd_a1(char **cmd, int pi)
{
	char	*ppp[3];

	ppp[0] = cmd[0];
	ppp[1] = NULL;
	ppp[2] = NULL;
	if (!fork())
	{
		if (execve (cmd[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd[0]), ppp, NULL) == -1)
					printf("\e[0;31mminishell: command not found\n");
			}
		}
	}
	wait (0);
}

void	my_exec_cmd_b1(char **cmd, int pi)
{
	char	*ppp[3];

	ppp[0] = cmd[0];
	ppp[1] = cmd[1];
	ppp[2] = NULL;
	if (!fork())
	{
		// if ()
		if (execve (cmd[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd[0]), ppp, NULL) == -1)
					printf("\e[0;31mminishell: command not found\n");
			}
		}
	}
	wait (0);
}

void	my_exec_cmd_c1(char **cmd, int pi)
{
	char	*ppp[4];

	ppp[0] = cmd[0];
	ppp[1] = cmd[1];
	ppp[2] = cmd[2];
	ppp[3] = NULL;
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
	wait (0);
}

//redirect filename no flag
void	my_exec_cmd_c2(char **cmd, int pi)
{
	int		file_d;
	char	*ppp[3];
	int		save_out;

	ppp[0] = cmd[0];
	ppp[1] = NULL;
	ppp[2] = NULL;
	file_d = 0;
	save_out = dup(fileno(stdout));
	if (cmd[1][1] == '\0')
		file_d = open(cmd[2], O_CREAT | O_RDWR | O_TRUNC);
	else
		file_d = open(cmd[2], O_CREAT | O_RDWR | O_APPEND);
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
