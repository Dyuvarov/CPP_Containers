NAME		= containers

SRCS		= src/main.cpp src/test/Tests.cpp src/test/TestUtils.cpp
OBJS		= $(SRCS:.cpp=.o)

INCLUDES 	= -I includes/ -I src/test

CC			= clang++
FLAGS		= -Wall -Wextra -Werror -std=c++98

.cpp.o:
			clang++ $(FLAGS) $(INCLUDES) -c $< -o ${<:.cpp=.o}

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re