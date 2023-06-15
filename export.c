/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:09:04 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_epxport(t_list *export_list)
{
	char	*tmp;
	char	**tmp2;
	int		i;

	while (export_list)
	{
		printf("declare -x ");
		tmp = ft_strdup(export_list->content);
		i = -1;
		while (tmp[++i])
		{
			if (tmp[i] == '=')
			{
				tmp2 = ft_split(export_list->content, '=');
				if (tmp2[1])
					printf("=\"%s\"", tmp2[1]);
				else
					printf("=\"\"");
				break ;
			}
			printf("%c", tmp[i]);
		}
		printf("\n");
		export_list = export_list->next;
	}
}

int	export_empty(t_list *export_list, t_list *env_list, char *var)
{
	int	i;

	i = 0;
	while (var[++i])
	{
		if (var[i] == '=' && var[i + 1] == '\0')
		{
			ft_lstadd_back(&export_list, ft_lstnew(var));
			ft_lstadd_back(&env_list, ft_lstnew(var));
			return (0);
		}
		else if (!var[i + 1])
			ft_lstadd_back(&export_list, ft_lstnew(var));
	}
	return (1);
}

void	same_var(t_list *export_list, t_list *env_list, char *var)
{
	t_list	*tmp;
	char	**tmp2;
	char	**tmp3;

	tmp = export_list;
	tmp3 = ft_split(var, '=');
	while (tmp)
	{
		tmp2 = ft_split(tmp->content, '=');
		if (!ft_strncmp(tmp2[0], tmp3[0], ft_strlen(tmp3[0]))
			&& ft_strlen(tmp3[0]) == ft_strlen(tmp2[0]))
		{
			my_unset(tmp2[0], export_list, env_list);
			free(tmp2);
			break ;
		}
		free(tmp2);
		tmp = tmp->next;
	}
	free(tmp3);
}

void	my_export(t_list *export_list, t_list *env_list, char *var)
{
	int		i;

	i = 0;
	if (var)
	{
		same_var(export_list, env_list, var);
		if (!ft_isalpha(var[0]))
		{
			printf("\e[0;31mminishell: export: not a valid identifier\n");
			return ;
		}
		if (!export_empty(export_list, env_list, var))
			return ;
		while (var[++i])
		{
			if (var[i] == '=' && var[i - 1] != ' '
				&& var[i + 1] != ' ' && var[i + 1] != '\0')
			{
				ft_lstadd_back(&env_list, ft_lstnew(var));
				return ;
			}
		}
		return ;
	}
	print_epxport(export_list);
}