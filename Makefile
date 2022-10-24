CC = gcc

SRCS 	= exec/builtin_utils.c exec/builtin.c exec/env_functions.c exec/exec_checkers.c exec/exec_cond.c exec/exec_utils.c exec/exec.c \
	shell/minishell.c shell/prompt.c parse/check.c parse/parse_utils.c parse/parse.c parse/tokenizer.c parse/var_expansion.c \
	utils/concat.c utils/ft_realloc.c utils/init_vars.c utils/matrix_functions.c utils/matrix_functions2.c utils/utils.c \
	utils/string_functions.c utils/ft_isnum.c parse/update_line.c exec/redirections.c parse/redir.c shell/signal.c exec/helper_exec.c\
	shell/free.c parse/helper_update.c exec/checker_helper.c


NAME = minishell

OBJS = $(SRCS:.c=.o)

#CFLAGS = -g -I ~/.brew/opt/readline/include -L ~/.brew/opt/readline/lib -lreadline -fsanitize=address -lreadline
#CFLAGS = -g -Wall -Werror -Wextra -fsanitize=address -lreadline
#CFLAGS = -g  -fsanitize=address -lreadline
CFLAGS = -g  -Wall -Werror -Wextra -fsanitize=address -lreadline 

LIBFT= libft/libft.a

%.o:%.c *.h
	make -C libft
	$(CC) $(CFLAGS) -c $< -o $@

all: *.h
	@$(MAKE) $(NAME)

$(NAME): $(OBJS)
	make bonus -C libft
		$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(CFLAGS)
#	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	make clean -C libft
	rm -rf *.o exec/*.o parse/*.o shell/*.o utils/*.o

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all%