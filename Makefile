# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 00:00:50 by flip              #+#    #+#              #
#    Updated: 2023/07/10 17:18:49 by dhussain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
FLAGS		:= 	-Wall -Wextra -Werror
LIBFT		:= 	./libft/libft.a -lreadline
HEADERS		:= 	-I ./includes/libft -I ./includes
SRCS		:= 	main.c \
				lexer.c \
				lexer_utils.c \
				lexer_dataorg_utils.c \
				lexer_get_path.c \
				lexer_eddit_line.c \
				lexer_split_quotes.c \
				lexer_data_org.c \
				lexer_data_envvar.c \
				lexer_into_list.c \
				error.c \
				execution_processes.c \
				execution_utilities.c \
				execution_builtin_operations.c \
				execution_heredoc.c \
				execution_builtin.c \
				interface_frontend.c \
				utilities_double_arrays.c \

SRCDIR 		:= 	./srcs
OBJDIR 		:= 	./objs
OBJS		:= 	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS		:= 	$(addprefix $(SRCDIR)/,$(SRCS))

# Colors #############################################
Black		= "\033[0;30m"		# Black
Red			= "\033[0;31m"		# Red
Green		= "\033[0;32m"		# Green
Yellow		= "\033[0;33m"		# Yellow
Blue		= "\033[0;34m"		# Blue
Purple		= "\033[0;35m"		# Purple
Cyan		= "\033[0;36m"		# Cyan
White		= "\033[0;37m"		# White
Text_Off	= "\033[0m"			# Text Style Off
Bold		= "\033[1m"			# Text Style Bold
######################################################

ifdef DEBUG
	CC += -g -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	@$(CC) $^ $(LIBFT) -lreadline $(HEADERS) -o $(NAME)
	@echo $(Green) $(Bold) Minishell compiled succesfully ✅ $(Text_Off)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS)

clean:
	@rm -rf $(OBJDIR)
	@echo $(Yellow) Minishell: cleaned object files! $(Text_Off)
	@$(MAKE) -C libft clean

fclean:	clean
	@rm -f $(NAME) 
	@echo $(Yellow) Minishell: cleaned executable! $(Text_Off)
	@$(MAKE) -C libft fclean

compile_cmd: fclean
	@compiledb make; mv *.json ./data

re:	fclean all

.PHONY:	all, clean, fclean, re
