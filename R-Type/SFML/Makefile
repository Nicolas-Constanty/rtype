CC		=	g++

RM 		=	rm -rf

NAME	=	libSFMLSaltyEngine.a

PROJECT_DIR =   ../..
SRC_DIR     =   $(PROJECT_DIR)/src
INC_DIR     =   $(PROJECT_DIR)/include

SALTYENGINE_DIR         =   $(SRC_DIR)/SaltyEngine
SFML_DIR                =   $(SALTYENGINE_DIR)/SFML

SRC		= 	$(SALTYENGINE_DIR)/SFML/AssetManager.cpp    \
            $(SALTYENGINE_DIR)/SFML/EventManager.cpp    \
            $(SALTYENGINE_DIR)/SFML/Music.cpp           \
            $(SALTYENGINE_DIR)/SFML/Renderer.cpp        \
            $(SALTYENGINE_DIR)/SFML/Scene.cpp           \
            $(SALTYENGINE_DIR)/SFML/Sound.cpp           \

CPPFLAGS 	=   -W -Wall -Wextra -std=c++11 -fPIC

CPPFLAGS    +=  -I $(INC_DIR) #-I$(PROJECT_DIR)/Dependencies/SFML/Linux/include

#LDFLAGS     +=   -L$(PROJECT_DIR)/Dependencies/SFML/Linux/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -Wl,-rpath=$(PROJECT_DIR)/Dependencies/SFML/Linux/lib

LDFLAGS     = -lpthread -ldl -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

LDFLAGS	=   -L ../SaltyEngine -lSaltyEngine -shared -O2

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
