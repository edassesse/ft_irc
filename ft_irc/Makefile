NAME		= ircserv
OBJS		= $(SRCS:.cpp=.o)
HEADER		= Server.hpp Irc.h Server.hpp
SRCS		= Main.cpp Server.cpp
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
