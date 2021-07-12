# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/12 13:27:28 by rel-bour          #+#    #+#              #
#    Updated: 2021/07/12 13:46:13 by rel-bour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell_prs

CC = gcc -g -fsanitize=address -lreadline -ledit

CFLAGS = -Wall -Wextra -Werror   

SRC = *.c\
parsing_n/*.c
	
all : $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) -o $(NAME)
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)
re:	fclean all