# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aemilien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/26 13:27:27 by aemilien          #+#    #+#              #
#    Updated: 2016/12/28 11:39:16 by aemilien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CCFLAGS= -Wall -Wextra -Werror -o

LIBFT= -lft -L libft -I libft

LIBMLX= -lmlx -L minilibx_macos -I minilibx_macos

INCLUDE= -I include

FRAMEWORK= -framework OpenGL -framework AppKit

SRC= main.c event.c error.c split_color.c put_pixel_to_image.c fill_image.c julia_set.c

OBJ=$(SRCS:.c=.o)

NAME=fractol

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(INCLUDE) $(CCFLAGS) $@ $(SRC) $(LIBFT) $(LIBMLX) $(FRAMEWORK)

%.o:%.c
	@gcc $(INCLUDE) $(CCFLAGS) $@ -c $< $(LIBFT) $(LIBMLX)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
