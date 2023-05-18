/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:52:09 by zel-kach          #+#    #+#             */
/*   Updated: 2023/05/14 04:52:10 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include "libft/libft.h"
#include <string.h>



int fd[2];
/*---commands---*/
void	all_cmd(char **cmd, t_list *export_list, t_list *env_list, int pi);
void	my_pwd(char **cmd, int pi);
void	my_exit(void);
void	my_cd(char *cmd, int pi);
void	my_export(t_list *export_list, t_list *env_list, char *var, int pi);
void	my_env(t_list *env, int pi);
void	my_unset(t_list *env, int pi);
void	my_exec_cmd(char **cmd, int pi);
void	my_exec_cmd_a1(char **cmd, int pi);
void	my_exec_cmd_b1(char **cmd, int pi);
void	my_exec_cmd_c1(char **cmd, int pi);
void	my_exec_cmd_c2(char **cmd, int pi);
void	my_exec_cmd_d1(char **cmd, int pi);
void	my_exec_cmd_e1(char **cmd, int pi);
void	my_echo(char **cmd, int pi);
void	my_echo1(char **cmd, int pi);
void	my_echo2(char **cmd, int pi);
void	my_echo3(char **cmd, int pi);
void	my_echo4(char **cmd, int pi);

/*---signals---*/
void	sighandler(int signal);

/*---utils---*/


/*---parsing---*/

typedef enum	type{
	tokenword,
	tokenpipe,
	redirections,
	NONE
}e_type;

typedef struct	s_token{
	char *cmd;
	e_type type;
	struct s_token *next;
}t_toke

typedef struct	s_arg{
	char *cmd;
	char *redfile;
	char **arg;
	e_type type;
	struct s_arg *next;
}t_arg;

typedef struct	s_data
{
	int		i;
	char	*str;
	
}t_data;

t_token	*ft_tokenlast(t_token *lst);
t_token	*new_token(char *cmd, e_type type);
t_arg	*newarg_token(char *cmd, e_type type);
t_arg	*ft_arglast(t_arg *lst);
e_type	get_type(char *str);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	add_free(t_data *data, t_token **token);
void	ft_argadd_back(t_arg **lst, t_arg *new);
void	is_token(t_data *data, char *line);
void	default_cmd(t_data *data, char *line);
void	free_tabb(char **tabb);
void	is_arg(t_token *tmp, t_arg **arg);
void	free_list(t_token *tabb);
void	append_word(t_token **tmp, t_arg **arg);
void	apend_redirection(t_token **tmp, t_arg **arg);
char	**alloc_arg(char **args, char *cmd);
char	*append_char(char *str, char c);
char	*print_token(int n);
char	*double_quotes(char *line,char *str, int *len);
char	*single_quotes(char *line,char *str, int *len);
char	*char_to_str(char *line);
char	*get_token(char *line);
int		get_end(char *line, int i);
int 	token_line(char *line, t_list *export_list, t_list *env_list);
int		check_token(char c);
int		is_char(char c);
int		ft_parsing_2(t_token **token);
int		ft_parsing(char *tmp);

#endif
