NAME=fractol

OS="$(shell uname)"

CCFLAGS= -O3 -Wall -Wextra -Werror

LIBFT= -lft -L libft -I libft

USAGE="Usage : ./fractol [--julia] [--mandelbrot] [--burninship]"

LPTHREAD= -lpthread

FRAMEWORK= -framework OpenGL -framework AppKit

INCLUDE=-I includes

SRC= src/main.c \
		src/event.c \
		src/error.c \
		src/split_color.c \
		src/put_pixel_to_image.c\
	  src/julia_set.c \
		src/mandelbrot_set.c \
		src/third_set.c  \
	  src/redraw.c \
		src/display_info_maths.c \
		src/bmp.c\
	  src/ft_write_n_bytes.c \
		src/split_calcul.c \
		src/end_program.c\

OBJ=$(SRC:.c=.o)

ifeq ($(OS), "Linux")
	TARGET= LINUX
	LIBMLX_SRCS= minilibx_linux
else
	TARGET= MACOS
	LIBMLX_SRCS= minilibx_macos
endif

LIBMLX= -lmlx -L $(LIBMLX_SRCS)

INCLUDE= -I $(LIBMLX_SRCS) -I includes


all: $(TARGET)

LINUX: $(OBJ)
	@make -C libft
	@make -C minilibx_linux
	@gcc -o $(NAME) $^ $(LIBFT) $(LPTHREAD) \
	$(LIBMLX) $(CCFLAGS) -lX11 -lXext -lm \
	`pkg-config --libs --cflags x11`

MACOS: $(OBJ)
	@make -C libft
	@make -C minilibx_macos
	@gcc -o $(NAME) $^ $(LIBFT) $(LPTHREAD) \
	$(LIBMLX) $(FRAMEWORK) $(CCFLAGS)

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@make clean -C libft
	@make clean -C $(LIBMLX_SRCS)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all
