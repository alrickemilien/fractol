NAME=fractol

OS="$(shell uname)"

CCFLAGS= -O3 -Wall -Wextra -Werror

LIBFT= -lft -L libft -I libft

LPTHREAD= -lpthread

FRAMEWORK= -framework OpenGL -framework AppKit

INCLUDE=-I includes

SRC= src/main.c \
		src/event.c \
		src/random_moves.c \
		src/error.c \
	  src/julia_set.c \
		src/mandelbrot_set.c \
		src/third_set.c  \
	  src/render.c \
		src/render_utils.c \
		src/display_info_maths.c \
		src/bmp.c\
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
