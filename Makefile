NAME		:=	minishell
COMPILER	:=	cc
DEBUG_MODE	:=	
FLAGS		:= 	-Wall -Wextra -Werror
LIBS		:= 	./libft/libft.a -lreadline -I /Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib
HEADERS		:= 	-I libft -I includes -I /Users/$(USER)/.brew/opt/readline/include 
SRCS		:= 	main.c \
				lexing/lexer.c \
				lexing/line_checker.c \
				lexing/line_checker_checks.c \
				lexing/lexer_utils.c \
				lexing/enum_arrayfts.c \
				lexing/get_path.c \
				lexing/eddit_line.c \
				lexing/split_quotes.c \
				lexing/splitquo_quotefts.c \
				lexing/split_quotes_utils.c \
				lexing/data_org.c \
				lexing/dataorg_cases.c \
				lexing/dataorg_utils.c \
				lexing/dataorg_special_cases.c \
				lexing/dataorg_command.c \
				lexing/into_list.c \
				lexing/into_list_cases.c \
				lexing/intolist_other.c \
				lexing/parsing_grep.c \
				lexing/parser_cat.c \
				lexing/parsing_echo.c \
				lexing/variable_expander.c \
				lexing/varexp_utils.c \
				lexing/varexp_arrayft.c \
				lexing/varexp_lineft.c \
				lexing/file_delim_func.c \
				lexing/list_checks.c \
				error/error.c \
				error/err_log.c \
				error/free.c \
				error/memory_management.c \
				execution/execution_processes.c \
				execution/execution_utilities.c \
				execution/execution_heredoc.c \
				execution/execution_heredoc_expansion.c \
				execution/execution_heredoc_utilities.c \
				execution/execution_routing.c \
				execution/execution_absolute_path.c \
				builtins/builtin_utilities.c \
				builtins/builtin_execution.c \
				builtins/builtin_cd.c \
				builtins/builtin_echo.c \
				builtins/builtin_env.c \
				builtins/builtin_export.c \
				builtins/builtin_pwd.c \
				builtins/builtin_unset.c \
				builtins/builtin_exit.c \
				interface/interface_frontend.c \
				utilities/utilities_debugging.c \
				utilities/utilities_misc.c \
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
	COMPILER += -g
	LIBFT_DEBUG += DEBUG=1
	DEBUG_MODE += "(debug mode)"
endif

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft $(LIBFT_DEBUG) 
	@$(COMPILER) $^ $(LIBS) -o $(NAME)
	@echo $(Green) $(Bold) $(DEBUG_MODE) Minishell compiled succesfully ✅ $(Text_Off)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(@D) 
	@echo $(Cyan) Building... [$<] $(Text_Off)
	@$(COMPILER) $(FLAGS) $(HEADERS) -c $< -o $@

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
