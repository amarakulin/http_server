#Tools to edit text ###
GREEN = \033[1;92m
YELLOW = \033[3;93m
BLUE = \033[3;34m
TEXT_RESET = \033[0;0m

NAME = unit_test

### COMPILE ###
CC = clang++
FLAGS = -Wall -Wextra -Werror --std=c++98
NOT_PATH = -not -path

### DIRECTORY/PATH ###
OBJ_DIR = ./src/obj
IGNORE_PATHS = $(NOT_PATH) "$(OBJ_DIR)/*"

### SEARCH PATHS ###
HPP_DIR = $(shell find ./src -type d $(IGNORE_PATHS))
SRC_PATHS = $(shell find . -type d $(IGNORE_PATHS) )
CPP_FILES = $(shell find . -name "*.cpp" $(IGNORE_PATHS) -execdir echo {} ';')

### LINK ###
OBJ = $(CPP_FILES:%.cpp=%.o)
O_FILES = $(addprefix $(OBJ_DIR)/, $(OBJ))
INCLUDE = $(addprefix -I, $(HPP_DIR))

vpath %.cpp $(SRC_PATHS)
vpath %.o $(OBJ_DIR)
vpath %.hpp $(INCLUDE)

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(INCLUDE) $(O_FILES) -o $@
	@echo "$(GREEN)START TESTING\n"
	@./$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

%.o: %.cpp
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $(OBJ_DIR)/$@

clean:
	@echo "$(TEXT_RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Delete 'o' files in '$(NAME)'"

fclean: clean
	@echo "$(TEXT_RESET)"
	@rm -f $(NAME)
	@echo "$(YELLOW)Delete the binary file '$(NAME)'"
	@echo

re: fclean all