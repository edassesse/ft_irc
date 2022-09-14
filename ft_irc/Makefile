NAME		= ircserv
OBJS		= $(SRCS:.cpp=.o)
HEADER		= server.hpp Irc.h
SRCS		= main.cpp Parsing.cpp
RM			= rm -f
CC			= clang++
CFLAGS		= -Wall -Werror -Wextra

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
