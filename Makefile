NAME = pipex
CC =  cc -Wall -Wextra -Werror -g3
SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIBFT_PATH = ./libft/
HEADER = -I ./libft/src -I /src
LIBFT = libft/libft.a

SRC	= child_processes.c create_pipex.c free_utils.c main.c verify_cmd.c
OBJ = $(SRC:%.c=%.o)

OBJ_WITH_PATH = $(addprefix $(OBJ_PATH),$(OBJ))

all: $(NAME)

$(NAME): $(OBJ_WITH_PATH)
	$(CC) $(OBJ_WITH_PATH) $(LIBFT) $(HEADER) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p obj
	@make -C $(LIBFT_PATH) all
	$(CC) $< -o $@ -c $(HEADER) 

clean:
	@rm -rf obj
	@rm -rf obj_bonus
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS_NAME)
	@make -C $(LIBFT_PATH) fclean

val: $(NAME)
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --vgdb=yes ./pipex missingfile "fsdfds" "cat -e" "fdsfds2" "grep world" "fdsfdsds" "echo ----"  /etc/passwd

val2: $(NAME)
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --vgdb=yes ./pipex infile.txt "cat -e" "grep world" "tr rl ' \"'" outfile.txt  && cat outfile.txt 
	
val3: $(NAME)
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --vgdb=yes ./pipex here_doc eof "cat -e" "grep world" "tr rl ' \"'" outfile2.txt && cat outfile2.txt 

re: fclean all

test: $(NAME)
	./pipex infile.txt "cat -e" "grep world" "tr rl ' \"'" outfile.txt  && cat outfile.txt 
	./pipex here_doc eof "cat -e" "grep world" "tr rl ' \"'" outfile2.txt && cat outfile2.txt 
	
