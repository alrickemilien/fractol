NAME=fractol

OS="$(shell uname)"

CCFLAGS= -O3 -Wall -Wextra -Werror 

LIBFT= -lft -L libft -I libft

USAGE="Usage : ./fractol [--julia] [--mandelbrot] [--burninship]"

LPTHREAD= -lpthread

FRAMEWORK= -framework OpenGL -framework AppKit

INCLUDE=-I includes

SRCS= main.c event.c error.c split_color.c put_pixel_to_image.c\
	  julia_set.c mandelbrot_set.c third_set.c  \
	  redraw.c display_info_maths.c bmp.c\
	  ft_write_n_bytes.c split_calcul.c end_program.c\

OBJ=$(SRCS:.c=.o)

ifeq ($(OS), "Linux")
	TARGET= LINUX
	LIBMLX_SRCS= minilibx_linux
else
	TARGET= MACOS
	LIBMLX_SRCS= minilibx_macos
endif

LIBMLX= -lmlx -L $(LIBMLX_SRCS) -I $(LIBMLX_SRCS)


all: $(TARGET)

LINUX: $(OBJ)
	@make -C libft
	@make -C minilibx_linux
	@gcc -o $(NAME) $^ $(LIBFT) $(INCLUDE) $(LPTHREAD) \
	$(LIBMLX) $(CCFLAGS) -lX11 -lXext -lm \
	`pkg-config --libs --cflags x11` 
	
MACOS: $(OBJ)
	@make -C libft
	@make -C minilibx_macos
	@gcc $@ $^ $(LIBFT) $(LPTHREAD)\
	$(LIBMLX) $(FRAMEWORK) $(CCFLAGS)

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(LIBFT) $(LIBMLX) $(LPTHREAD) $(CCFLAGS)

clean:
	@make clean -C libft
	@make clean -C $(LIBMLX_SRCS)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@make fclean -C $(LIBMLX_SRCS)
	@rm -rf $(NAME)

re: fclean all
