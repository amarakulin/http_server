#Tools to edit text
GREEN = \033[1;92m
YELLOW = \033[3;93m
BLUE = \033[3;34m
TEXT_RESET = \033[0;0m

NAME = webserver
CC = clang++
FLAGS = -Wall -Wextra -Werror --std=c++98

TEST_DIR = ./unit_test
IGNORE_PATHS = ! -path "$(TEST_DIR)/*"
OBJDIR = ./src/obj


OBJ = $(C_FILES:%.cpp=%.o)
O_FILES = $(addprefix $(OBJDIR)/, $(OBJ))

HPP_DIR = $(shell find ./src -type d -not -path ./.git -not -path ./src/obj -not -path $(TEST_DIR))

SRC_PATHS = $(shell find . -type d -not -path ./.git -not -path ./src/obj -not -path $(TEST_DIR))

C_FILES = $(shell find . -name "*.cpp" $(IGNORE_PATHS) -execdir echo {} ';')

INCLUDE = $(addprefix -I, $(HPP_DIR))

vpath %.cpp $(SRC_PATHS)
vpath %.o $(OBJDIR)
vpath %.hpp $(INCLUDE)

.PHONY: all clean fclean re

all: test $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(INCLUDE) $(O_FILES) -o $@
	@echo "$(GREEN)Success!"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

%.o: %.cpp
	@echo "$(BLUE)Compiling $<"
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $(OBJDIR)/$@

clean:
	@echo "$(TEXT_RESET)"
	@rm -rf $(OBJDIR)
	@make clean -C $(TEST_DIR)
	@echo "$(YELLOW)Delete 'o' files in '$(NAME)'"

fclean: clean
	@echo "$(TEXT_RESET)"
	@rm -f $(NAME)
	@make fclean -C $(TEST_DIR)
	@echo "$(YELLOW)Delete the binary file '$(NAME)'"
	@echo

test:
	@make -C $(TEST_DIR)
	@$(TEST_DIR)/unit_test

re: fclean all