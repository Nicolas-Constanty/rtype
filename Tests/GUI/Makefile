CC		=	g++

RM 		=	rm -rf

NAME	=	test_gui

PROJECT_DIR =   ../..

SRC_DIR =   $(PROJECT_DIR)/src

INC_DIR =   $(PROJECT_DIR)/include

SALTYENGINE_DIR         =   $(SRC_DIR)/SaltyEngine
COMMON_DIR              =   $(SRC_DIR)/Common
MONSTER_DIR             =   $(SRC_DIR)/Monster
CLIENT_DIR              =   $(SRC_DIR)/ClientLauncher
PlAYER_DIR              =   $(SRC_DIR)/Player

SRC		= 	main.cpp                                \

CPPFLAGS 	=   -W -Wall -g -Wextra -std=c++11 -fPIC -g

CPPFLAGS    +=  -I $(INC_DIR) #-I$(PROJECT_DIR)/Dependencies/SFML/Linux/include

LDFLAGS     =  -lpthread -ldl -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

LDFLAGS     +=  -L ../../lib -lSaltyEngine -lSFMLSaltyEngine -lParser -Wl,-rpath=$(PROJECT_DIR)/lib/

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
