##
## Bogdan G. // Adina C.
##

vpath %.c ./src/
vpath %.c ./src/logger
vpath %.c ./src/parser
vpath %.c ./src/utils

########################
#### VARIABLES #########
########################

NAME	= tello

RM		= rm -rf

########################
#### CC RELATED ########
########################

CC		= gcc

INCLUDES = -I./includes/

CFLAGS 	= -g3 \
		  -Wno-unused-function \
		  -Wall -Werror -Wextra \
		  --pedantic \
		  -Ofast

LINK_FLAG =

########################
### FILES PATH #########
########################

MAIN		 =	main.c

SRC = \

PARSER = 	get_instruction_queue.c \
			input_checking.c

UTILS =     arrays.c \
			file_handler.c \
			get_next_line.c \
			nums.c \
			strings.c \
			swaps.c

LOGGER = create_logfile.c \
		 update_logs.c

# needed for unit tests, do not include $(MAIN)
COMBINED_NO_MAIN = 	$(SRC) \
					$(LOGGER) \
					$(UTILS) \
					$(PARSER)

# binary included files
COMBINED	=	$(MAIN) \
			$(COMBINED_NO_MAIN)

TEST_SRC 	= ./tests/tests_parser.c \
			  ./tests/tests_nums.c \
			  ./tests/tests_swaps.c \
			  ./tests/tests_arrays.c \
			  ./tests/tests_strings.c \
			  ./tests/tests_file_handler.c \
			  ./tests/tests_get_next_line.c

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
	@gcc -o $(NAME) $^ $(LINK_FLAG)
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

func_tests:
	@sh tests/.ftests

tests: directories $(LIB) $(OBJTST)
	@$(CC) -c $(TEST_SRC) --coverage -g3 $(INCLUDES) $(LINK_FLAG)
	@mv *.o objects
	@$(CC) -o unit_tests ./objects/*.o --coverage $(INCLUDES) $(LINK_FLAG) -lcriterion
	@./unit_tests > /dev/null
	@echo -e "\e[34m[*** TESTS OVER ***]\e[39m"

tests_clean: tests
	@gcovr --exclude tests/
	@$(RM) unit_tests
	@$(RM) *.gc* unit_tests
	@$(RM) $(NAME)
	@$(RM) objects
	@echo -e "\e[34m[*** CLEAN SUCCESSFUL ***]\e[39m"

########################
#### .PHONY ############
########################

.PHONY: all clean fclean re tests tests_clean doc
