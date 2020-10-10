##
## Bogdan G. // Adina C.
##

vpath %.c ./src/
vpath %.c ./src/exec/net
vpath %.c ./src/exec
vpath %.c ./src/parser
vpath %.c ./src/utils

########################
#### VARIABLES #########
########################

NAME	= tahkum

RM		= rm -rf

########################
#### CC RELATED ########
########################

CC		= gcc

INCLUDES = -I./include/

CFLAGS 	= -g3 \
		  -ftest-coverage \
		  -Wall -Werror -Wextra \
		  --pedantic \
		  -fprofile-arcs \
		  -fPIC

LINK_FLAG =

########################
### FILES PATH #########
########################

MAIN		 =	main.c

SRC = \

PARSER = 	get_instruction_queue.c \
			input_checking.c \
			initial_setup.c \
			file_handler.c

UTILS =     arrays.c \
			logs.c \
			get_next_line.c \
			nums.c \
			strings.c \
			swaps.c

EXEC  = drone_interactions.c \
		 socket_handler.c \
		 key_listener.c \
		 exec_loop.c

# needed for unit tests, do not include $(MAIN)
COMBINED_NO_MAIN = 	$(SRC) \
					$(UTILS) \
					$(PARSER) \
					$(EXEC)

# binary included files
COMBINED	=	$(MAIN) \
			$(COMBINED_NO_MAIN)

TEST_SRC 	= ./tests/tests_parser.c \
			  ./tests/tests_nums.c \
			  ./tests/tests_swaps.c \
			  ./tests/tests_arrays.c \
			  ./tests/tests_strings.c \
			  ./tests/tests_file_handler.c \
			  ./tests/tests_get_next_line.c \
			  ./tests/tests_socket.c \
			  ./tests/tests_logger.c

OBJECT_DIR 	= ./objects

OBJ 	 	= $(patsubst %.c, $(OBJECT_DIR)/%.o, $(COMBINED))
OBJTST 		= $(patsubst %.c, $(OBJECT_DIR)/%.o, $(COMBINED_NO_MAIN))

########################
#### COMPILATION #######
########################

all: directories $(LIB) $(NAME)

$(OBJECT_DIR):
	@mkdir -p $@

directories: | $(OBJECT_DIR)

$(OBJECT_DIR)/%.o : %.c
	@gcc -o $@ -c $< $(CFLAGS) $(INCLUDES)
	@echo -e "\e[35mCompiling $@\e[39m"

$(LIB):

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(CFLAGS) $^ $(LINK_FLAG)
	@echo -e "\e[34m[*** COMPILATION SUCCESSFUL ***]\e[39m"

clean:
	@$(RM) objects

fclean: clean
	@$(RM) $(NAME)
	@echo -e "\e[34m[*** CLEAN ***]\e[39m"

re: fclean all


########################
###### DOXYGEN  ########
########################

doc:
	@make -C  ./doxygen --no-print-directory

docdel:
	@make del -C ./doxygen --no-print-directory

docre:
	@make re -C ./doxygen --no-print-directory

########################
#### UNIT TESTS ########
########################

func_tests: tests_clean
	@sh tests/.ftests

tests: fclean directories $(LIB) $(OBJTST)
	@$(CC) -c $(TEST_SRC) --coverage -g3 $(INCLUDES)
	@mv *.o objects
	@$(CC) -o unit_tests ./objects/*.o --coverage $(INCLUDES) -lcriterion
	@./unit_tests >/dev/null 2>&1
	@echo -e "\e[34m[*** TESTS OVER ***]\e[39m"

tests_clean: tests
	@gcovr -r . -e tests --sort-percentage
	@$(RM) unit_tests
	@$(RM) *.gc* unit_tests
	@$(RM) $(NAME) tello.log
	@$(RM) objects
	@echo -e "\e[34m[*** CLEAN SUCCESSFUL ***]\e[39m"

########################
#### .PHONY ############
########################

.PHONY: all clean fclean re tests tests_clean doc docre docdel
