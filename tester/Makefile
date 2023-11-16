NAME		:=	app
COMPILER	:=	cc
FLAGS		:= 	-Wall -Wextra -Werror
LIBS		:= 	./libft/libft.a -I
HEADERS		:= 	-I include
SRCS		:= 	tester.c \

SRCDIR 		:= 	./src
OBJDIR 		:= 	./obj
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

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft $(LIBFT_DEBUG) 
	@$(COMPILER) $^ $(LIBS) -o 
	@echo $(Green) $(Bold) Tester is built ✅ $(Text_Off)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(@D) 
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

re:	fclean all

.PHONY:	all, clean, fclean, re

