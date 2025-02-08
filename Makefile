#########COLORS##########
RESET			= \033[0m
BLACK			= \033[1;30m
RED				= \033[1;31m
GREEN			= \033[1;32m
YELLOW			= \033[1;33m
BLUE			= \033[1;34m
PURPLE			= \033[1;35m
CYAN			= \033[1;36m
WHITE			= \033[1;37m

##########FLAGS##########
CC				= cc
#CPFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address
CPFLAGS			= -Wall -Wextra -Werror -g -fsanitize=thread
RM				= rm -rf

##########FILES & FOLDERS##########
NAME			= philo
SRC				= srcs
OBJ_DIR			= objs
_FILES			= init free utils table
OBJS			= $(_FILES:%=%.o)
TARGET			= $(addprefix $(OBJ_DIR)/, $(OBJS))
DEPS			= includes


##########RULES##########
all				: 	$(NAME)

$(NAME)			:	$(OBJ_DIR) $(TARGET) philo.c
					echo "[$(CYAN) Compiling $(RESET)] $(GREEN)Main$(RESET)"
					$(CC) $(CPFLAGS) philo.c $(TARGET) $(LIBFT) $(PRINTF) -o $(NAME) -I $(DEPS)

					echo "$(GREEN)Done.$(RESET)"

$(OBJ_DIR)/%.o	:$(SRC)/%.c
					echo "[$(CYAN)Compiling$(RESET)] $(CPFLAGS) $(GREEN)$<$(RESET)"
					$(CC) $(CPFLAGS) -c $< -o $@ -I $(DEPS)

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)

clean			:
					${RM} main.o
					echo "[$(RED)Deleted$(RESET)] $(GREEN)MAIN$(RESET)"
					$(RM) $(OBJ_DIR)
					echo "[$(RED)Deleted$(RESET)] $(GREEN)OBJS$(RESET)"


fclean			: clean
					${RM} ${NAME}
					echo "[$(RED)Deleted$(RESET)] $(GREEN)${NAME}$(RESET)"

re				: fclean all

.PHONY:		all clean fclean re

.SILENT:
