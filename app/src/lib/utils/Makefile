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

SRC_TESTS = ./tests/tests_arrays.c

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
	@gcc -c $(SRC) -I $(HEADER)
	@gcc -c $(SRC_TESTS) --coverage -g3 -I $(HEADER)
	@mkdir -p objects
	@mv *.o objects
	@gcc -o $(TEST_BIN) objects/*.o -lcriterion --coverage -g3 -I $(HEADER)
	@./$(TEST_BIN)
	@echo "[*** UTILS TESTS OVER ***]"

tests_clean: tests
	@gcovr *
	@$(RM) $(TEST_BIN) *gc* $(NAME) objects
	@echo "[*** CLEAN SUCCESSFUL ***]"




.PHONY: all clean fclean re tests tests_clean
