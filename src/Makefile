NAME		= ircserv
OBJS		= $(SRCS:.cpp=.o)
HEADER		= ../include/Command.hpp ../include/User.hpp ../include/Server.hpp ../include/Channel.hpp
SRCS		= Server.cpp Command.cpp User.cpp Utils.cpp Channel.cpp
RM			= rm -f
CC			= clang++
CFLAGS		= -Wall -Werror -Wextra -std=c++98

all:
					@$(MAKE) $(NAME)

$(NAME): $(OBJS) $(HEADER)
					@printf "$(ERASE)"
					$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
					@echo "$(BOLD)$(GREEN)Compilation $(NAME) Succes !$(END)"

clean :
					@rm -rf $(OBJS)
					@echo "$(RED)Clean $(NAME) Succes !$(END)"

fclean :			clean
					@rm -f $(NAME)
					@echo "$(RED)Fclean $(NAME) Succes !$(END)"

re:					fclean all
