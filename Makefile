# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aemilien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/26 13:27:27 by aemilien          #+#    #+#              #
#    Updated: 2017/01/12 10:53:39 by aemilien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CCFLAGS= -Wall -Wextra -Werror  -O3 -o

LIBFT= -lft -L libft -I libft

LPTHREAD= -lpthread

LIBMLX= -lmlx -L minilibx_macos -I minilibx_macos

FRAMEWORK= -framework OpenGL -framework AppKit

SRC= main.c event.c error.c split_color.c put_pixel_to_image.c julia_set.c mandelbrot_set.c redraw.c\
third_set.c display_info_maths.c bmp.c ft_write_n_bytes.c split_calcul.c\

OBJ=$(SRCS:.c=.o)

NAME=fractol

all: $(NAME)

$(NAME): $(OBJ)
	@make re -C libft
	@gcc $(CCFLAGS) $@ $(SRC) $(LIBFT) $(LIBMLX) $(LPTHREAD) $(FRAMEWORK)

%.o:%.c
	@gcc $(CCFLAGS) $@ -c $< $(LIBFT) $(LPTHREAD) $(LIBMLX)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
