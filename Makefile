##
## EPITECH PROJECT, 2023
## B-CCP-400-PAR-4-1-theplazza-joseph.yu
## File description:
## Makefile
##

TEST_FILES = tests/test_project.cpp

NAME = plazza

TEST_NAME = unit_tests

MAIN_SRC = src/main.cpp

ERROR = Error/

PARSING = Parsing/

UTILS = Utils/

PIZZA = Pizza/

ENCAPSULATION = Encapsulation

GRAPHIC = Graphical/

SRC	=	src/$(PARSING)Parsing.cpp			\
		src/$(GRAPHIC)Graphic.cpp			\
		src/$(ERROR)Error.cpp				\
		src/$(ERROR)ErrorHandling.cpp		\
		src/$(UTILS)Order.cpp				\
		src/$(UTILS)Ingredient.cpp			\
		src/$(UTILS)Factory.cpp				\
		src/Kitchen.cpp						\
		src/Reception.cpp					\
		src/$(PIZZA)/Pizza.cpp				\

SRC +=	src/$(ENCAPSULATION)/Process.cpp	\
		src/$(ENCAPSULATION)/IPC.cpp		\
		src/$(ENCAPSULATION)/Platform.cpp

ALL_SRC += $(SRC)

ALL_SRC += $(MAIN_SRC)

OBJ	= $(ALL_SRC:.cpp=.o)

CFLAGS += -Wall -Wextra

CPPFLAGS += -I./include/

CPPFLAGS += -I./src/$(ERROR)

CPPFLAGS += -I./src/$(PARSING)

CPPFLAGS += -I./src/$(UTILS)

CPPFLAGS += -I./src/$(PIZZA)

CPPFLAGS += -I./src/$(GRAPHIC)

LDFLAGS += -lpthread
LDFLAGS += -lsfml-system -lsfml-window -lsfml-graphics

all: $(NAME)

# $(NAME): OBJ += $(MAIN_SRC:.cpp=.o)
$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)

tests_run: clean
	$(CXX) $(SRC) $(TEST_FILES) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $(TEST_NAME) -lcriterion --coverage
	./${TEST_NAME}
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

clean:
	$(RM) -f $(OBJ)
	$(RM) *.gcda
	$(RM) *.gcno

fclean: clean
	$(RM) -f $(NAME)
	$(RM) -f $(TEST_NAME)
re: fclean all

debug: CPPFLAGS += -g3
debug: re

.PHONY: all clean fclean re