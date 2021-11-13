DIR_HEADERS	= ./includes/

DIR_SRCS	= ./srcs/

DIR_LIBS	= ./libft/

NAME = minishell

CFLAG = -I $(DIR_HEADERS) -I /Users/$(USER)/.brew/Cellar/readline/8.1/include

FLAGS = -L $(DIR_LIBS) -lft -lreadline -L /Users/$(USER)/.brew/Cellar/readline/8.1/lib/

SRC = launch/main.c launch/init_env.c launch/signal.c launch/all_free.c \
parser/parser.c parser/add_token.c parser/check_utils.c parser/check_utils_2.c \
parser/parse_env.c parser/parse_quot.c parser/parse_quot_utils.c parser/parse_separator.c \
parser/pass_utils.c parser/ft_arraypush.c \
parser/token_list.c parser/error.c \
builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c \
builtin/export_new.c builtin/export_no_args.c builtin/pwd.c builtin/unset.c builtin/utils.c \
exec/commands.c exec/exec_bin.c exec/heredoc.c exec/pipes.c \
exec/pipes_parent.c exec/pipes_utils.c exec/redirects.c exec/utils.c exec/diff_split.c exec/list_to_array.c \
exec/to_absolute.c exec/handle_signals.c

SRCS = $(addprefix $(DIR_SRCS), $(SRC))

OBJS = $(SRCS:.c=.o)

GCC	= gcc -g -Wall -Werror -Wextra

RM	= rm -f

%.o: %.c
		$(GCC) -c $< -o $@ $(CFLAG)

all: $(NAME)

$(NAME) : 		$(OBJS) $(DIR_HEADERS)*.h $(DIR_LIBS)
				@make bonus -s -C $(DIR_LIBS)
				@$(GCC) $(FLAGS) $(CFLAG) $(OBJS) -o $(NAME)
				@echo "$(FONT00)$(COLOR6)$@$(FONT99)is$(FONT5)ready$(FONT99)"

clean:
	make clean -C $(DIR_LIBS)
	$(RM) $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(DIR_LIBS)

re: fclean all

.PHONY: all clean fclean re

FONT99 = \033[0m #сброс цвета
FONT00 = \033[1m #жирный шрифт
FONT01 = \033[4m #подчеркивание
COLOR0 = \033[47m #серый цвет фона
FONT3 = \033[34m #синий цвет шрифта
FONT4 = \033[33m #желтый цвет шрифта
COLOR5 = \033[42m #зелёный цвет фона
FONT5 = \033[32m #зелёный цвет шрифта
COLOR6 = \033[41m #красный цвет фона
FONT6 = \033[31m #красный цвет шрифта
COLOR7 = \033[40m #чёрный цвет фона