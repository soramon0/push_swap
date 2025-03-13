CC = cc
CFLAGS = -Wall -Wextra -Werror -g -D LOG_DEBUG=1
NAME = push_swap
NAME_BONUS = checker
SRC = main.c $(shell find ./src -depth -maxdepth 1 -type f -name "*.c")
SRC_BONUS = main_bonus.c $(shell find ./src -depth -maxdepth 1 -type f -name "*.c")
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
LIBFT_NAME = src/libft/libft.a
PROGRAM_ARG=$(shell seq -2500 5000 | shuf -n 500)

all: $(NAME)

libft: $(LIBFT_NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

bonus: $(LIBFT_NAME) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_NAME) -o $(NAME_BONUS)

$(LIBFT_NAME):
	$(MAKE) -C ./src/libft

clean:
	$(MAKE) -C src/libft clean
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(MAKE) -C src/libft fclean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

run: debug
	./push_swap "$(PROGRAM_ARG)"
	@rm $(NAME) $(OBJ)

debug: $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(EXTRA_FLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./push_swap "$(PROGRAM_ARG)"

profile_cpu_gen: debug
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes ./push_swap "$(PROGRAM_ARG)"

profile_cpu: profile_cpu_gen
	callgrind_annotate $(shell find . -type f -name callgrind.out*) --inclusive=yes --tree=both > profile_cpu.txt

profile_mem_gen: debug
	valgrind --tool=massif ./push_swap "$(PROGRAM_ARG)"

profile_mem: profile_mem_gen
	ms_print $(shell find . -type f -name massif.out*) > profile_mem.txt

run_checker:
	./push_swap "$(PROGRAM_ARG)" | ./checker_linux "$(PROGRAM_ARG)"

.PHONY: all clean fclean re run libft run_checker debug profile_cpu profile_mem profile_mem_gen profile_cpu_gen leaks
