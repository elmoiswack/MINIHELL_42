NAME		:=	minishell
FLAGS		:= 	-Wall -Wextra #-Werror
LIBS		:= 	./libft/libft.a -lreadline -I /Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib
HEADERS		:= 	-I libft -I includes -I /Users/$(USER)/.brew/opt/readline/include 
SRCS		:= 	main.c \
				memory_management.c \
				lexing/lexer.c \
				lexing/lexer_utils.c \
				lexing/enum_arrayfts.c \
				lexing/get_path.c \
				lexing/eddit_line.c \
				lexing/split_quotes.c \
				lexing/split_quotes_utils.c \
				lexing/data_org.c \
				lexing/dataorg_utils.c \
				lexing/data_org_special.c \
				lexing/into_list.c \
				lexing/parsing_grep.c \
				lexing/parser_cat.c \
				lexing/parsing_echo.c \
				lexing/variable_expander.c \
				lexing/varexp_utils.c \
				lexing/varexp_mult.c \
				lexing/varexp_checks.c \
				lexing/delimiter_func.c \
				error/error.c \
				error/free.c \
				execution/execution_processes.c \
				execution/execution_utilities.c \
				execution/execution_heredoc.c \
				builtins/builtin_operations.c \
				builtins/builtin_execution.c \
				interface/interface_frontend.c \
				utilities/utilities_double_arrays.c \
				signals/signal_handler.c \

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
	@$(CC) $^ $(LIBS) -o $(NAME)
	@echo $(Green) $(Bold) Minishell compiled succesfully ✅ $(Text_Off)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(@D) 
	@echo $(Cyan) Building... [$<] $(Text_Off)
	@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR):
	@mkdir $@

clean:
	@rm -rf $(OBJDIR)
	@echo $(Yellow) Cleaned object files! $(Text_Off)
	@$(MAKE) -C libft clean

fclean:	clean
	@rm -f $(NAME) 
	@echo $(Yellow) Cleaned executable! $(Text_Off)
	@$(MAKE) -C libft fclean

compile_cmd: fclean
	@compiledb make; mv *.json ./data

re:	fclean all

.PHONY:	all, clean, fclean, re
