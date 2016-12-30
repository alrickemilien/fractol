# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aemilien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/26 13:27:27 by aemilien          #+#    #+#              #
#    Updated: 2016/12/30 13:45:41 by aemilien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CCFLAGS= -Wall -Wextra -Werror  -O3 -o

LIBFT= -lft -L libft -I libft

LPTHREAD= -lpthread

LIBMLX= -lmlx -L minilibx_macos -I minilibx_macos

INCLUDE= -I include

FRAMEWORK= -framework OpenGL -framework AppKit

SRC= main.c event.c error.c split_color.c put_pixel_to_image.c fill_image.c julia_set.c mandelbrot_set.c\
third_set.c menu.c

OBJ=$(SRCS:.c=.o)

NAME=fractol

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(INCLUDE) $(CCFLAGS) $@ $(SRC) $(LIBFT) $(LIBMLX) $(LPTHREAD) $(FRAMEWORK)

%.o:%.c
	@gcc $(INCLUDE) $(CCFLAGS) $@ -c $< $(LIBFT) $(LPTHREAD) $(LIBMLX)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
