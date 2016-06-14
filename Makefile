# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avella <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/28 15:58:31 by avella            #+#    #+#              #
#    Updated: 2016/05/28 15:58:48 by avella           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

CC = gcc

INCLUDES = "libft/includes"

FLAGS =

MLXFLA = -lmlx -framework OpenGL -framework AppKit

SRC =   all_give.c all_inter.c all_light.c all_rotate.c all_shadow.c \
	event.c get_next_line.c img_func.c main.c pars_one.c pars_three.c \
	pars_two.c parsing.c ray_tracer.c small_cool_func.c usefull.c usefull_second.c

LIB = libft/libft.a

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) -c $(SRC) -I $(INCLUDES)
	$(CC) $(FLAGS) -o $(NAME) $(SRC) $(MLXFLA) $(LIB) -I $(INCLUDES)

clean :
	make -C libft/ clean
	rm -f $(OBJ)

fclean : clean
	rm -f $(LIB)
	rm -f $(NAME)

re : fclean all
