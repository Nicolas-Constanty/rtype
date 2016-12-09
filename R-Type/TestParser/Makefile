DIR = ../../src/Parser/

INC = ../../include

DEPENDENCE = ../../Dependencies/Boost/Win/include

RM = rm -rf

SRC = 	$(DIR)ConsumerParser.cpp \
	$(DIR)JsonException.cpp \
	$(DIR)JsonVariant.cpp \
	$(DIR)Parser.cpp \
	$(DIR)ParserConf.cpp \
	$(DIR)ParserHttp.cpp \
	$(DIR)ParserJson.cpp \
	$(DIR)ProducterStream.cpp \
	main.cpp \

OBJ = $(SRC:.cpp=.o)

NAME = test_parser

CC = g++

CPPFLAGS = -I$(INC) -I$(DEPENDENCE) -std=c++11

$(NAME): $(OBJ)
	$(CC) -I$(INC) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
