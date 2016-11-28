CC		=	g++

RM 		=	rm -rf

NAME	=	salty-engine

LIBNAME =   libSaltyEngine.a

PROJECT_DIR =   ../..

SRC_DIR =   $(PROJECT_DIR)/src

INC_DIR =   $(PROJECT_DIR)/include

SALTYENGINE_DIR         =   $(SRC_DIR)/SaltyEngine
COMMON_DIR              =   $(SRC_DIR)/Common

SRC		= 	$(SALTYENGINE_DIR)/Behaviour.cpp        \
            $(SALTYENGINE_DIR)/Component.cpp        \
            $(SALTYENGINE_DIR)/GameObject.cpp       \
	    $(SALTYENGINE_DIR)/main.cpp		\
            $(SALTYENGINE_DIR)/Object.cpp           \
            $(SALTYENGINE_DIR)/PlayerController.cpp \
            $(SALTYENGINE_DIR)/SaltyBehaviour.cpp   \
            $(SALTYENGINE_DIR)/SaltyEngine.cpp      \
            $(SALTYENGINE_DIR)/Scene.cpp            \
            $(SALTYENGINE_DIR)/Factory.cpp          \
            $(COMMON_DIR)/LibLoader.cpp             \

CPPFLAGS 	=   -W -Wall -g -Wextra -std=c++11 -fPIC

CPPFLAGS    +=  -I $(INC_DIR)

LDFLAGS	=   -lpthread -ldl

OBJ		= 	$(SRC:.cpp=.o)

$(NAME)	: 	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	ar rc $(LIBNAME) $(OBJ)
	ranlib $(LIBNAME)

all		: 	$(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: 	clean
	$(RM) $(NAME)

re		: 	fclean all

.PHONY	: all clean fclean re
