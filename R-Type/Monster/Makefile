CC		=	g++

RM 		=	rm -rf

NAME	=	monster.so

PROJECT_DIR =   ../..

SRC_DIR =   $(PROJECT_DIR)/src

INC_DIR =   $(PROJECT_DIR)/include

SALTYENGINE_DIR         =   $(SRC_DIR)/SaltyEngine
COMMON_DIR              =   $(SRC_DIR)/Common
MONSTER_DIR             =   $(SRC_DIR)/Monster

SRC		= 	$(MONSTER_DIR)/Monster.cpp              \
            $(MONSTER_DIR)/MonsterController.cpp    \

CPPFLAGS 	=   -W -Wall -g -Wextra -std=c++11 -fPIC

CPPFLAGS    +=  -I $(INC_DIR)

LDFLAGS	=   -lpthread -ldl -L ../SaltyEngine -lSaltyEngine -shared -O2

OBJ		= 	$(SRC:.cpp=.o)

$(NAME)	: 	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

all		: 	$(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: 	clean
	$(RM) $(NAME)

re		: 	fclean all

.PHONY	: all clean fclean re
