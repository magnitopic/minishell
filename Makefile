# Minishell
NAME			=	minishell

SHELL_SRC	=	src/minishell.c \
				src/signals.c \
				src/execution.c \
				src/create_arrays.c \
				src/create_vars.c \
				src/parsing.c \
				src/utils.c

OBJS			= $(SHELL_SRC:.c=.o)

# Libft
LIBFT			=	libft.a
LIBFT_SRC		=	./libft/

# Compiler
CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Werror -Wextra
EXTRAFLAGS		=	-lreadline

# Colours
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
WHITE			=	\033[0;37m
RESET			=	\033[0m

# Rules
all:		$(LIBFT) $(NAME)
			@printf "$(BLUE)==> $(CYAN)Minishell compiled ✅\n\n$(RESET)"

$(LIBFT):
			@make -C libft bonus

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(EXTRAFLAGS) $(LIBFT_SRC)$(LIBFT) -o $(NAME)

clean:
			@$(RM) $(NAME) $(OBJS) $(OBJSBNS) $(NAME_BONUS)
			@printf "\n$(BLUE)==> $(RED)Removed Minishell 🗑️\n$(RESET)"

fclean:		clean
			@make -C libft fclean

re:			fclean all
			@printf "$(BLUE)==> $(CYAN)Minishell recompiled 🔄\n$(RESET)"

.PHONY:		all clean fclean re
