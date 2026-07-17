NAME = btc
SRC = main.cpp BitcoinExchange.cpp 

RM = rm -rf
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -MMD -MP -std=c++98
DIR_OBJ = obj

# ---------- No need to touch after this point ----------

OBJ = $(SRC:%.cpp=$(DIR_OBJ)/%.o)
DEPS = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -lm -o $(NAME)

$(DIR_OBJ)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re

