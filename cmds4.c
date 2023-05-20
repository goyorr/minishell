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
void	my_exec_cmd_a1(t_arg *cmd, int pi)
{
	char	*ppp[3];
	int		save_out;
	int		save_in;

	ppp[0] = cmd->arg[0];
	ppp[1] = NULL;
	ppp[2] = NULL;
	if (pi == FPIPE)
	{
		save_out = dup(fileno(stdout));
		dup2(g_fd[1], 1);
	}
	else if (pi == PIPE)
	{
		save_out = dup(fileno(stdout));
		save_in = dup(fileno(stdin));
		dup2(g_fd[1], 1);
		dup2(g_fd[0], 0);
	}
	else if (pi == EPIPE)
	{
		save_in = dup(fileno(stdin));
		dup2(g_fd[0], 0);
		close(g_fd[1]);
	}
	if (!fork())
	{
		if (execve (cmd->arg[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->arg[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd->cmd), ppp, NULL) == -1)
				{
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
				}
			}
		}
	}
	if (pi == EPIPE)
	{
		close(g_fd[0]);
		dup2(save_in, fileno(stdin));
	}
	else if (pi == FPIPE)
	{
		close(g_fd[1]);
		dup2(save_out, fileno(stdout));
	}
	else if (pi == PIPE)
	{
		close(g_fd[1]);
		close(g_fd[0]);
		dup2(save_out, fileno(stdout));
	}
	wait(0);
}

void	my_exec_cmd_b1(t_arg *cmd, int pi)
{
	char	*ppp[3];
	int		save_out;
	int		save_in;

	save_out = dup(fileno(stdin));
	ppp[0] = cmd->arg[0];
	ppp[1] = cmd->arg[1];
	ppp[2] = NULL;

	if (pi == FPIPE)
	{
		save_out = dup(fileno(stdout));
		dup2(g_fd[1], 1);
	}
	else if (pi == PIPE)
	{
		save_out = dup(fileno(stdout));
		save_in = dup(fileno(stdin));
		dup2(g_fd[1], 1);
		dup2(g_fd[0], 0);
	}
	else if (pi == EPIPE)
	{
		save_in = dup(fileno(stdin));
		dup2(g_fd[0], 0);
		close(g_fd[1]);
	}
	if (!fork())
	{
		if (execve (cmd->arg[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->arg[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd->cmd), ppp, NULL) == -1)
				{
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
				}
			}
		}
	}
	if (pi == EPIPE)
	{
		close(g_fd[0]);
		dup2(save_in, fileno(stdin));
	}
	else if (pi == FPIPE)
	{
		close(g_fd[1]);
		dup2(save_out, fileno(stdout));
	}
	else if (pi == PIPE)
	{
		close(g_fd[1]);
		close(g_fd[0]);
		dup2(save_out, fileno(stdout));
	}
	wait(0);
}

void	my_exec_cmd_c1(t_arg *cmd, int pi)
{
	char	*ppp[4];
	int		save_out;
	int		save_in;

	ppp[0] = cmd->arg[0];
	ppp[1] = cmd->arg[1];
	ppp[1] = cmd->arg[2];
	ppp[2] = NULL;
	if (pi == FPIPE)
	{
		save_out = dup(fileno(stdout));
		dup2(g_fd[1], 1);
	}
	else if (pi == PIPE)
	{
		save_out = dup(fileno(stdout));
		save_in = dup(fileno(stdin));
		dup2(g_fd[1], 1);
		dup2(g_fd[0], 0);
	}
	else if (pi == EPIPE)
	{
		save_in = dup(fileno(stdin));
		dup2(g_fd[0], 0);
		close(g_fd[1]);
	}
	if (!fork())
	{
		if (execve (cmd->arg[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->arg[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd->cmd), ppp, NULL) == -1)
				{
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
				}
			}
		}
	}
	if (pi == EPIPE)
	{
		close(g_fd[0]);
		dup2(save_in, fileno(stdin));
	}
	else if (pi == FPIPE)
	{
		close(g_fd[1]);
		dup2(save_out, fileno(stdout));
	}
	else if (pi == PIPE)
	{
		close(g_fd[1]);
		close(g_fd[0]);
		dup2(save_out, fileno(stdout));
	}
	wait (0);
}

//redirect filename no flag
void	my_exec_cmd_c2(t_arg *cmd, int pi)
{
	int		file_d;
	char	*ppp[3];

	ppp[0] = cmd->arg[0];
	ppp[1] = NULL;
	ppp[2] = NULL;
	file_d = 0;
	if (pi == TRNC)
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_TRUNC | 0644);
	else
		file_d = open(cmd->next->redfile, O_CREAT | O_RDWR | O_APPEND | 0644);
	dup2(file_d, 1);
	if (!fork())
	{
		if (execve (cmd->arg[0], ppp, NULL) == -1)
		{
			if (execve (ft_strjoin("/bin/", cmd->arg[0]), ppp, NULL) == -1)
			{
				if (execve (ft_strjoin("/usr/bin/", cmd->cmd), ppp, NULL) == -1)
				{
					printf("\e[0;31mminishell: command not found\n");
					exit (0);
				}
			}
		}
	}
	close(file_d);
	wait(0);
}
