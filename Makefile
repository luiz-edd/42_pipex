NAME = pipex
CC =  cc -Wall -Wextra -Werror
SRC_PATH = ./src/
LIBFT_PATH = ./libft/
HEADER = -I ./libft/src -I /src
LIBFT = libft/libft.a

SRC	= $(addprefix $(SRC_PATH), main.c )
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(HEADER) -o $(NAME)

$(OBJ): $(SRC)
	mkdir -p obj
	make -C $(LIBFT_PATH) all
	$(CC) $< -o $@ -c $(HEADER) 

clean:
	@rm -rf obj
	@rm -rf obj_bonus
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS_NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all