NAME = minishell

CC = gcc
LIB = -L./libft -lft

SRC_DIR = ./srcs/
HEADER_DIR = -I./includes
CFLAGS = -fsanitize=address -g -Wall -Wextra -Werror $(HEADER_DIR)

SOURCE = minishell.c init_lst.c lstadd_sort.c cmd.c \
		get_env.c cmd_export.c edit_lst.c cmd_echo.c \
		lst_to_arr.c cmd_unset.c many_cmd.c quote_cmd.c \
		quote_many_cmd.c redirect.c
SRCS = $(addprefix $(SRC_DIR), $(SOURCE))

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft bonus
	$(CC) $(LIB) $(CFLAGS) $(SRCS) -o $(NAME)

bonus: all

clean:
	make -C ./libft clean
	rm -rf $(OBJ)

fclean: clean
	rm -rf ./libft/libft.a
	rm -rf $(NAME)

re: fclean all

.PHONY:all clean fclean re
