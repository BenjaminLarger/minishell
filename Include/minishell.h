#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../Library/Libft/libft.h"
# include "../Library/Ft_printf/ft_printf.h"
# include "error.h"
# include "list.h"
# include <stdbool.h>
# define MAX_PATH_LEN 1024
# define FALSE 0
# define TRUE 1
# define FAILURE 1
# define SUCCESS 0


// 1_read_input.c //
void	read_input(void);

#endif