NAME = so_long
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -crs
FILES = so_long.c gnl/get_next_line.c gnl/get_next_line_utils.c check.c play.c winnable.c
SANITIZE = -fsanitize=address


all : $(NAME)

$(NAME) :
	@make -C libft
	@cp libft/libft.a .
	@$(CC) $(CFLAGS) $(FILES) -lft -L./libft -lmlx -framework OpenGL -framework AppKit -o $(NAME) 
%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
clean :
	@make -C libft fclean
	@$(RM) $(NAME)
	@$(RM) libft.a
fclean : clean
	@make -C libft fclean
	@$(RM) $(NAME)
	@$(RM) libft.a
re : fclean all
.PHONY : all clean fclean re