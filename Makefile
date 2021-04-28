# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 12:45:13 by egomez-a          #+#    #+#              #
#    Updated: 2021/04/27 16:57:33 by egomez-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = ./libft/libft.a

LIBFTFOLDER = ./libft

SRCS =	ft_printf.c \
		ft_flagsfunctions.c \
		ft_printchar.c \
		ft_printdecint.c \
		ft_printstring.c \
		ft_putcharpercent.c \
		ft_printu.c \
		ft_printpointer.c \
		ft_nbrtohex.c \
		ft_moveminus.c \
		ft_printx.c \
		ft_utoa.c
	
CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf 

AR = ar rcs

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	make re -C $(LIBFTFOLDER)
	$(CC) -g3 $(FLAGS) -c $(SRCS) -I.
	$(AR) $(NAME) $(OBJS) $(LIBFTFOLDER)/ft*.o
	@ranlib $(NAME)
	echo "Compiled '$(NAME)' OK"
	
all : 	$(NAME)

clean :
	$(RM) $(OBJS)
	@make -C $(LIBFTFOLDER)
	@echo "Cleaned objects OK"

fclean : clean
	$(RM) $(NAME)
	@echo "Removed '$(NAME)' OK"

re : fclean all

.PHONY: all, clean, fclean, re
