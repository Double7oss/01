# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 18:51:46 by hel-kadd          #+#    #+#              #
#    Updated: 2023/04/10 22:48:44 by abouzanb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = @cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

# AR = @ar 

# ARFLAGS = rc

SRCS =	./src/parse/lexer/lexer.c \
		./src/parse/lexer/lexer_utils.c \
		./src/parse/utils/ft_utils.c \
		./src/parse/utils/ft_str_func.c \
		./src/parse/parsing/parse.c \
		./src/parse/expand/expand.c \
		./src/parse/expand/expand_test.c \
		./src/parse/parsing/parse_utils.c ../minishell/bulit.c ../minishell/execution.c ../minishell/re_libft.c ../minishell/small_libft.c ../minishell/split.c ../minishell/split_with_slash.c ../minishell/utils1.c ../minishell/utils2.c  ../minishell/days/d00.c ../minishell/days/d01.c ../minishell/days/d02.c ../minishell/days/d03.c ../minishell/days/d04.c ../minishell/days/export.c  ../minishell/days/d05.c \
		main.c 


C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

OBJS = $(SRCS:.c=.o)

OBJSBS = $(BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
		@echo "$(C_GREEN)[parsing CREATED]$(C_RES)"

clean: 
		@rm -rf $(OBJS) $(OBJSBS)
		@echo "$(C_RED)[OBJECTS REMOVED]$(C_RES)"

fclean: clean
		@rm -rf $(NAME)
		@echo "$(C_RED)[parsing REMOVED]$(C_RES)"

re : fclean all



