NAME = pipex
NAME_BONUS = pipex_bonus
CFLAGS = -Wextra -Wall -Werror -g3
CC = cc $(CFLAGS)

# lib
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft/

#headers
HEADER = -I libft/src -I src/
HEADER_BONUS = -I libft/src -I src_bonus/

# file names
SRC	= child_processes.c create_pipex.c free_utils.c main.c verify_cmd.c
OBJ = $(SRC:%.c=%.o)
SRC_BONUS = child_processes_bonus.c create_pipex_bonus.c free_utils_bonus.c main_bonus.c verify_cmd_bonus.c
OBJ_BONUS  = $(SRC_BONUS:%.c=%.o)

# folder names
SRC_FOLDER = src/
OBJ_FOLDER = obj/
SRC_FOLDER_BONUS = src_bonus/
OBJ_FOLDER_BONUS = obj_bonus/

# add file to folder ex: src/main.c
SRC_PATH = $(addprefix $(SRC_FOLDER), $(SRC))
OBJ_PATH = $(addprefix $(OBJ_FOLDER), $(OBJ))
SRC_PATH_BONUS = $(addprefix $(SRC_FOLDER_BONUS), $(SRC_BONUS))
OBJ_PATH_BONUS = $(addprefix $(OBJ_FOLDER_BONUS), $(OBJ_BONUS))

all: $(NAME)

# mandatory
$(NAME): $(OBJ_PATH)
	$(CC) $(OBJ_PATH) $(LIBFT) $(HEADER) -o $(NAME)

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c
	@mkdir -p $(OBJ_FOLDER)
	@make -C $(LIBFT_PATH)
	$(CC) $< -o $@ -c $(HEADER) 

# bonus
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_PATH_BONUS)
	$(CC) $(OBJ_PATH_BONUS) $(LIBFT) $(HEADER_BONUS) -o $(NAME_BONUS)

$(OBJ_FOLDER_BONUS)%.o: $(SRC_FOLDER_BONUS)%.c
	@mkdir -p $(OBJ_FOLDER_BONUS)
	@make -C $(LIBFT_PATH)
	$(CC) $< -o $@ -c $(HEADER_BONUS) 

# utils 
clean:
	@rm -rf obj
	@rm -rf obj_bonus
	@make -C $(LIBFT_PATH) clean

fclean:
	@rm -rf obj
	@rm -rf obj_bonus
	@make -C $(LIBFT_PATH) fclean

re: fclean all

normi:
	norminette src/* src_bonus/* lib/libft/src/*

.PHONY: all clean fclean re

# tests
test: $(NAME_BONUS)
	./pipex_bonus infile.txt "cat -e" "grep world" "tr rl ' \"'" outfile.txt  && cat outfile.txt 
	./pipex_bonus here_doc eof "cat -e" "grep world" "tr rl ' \"'" outfile2.txt && cat outfile2.txt 

val: $(NAME_BONUS)
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --vgdb=yes ./pipex_bonus missingfile "fsdfds" "cat -e" "fdsfds2" "grep world" "fdsfdsds" "echo ----"  /etc/passwd

val2: $(NAME_BONUS)
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --vgdb=yes ./pipex_bonus infile.txt "cat -e" "grep world" "tr rl ' \"'" outfile.txt  && cat outfile.txt 
	
val3: $(NAME_BONUS)
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --vgdb=yes ./pipex_bonus here_doc eof "cat -e" "grep world" "tr rl ' \"'" outfile2.txt && cat outfile2.txt 

