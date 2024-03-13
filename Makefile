SHELL		= /bin/sh

NAME		:= minishell


CC			= gcc
CFLAGS		:= -Wextra -Wall -Werror \
	-Wunreachable-code -g -fsanitize=address,undefined \

LDFLAGS		= -L$(HOME)/.brew/opt/readline/lib

## LIBS ##
LIBFT		:= ./lib/libft
LIBS		= ${LIBFT}/libft.a -lreadline

## HEADERS ##
HEADER_SRCS	:=	minishell.h errors.h structures.h
HEADER_DIR	:=	inc/
HEADERS		= -I $(HEADER_DIR) -I ${LIBFT} -I$(HOME)/.brew/opt/readline/include

## SOURCE ##
SRCS		:= main.c \
	shell.c shell_process_args.c \
	input.c input_assign_tokens.c input_count_tokens.c \
	signal_handle.c signal_sigint.c signal_exit.c \
	builtin_cd.c builtin_echo.c builtin_pwd.c builtin_env.c \
	builtin_export.c env_variable_handling.c last_exit_status.c\
	shell_exec_args.c path.c shell_exec_builtin.c \
	redirections.c \
	utils_joinfree.c utils_process_args.c \
	cleanup_free_arrays.c \
	error_handling.c \
	dev_utils.c \

SRC_DIR		:= src/
BUILD_DIR	:= build/
SRCS		:= $(addprefix $(SRC_DIR),$(SRCS))
OBJS		:= $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRCS))

## TARGET ##
all		: libft $(NAME)
	@echo "${BMAG}Build successful!${NC}"

libft	:
	@echo "${MAG}Building ${BMAG}libft...${NC}"
	@${MAKE} -C ${LIBFT}
	@echo "${BMAG}libft ${MAG}build complete.${NC}"

$(NAME)	: $(OBJS)
	@echo "${BCYA}Creating executable: $(NAME)${NC}"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "${BMAG}$(NAME) ${MAG}build complete.${NC}"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HEADER_DIR), $(HEADER_SRCS))
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "${BGRE}Compiling:${NC} $(notdir $<) \
		${MAG}for ${BMAG}$(NAME)${NC} "

clean	:
	@echo "$(RED)Cleaning$(NC)"
	rm -f $(OBJS)
	rm -rf $(BUILD_DIR)
	${MAKE} -C ${LIBFT} fclean

fclean	: clean
	rm -f $(NAME)

re		: fclean all

.PHONY	: all, clean, fclean, re, libft
.DEFAULT_GOAL := all

## Colors ##
RED		:= \033[0;31m
BRED	:= \033[1;31m
GRE		:= \033[0;32m
BGRE	:= \033[1;32m
YEL		:= \033[0;33m
BYEL	:= \033[1;33m
BLU		:= \033[0;34m
BBLU	:= \033[1;34m
MAG		:= \033[0;35m
BMAG	:= \033[1;35m
CYA		:= \033[0;36m
BCYA	:= \033[1;36m
BWHI	:= \033[1;37m
NC		:= \033[0m
