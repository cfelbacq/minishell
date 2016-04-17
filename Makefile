# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/24 12:32:29 by cfelbacq          #+#    #+#              #
#    Updated: 2016/04/17 16:48:22 by cfelbacq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c \
	  src/env.c \
	  src/env2.c \
	  src/shell.c \
	  src/epur_line.c \
	  src/path_test.c \
	  src/prompt.c \
	  src/print_err.c \
	  src/tools.c \
	  src/tools2.c \
	  src/CD/cd.c \
	  src/CD/cd2.c \
	  src/CD/check_cd.c \
	  src/CD/check_cd2.c \
	  src/CD/epur_path_cd.c \
	  src/CD/epur_list_cd.c \
	  src/CD/cd_double_ar.c \
	  src/init.c \
	  src/setenv.c \
	  src/unsetenv.c \
	  src/exit.c \
	  src/free.c

OBJ = main.o \
	  env.o \
	  env2.o \
	  shell.o \
	  epur_line.o \
	  path_test.o \
	  prompt.o \
	  print_err.o \
	  tools.o \
	  tools2.o \
	  cd.o \
	  cd2.o \
	  check_cd.o \
	  check_cd2.o \
	  epur_path_cd.o \
	  epur_list_cd.o \
	  cd_double_ar.o \
	  init.o \
	  setenv.o \
	  unsetenv.o \
	  exit.o \
	  free.o

libft = libft/libft.a

all : $(NAME)

$(NAME) :
	make -C libft
	gcc -Wall -Werror -Wextra -c $(SRC)
	gcc -o $(NAME) $(OBJ) $(libft)

clean :
	rm -rf $(OBJ)
	make clean -C libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft

re : fclean all
