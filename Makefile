# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 04:51:47 by zel-kach          #+#    #+#              #
#    Updated: 2023/07/08 12:01:22 by zel-kach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c cmds.c execute_utils.c execute.c \
	 redirect.c echo.c here_doc.c export.c unset.c \
	 arg.c parsing_2.c parsing.c token_2.c token.c \
	 utils.c signals.c export_helper.c execute_utils2.c \
	 execute2.c pwd.c here_doc_utils.c utils_2.c execute_utils3.c \
	 ft_free.c cmds_2.c parsing_3.c parsing_4.c arg_2.c redirect22.c \

OBJ = ${SRC:.c=.o}

libfta = ./libft/libft.a

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include

all: libftm ${NAME}

${NAME}: ${OBJ}
		${CC} ${OBJ} ${libfta} -L $(shell brew --prefix readline)/lib -lreadline -o $@ 
%.o: %.c minishell.h ${libfta}
		${CC} ${CFLAGS} -c $<

libftm:
		make -C libft

libftclean:
			make clean -C libft

libftfclean:
			make fclean -C libft

clean: libftclean
		${RM} ${OBJ}

fclean: clean libftfclean
		${RM} ${NAME}

re: fclean all

