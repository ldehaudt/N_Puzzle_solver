NAME = nPuzzle

SRC = Board.cpp Display.cpp Solver.cpp nPuzzle.cpp

OBJ = $(SRC:.cpp=.o)

FRAMEWORKS = -framework OpenGl

GREEN = \033[1;38;2;0;175;117m
RED = \033[1;38;2;225;20;20m
WHITE = \033[1;38;2;255;251;214m
YELLO = \033[1;38;2;255;200;0m

BREW_INC = -I ~/.brew/include
SDL_LINK = -L ~/.brew/lib -l SDL2
CPPFLAGS = -Wall -Wextra -Werror -O2

CPP = @clang++ -std=c++11

all: $(NAME)

$(NAME): $(SRC) *.hpp
	@echo "${WHITE}Creating $@"
	$(CPP) -c $(SRC) $(BREW_INC)
	$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME) $(FRAMEWORKS) $(BREW_INC) $(SDL_LINK)
clean:
	@echo "${RED}Removing object files"	
	@rm -f *.o

fclean: clean
	@echo "${RED}Removing Executable >.<"	
	@rm -f $(NAME)

re: fclean all
