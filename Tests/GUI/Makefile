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
SFML_DIR                =   $(SALTYENGINE_DIR)/SFML

SRC		= 	$(CLIENT_DIR)/PlayerController.cpp      \
            $(CLIENT_DIR)/Laser.cpp                 \
            $(MONSTER_DIR)/MonsterController.cpp    \
            main.cpp                                \

CPPFLAGS 	=   -W -Wall -g -Wextra -std=c++11 -fPIC

CPPFLAGS    +=  -I $(INC_DIR) #-I$(PROJECT_DIR)/Dependencies/SFML/Linux/include

#DFLAGS	    =   -L$(PROJECT_DIR)/Dependencies/SFML/Linux/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -Wl,-rpath=$(PROJECT_DIR)/Dependencies/SFML/Linux/lib

LDFLAGS     +=  -lpthread -ldl -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

LDFLAGS     +=  -L ./ -lSaltyEngine -lSFMLSaltyEngine

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
