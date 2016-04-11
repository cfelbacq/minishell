# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/24 12:32:29 by cfelbacq          #+#    #+#              #
#    Updated: 2016/04/11 18:37:43 by cfelbacq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c \
	  src/env.c \
	  src/shell.c \
	  src/prompt.c \
	  src/print_err.c \
	  src/tools.c \
	  src/tools2.c \
	  src/cd.c \
	  src/cd2.c \
	  src/check_cd.c \
	  src/epur_path_cd.c \
	  src/epur_list_cd.c \
	  src/init.c \
	  src/setenv.c \
	  src/unsetenv.c

OBJ = main.o \
	  env.o \
	  shell.o \
	  prompt.o \
	  print_err.o \
	  tools.o \
	  tools2.o \
	  cd.o \
	  cd2.o \
	  check_cd.o \
	  epur_path_cd.o \
	  epur_list_cd.o \
	  init.o \
	  setenv.o \
	  unsetenv.o

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
	make fclean -C libft

re : fclean all
