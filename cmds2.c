/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 04:51:59 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// echo redirect file_name
void	my_echo1(char **cmd, int pi)
{
	int	file_d;
	int	save_out;

	save_out = 0;
	file_d = 0;
	if (cmd[1][1] == '>')
		file_d = open(cmd[2], O_CREAT | O_RDWR | O_APPEND);
	else
		file_d = open(cmd[2], O_CREAT | O_RDWR | O_TRUNC);
	save_out = dup(fileno(stdout));
	dup2(file_d, 1);
	ft_putendl_fd("", file_d);
	dup2(save_out, fileno(stdout));
	close(file_d);
}

// echo -n redirect file_name
void	my_echo2(char **cmd, int pi)
{
	int	file_d;
	int	save_out;

	save_out = 0;
	file_d = 0;
	if (cmd[2][1] == '>')
		file_d = open(cmd[3], O_CREAT | O_RDWR | O_APPEND);
	else
		file_d = open(cmd[3], O_CREAT | O_RDWR | O_TRUNC);
	save_out = dup(fileno(stdout));
	dup2(file_d, 1);
	ft_putstr_fd("", file_d);
	dup2(save_out, fileno(stdout));
	close(file_d);
}

// echo meggase rdirect file_name
void	my_echo3(char **cmd, int pi)
{
	int	file_d;
	int	save_out;

	save_out = 0;
	file_d = 0;
	if (cmd[2][1] == '>')
		file_d = open(cmd[3], O_CREAT | O_RDWR | O_APPEND);
	else
		file_d = open(cmd[3], O_CREAT | O_RDWR | O_TRUNC);
	save_out = dup(fileno(stdout));
	dup2(file_d, 1);
	ft_putendl_fd(cmd[1], file_d);
	dup2(save_out, fileno(stdout));
	close(file_d);
}

// echo -n meggase rdirect file_name
void	my_echo4(char **cmd, int pi)
{
	int	file_d;
	int	save_out;

	save_out = 0;
	file_d = 0;
	if (cmd[3][1] == '>')
		file_d = open(cmd[4], O_CREAT | O_RDWR | O_APPEND);
	else
		file_d = open(cmd[4], O_CREAT | O_RDWR | O_TRUNC);
	save_out = dup(fileno(stdout));
	dup2(file_d, 1);
	ft_putstr_fd(cmd[2], file_d);
	dup2(save_out, fileno(stdout));
	close(file_d);
}

void	my_echo(char **cmd, int pi)
{
	if (!cmd[1])
		printf("\n");
	else if (!cmd[2])
	{
		if (!ft_strncmp(cmd[1], "-n\0", 3))
			printf("");
		else
			printf("%s\n", cmd[1]);
	}
	else if (!cmd[3])
	{
		if (!ft_strncmp(cmd[1], "-", 1))
			printf("%s", cmd[2]);
		else
			my_echo1(cmd, pi);
	}
	else if (!cmd[4])
	{
		if (!ft_strncmp(cmd[1], "-", 1))
			my_echo2(cmd, pi);
		else
			my_echo3(cmd, pi);
	}
	else if (!cmd[5])
		my_echo4(cmd, pi);
}
