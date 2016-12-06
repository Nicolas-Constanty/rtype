BCC		=	g++

RM 		=	rm -rf

NAME	=	salty-engine

LIBNAME =   libSaltyEngine.a

PROJECT_DIR =   ../..

SRC_DIR =   $(PROJECT_DIR)/src

INC_DIR =   $(PROJECT_DIR)/include

SALTYENGINE_DIR         =   $(SRC_DIR)/SaltyEngine
COMMON_DIR              =   $(SRC_DIR)/Common
MONSTER_DIR             =   $(SRC_DIR)/Monster
CLIENT_DIR              =   $(SRC_DIR)/ClientLauncher

SRC		= 	$(SALTYENGINE_DIR)/Animation.cpp        \
            $(SALTYENGINE_DIR)/AnimationClip.cpp    \
            $(SALTYENGINE_DIR)/Behaviour.cpp        \
            $(SALTYENGINE_DIR)/Component.cpp        \
            $(SALTYENGINE_DIR)/Debug.cpp            \
            $(SALTYENGINE_DIR)/DefaultScene.cpp     \
            $(SALTYENGINE_DIR)/Factory.cpp          \
            $(SALTYENGINE_DIR)/GameObject.cpp       \
            $(SALTYENGINE_DIR)/Object.cpp           \
            $(SALTYENGINE_DIR)/RigidBody.cpp        \
            $(SALTYENGINE_DIR)/SaltyBehaviour.cpp   \
            $(SALTYENGINE_DIR)/SaltyEngine.cpp      \
            $(SALTYENGINE_DIR)/Scene.cpp            \
            $(SALTYENGINE_DIR)/GUI/Button.cpp           \
            $(SALTYENGINE_DIR)/GUI/Event.cpp            \
            $(SALTYENGINE_DIR)/GUI/UIBehaviour.cpp      \
            $(SALTYENGINE_DIR)/GUI/Widget.cpp           \
            $(SALTYENGINE_DIR)/Input/Action.cpp         \
            $(SALTYENGINE_DIR)/Input/Axis.cpp           \
            $(SALTYENGINE_DIR)/Input/Mapping.cpp        \
            $(COMMON_DIR)/LibLoader.cpp                 \

CPPFLAGS 	=   -W -Wall -g -Wextra -std=c++11 -fPIC -rdynamic -shared -O2

CPPFLAGS    +=  -I $(INC_DIR)

LDFLAGS		+= -ldl

OBJ		= 	$(SRC:.cpp=.o)

$(NAME)	: 	$(OBJ)
	ar rc $(LIBNAME) $(OBJ)
	ranlib $(LIBNAME)

all		: 	$(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: 	clean
	$(RM) $(NAME) $(LIBNAME)

re		: 	fclean all

.PHONY	: all clean fclean re
