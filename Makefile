# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/24 12:32:29 by cfelbacq          #+#    #+#              #
#    Updated: 2016/03/28 14:08:10 by cfelbacq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c \
	  src/env.c \
	  src/shell.c \
	  src/tools.c \
	  src/cd.c \
	  src/init.c \
	  src/setenv.c \

OBJ = main.o \
	  env.o \
	  shell.o \
	  tools.o \
	  cd.o \
	  init.o \
	  setenv.o

libft = libft/libft.a

all : $(NAME)

$(NAME) :
	make -C libft
	gcc -c $(SRC)
	gcc -o $(NAME) $(OBJ) $(libft)

clean :
	rm -rf $(OBJ)
	make clean -C libft

fclean : clean
	rm -rf $(NAME)

re : fclean all
