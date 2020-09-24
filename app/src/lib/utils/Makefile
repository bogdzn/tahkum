##
## Bogdan G. // Adina C.
##


NAME 	= 	libutils.a

FLAGS = -Wall -Werror -Wextra \
		--pedantic \
		-Ofast

SRC 	=	./arrays.c \
			./file_handler.c \
			./get_next_line.c \
			./nums.c \
			./strings.c \
			swaps.c

SRC_TESTS = ./tests/tests_arrays.c \
			./tests/tests_nums.c \
			./tests/tests_swaps.c \
			./tests/tests_strings.c \
			./tests/tests_file_handler.c \
			./tests/tests_get_next_line.c

TEST_BIN = unit_tests

HEADER 	=	./utils.h

LIBPATH = 	./../../../includes/

RM 		= rm -rf

all:
	@gcc -c $(SRC) -I ..
	@mkdir -p ./objects
	@mv *.o objects
	@ar rc $(NAME) ./objects/*.o
	@cp $(HEADER) $(LIBPATH)
	@cp $(NAME) ./../../.
	@echo "[*** UTILS LIB CREATED ***]"

clean:
	@rm -rf objects
	@rm -f $(NAME)

fclean: clean
	@rm -f $(LIBPATH)$(HEADER)
	@rm -f ../../$(NAME)
	@echo "[*** UTILS LIB CLEANED ***]"

re: fclean all

tests:
	@gcc -c $(SRC)
	@gcc -c $(SRC_TESTS) $(FLAGS) --coverage -g3
	@mkdir -p objects
	@mv *.o objects
	@gcc -o $(TEST_BIN) objects/*.o -lcriterion --coverage -g3
	@./$(TEST_BIN)
	@echo "[*** UTILS TESTS OVER ***]"

tests_clean: tests
	@gcovr --exclude tests/
	@$(RM) $(TEST_BIN) *gc* $(NAME) objects
	@echo "[*** CLEAN SUCCESSFUL ***]"


.PHONY: all clean fclean re tests tests_clean
