/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 08:55:01 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/26 08:55:07 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	redirect(t_arg *tmp)
{
	int	file_d;

	if (tmp->next->cmd[1] == '\0')
		file_d = open(tmp->next->redfile, O_CREAT | O_RDWR | O_TRUNC);
	else
		file_d = open(tmp->next->redfile, O_CREAT | O_RDWR | O_APPEND);
	dup2(file_d, 1);
	return (file_d);
}
