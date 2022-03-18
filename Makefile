*********************************************************************** #

NAME =	Matt-daemon

SRCS =	matt-daemon.cpp		\
		Tintin_reporter.cpp

SRCS_DIR = ./srcs/

INCS = ./incs/matt-daemon.hpp

FLAGS =	-Wall -Wextra -Werror -std=c++98

OBJ = $(SRCS:.cpp=.o)

OBJS = $(addprefix $(OBJS_DIR),  $(OBJ))

OBJS_DIR =	objs/

PRINT_REQ_AND_RESP = 0

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(INCS)
	@mkdir -p $(OBJS_DIR)
	@clang++ -D PRINT_VALUE=$(PRINT_REQ_AND_RESP) $(FLAGS) -c  $< -o $@
	@echo "Compiling $<"

$(NAME): $(OBJS)
	@clang++ $(FLAGS) -o $(NAME) $(OBJS)
	@echo "Exec Matt-daemon created"
	@echo "\nUsage: './Matt-daemon"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "Exec removed"

re: fclean all
