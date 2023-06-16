/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:52:35 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 09:47:59 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	hered_check(t_arg *tmp)
{
	while (tmp)
	{
		if (!ft_strncmp(tmp->cmd, "<<", 3))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	**alloc(t_arg	*file)
{
	int		i;
	char	**delem;

	i = 0;
	while (file && file->next && !ft_strncmp(file->next->cmd, "<<", 3))
	{
		i++;
		file = file->next;
	}
	delem = malloc(sizeof(char *) * i + 1);
	return (delem);
}

int	here_doc2(t_arg *tmp, int fd[2])
{
	char	**delimiter;
	int		file_d;
	char	*input;
	t_arg	*file;
	int		i;

	delimiter = NULL;
	file_d = 0;
	i = 0;
	file = tmp;
	if (file->next && (!ft_strncmp(file->next->cmd, ">", 2)
			|| !ft_strncmp(file->next->cmd, ">>", 3)))
		file = file->next;
	delimiter = alloc(file);
	while (file && file->next && !ft_strncmp(file->next->cmd, "<<", 3))
	{
		delimiter[i] = ft_strdup(file->next->redfile);
		i++;
		file = file->next;
	}
	i--;
	file = NULL;
	while (1)
	{
		if (!tmp->next || tmp->next->cmd[0] == '|')
			break ;
		if (!ft_strncmp(tmp->next->cmd, ">", 2)
			|| !ft_strncmp(tmp->next->cmd, ">>", 3))
		{
			file = tmp;
			tmp = tmp->next;
		}
		input = readline(">");
		while (1)
		{
			if (!ft_strncmp(delimiter[i], input, ft_strlen(input))
				&& (ft_strlen(input) == ft_strlen(delimiter[i])))
				break ;
			if (!tmp->next->next || tmp->next->next->cmd[0] == '|')
				ft_putendl_fd(input, fd[1]);
			input = readline(">");
		}
		i--;
		tmp = tmp->next;
	}
	if (file)
		file_d = redirect(file);
	return (file_d);
}

void	here_doc1(t_arg *tmp)
{
	char	*delimiter;
	char	*input;
	int		file_d;

	file_d = 0;
	delimiter = ft_strdup(tmp->next->cmd);
	while (1)
	{
		input = readline(">");
		if (!ft_strncmp(delimiter, input, ft_strlen(input))
			&& (ft_strlen(input) == ft_strlen(delimiter)))
			break ;
	}
}

int	here_doc(t_arg *tmp, int fd[2])
{
	t_arg	*tmp2;

	tmp2 = tmp;
	if (!ft_strncmp(tmp->cmd, "<<", 3))
	{
		here_doc1(tmp);
		tmp2 = tmp->next;
	}
	return (here_doc2(tmp2, fd));
}
