#CONFIG

NAME = minishell
CC = cc
DEPFLAGS = -MP -MD
RM = rm -rf

#FILES

INC = ./includes/

SRCS = ./builtins/ft_cd.c exec/exec_utils.c ./sources/utils_str.c \
	./builtins/ft_echo.c ./exec/heredoc.c ./tokenization/cmd_operand.c \
	./builtins/ft_env.c ./sources/error.c ./tokenization/cmd_operand_utils.c \
	./builtins/ft_exit.c ./sources/free_cmd.c ./tokenization/free_prompt.c \
	./builtins/ft_export.c ./sources/ft_itoa.c ./tokenization/prompt_handle.c \
	./builtins/ft_pwd.c ./sources/ft_split.c ./tokenization/quotes_after.c \
	./builtins/ft_unset.c ./sources/main.c ./tokenization/quotes.c \
	./exec/check_init.c ./sources/utils.c ./tokenization/token_init.c \
	./exec/exec_builtins.c ./sources/utils_format.c ./tokenization/token_parsing.c \
	./exec/exec_cmd.c ./sources/utils_malloc.c ./tokenization/token_utils.c \
	./exec/exec_init.c ./sources/utils_str2.c ./tokenization/var_expand.c \
	./exec/heredoc_expand.c ./tokenization/cmd_create_utils.c


OBJDIR = ./obj

OBJS = $(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(SRCS)))

DEP = $(OBJ:.o=.d)

#FLAGS

FLAGS = -Wall -Wextra -I$(INC) -g3

### RAJOUTER WERROR

#COMMANDS

all : $(NAME)

$(OBJDIR)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(DEPFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	@echo "$(YELLOW)object files deleted.$(DEFAULT)"

fclean : clean
	$(RM) $(NAME)
	@echo "$(RED)all files deleted.$(DEFAULT)"

re : fclean all

.PHONY:
		fdf all clean fclean bonus re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
