#Tools to edit text
GREEN = \033[1;92m
YELLOW = \033[3;93m
BLUE = \033[3;34m
TEXT_RESET = \033[0;0m

NAME = webserver
CC = clang++
FLAGS = -Wall -Wextra -Werror --std=c++98

IGNORE_PATHS = 
OBJDIR = ./src/obj
OBJ = $(C_FILES:%.cpp=%.o)
O_FILES = $(addprefix $(OBJDIR)/, $(OBJ))

HPP_DIR = $(shell find ./src -type d -not -path ./.git -not -path ./src/obj)

SRC_PATHS = $(shell find . -type d -not -path ./.git -not -path ./src/obj)

C_FILES = $(shell find . -name "*.cpp" $(IGNORE_PATHS) -execdir echo {} ';')

INCLUDE = $(addprefix -I, $(HPP_DIR))

vpath %.cpp $(SRC_PATHS)
vpath %.o $(OBJDIR)
vpath %.hpp $(INCLUDE)

.PHONY: all clean fclean re

all: $(OBJDIR) $(NAME)

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
	@echo "$(YELLOW)Delete 'o' files"

fclean: clean
	@echo "$(TEXT_RESET)"
	@rm -f $(NAME)
	@echo "$(YELLOW)Delete the binary file '$(NAME)'"
	@echo

re: fclean all