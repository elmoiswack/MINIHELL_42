NAME		:=	minishell
FLAGS		:= 	-Wall -Wextra -Werror
LIBS		:= 	./libft/libft.a -lreadline -I /Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib
HEADERS		:= 	-I libft -I includes -I /Users/$(USER)/.brew/opt/readline/include
SRCS		:= 	main.c \
				lexing/lexer.c \
				lexing/lexer_utils.c \
				lexing/lexer_dataorg_utils.c \
				lexing/lexer_get_path.c \
				lexing/lexer_eddit_line.c \
				lexing/lexer_split_quotes.c \
				lexing/lexer_data_org.c \
				lexing/lexer_data_envvar.c \
				lexing/lexer_into_list.c \
				error/error.c \
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
