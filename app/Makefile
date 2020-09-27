##
## Bogdan G. // Adina C.
##

vpath %.c ./src/
vpath %.c ./src/logger
vpath %.c ./src/parser

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

########################
### LIB RELATED ########
########################

LINK_FLAG = -L$(LIBPATH) -lutils

LIBPATH = ./src/.

LIBUTILS_PATH =  ./src/lib/utils

LIBS  		= libutils.a

########################
### FILES PATH #########
########################

MAIN		 =	main.c

SRC = \

PARSER = 	get_instr_from_file.c \
		get_instr_queue.c

LOGGER = create_logfile.c

# needed for unit tests, do not include $(MAIN)
COMBINED_NO_MAIN = 	$(SRC) \
					$(LOGGER)\
					$(PARSER)

# binary included files
COMBINED	=	$(MAIN) \
			$(COMBINED_NO_MAIN)

TEST_SRC 	= ./tests/tests_parse.c

OBJECT_DIR 	= ./objects

OBJ 	 	= $(patsubst %.c, $(OBJECT_DIR)/%.o, $(COMBINED))
OBJTST 		= $(patsubst %.c, $(OBJECT_DIR)/%.o, $(COMBINED_NO_SRC))

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
	@make --no-print-directory -C $(LIBUTILS_PATH)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $^ $(LINK_FLAG)
	@echo -e "\e[34m[*** COMPILATION SUCCESSFUL ***]\e[39m"

clean:
	@make clean --no-print-directory -C $(LIBUTILS_PATH)
	@$(RM) objects

fclean: clean
	@make fclean --no-print-directory -C $(LIBUTILS_PATH)
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
	@make tests --no-print-directory -C $(LIBUTILS_PATH)
	@$(CC) -c $(TEST_SRC) --coverage -g3 $(INCLUDES) $(LINK_FLAG)
	@mv *.o objects
	@$(CC) -o unit_tests ./objects/*.o --coverage $(INCLUDES) $(LINK_FLAG) -lcriterion
	@./unit_tests > /dev/null
	@echo -e "\e[34m[*** TESTS OVER ***]\e[39m"

tests_clean: tests
	@gcovr --exclude tests/
	@make fclean --no-print-directory -C $(LIBUTILS_PATH)
	@$(RM) unit_tests
	@$(RM) *.gc* unit_tests
	@$(RM) $(NAME)
	@$(RM) objects
	@echo -e "\e[34m[*** CLEAN SUCCESSFUL ***]\e[39m"

########################
#### .PHONY ############
########################

.PHONY: all clean fclean re tests tests_clean doc
