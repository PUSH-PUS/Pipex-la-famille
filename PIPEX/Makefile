NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = \
    SRC/util2.c SRC/pipex.c SRC/child-binS.c SRC/main.c SRC/util.c SRC/splitt.c \
    LIBFT/ft_strlen.c LIBFT/ft_atoi.c LIBFT/ft_bzero.c LIBFT/ft_calloc.c \
    LIBFT/ft_isalnum.c LIBFT/ft_isalpha.c LIBFT/ft_isascii.c LIBFT/ft_isdigit.c \
    LIBFT/ft_isprint.c LIBFT/ft_itoa.c LIBFT/ft_memchr.c LIBFT/ft_memcmp.c \
    LIBFT/ft_memcpy.c LIBFT/ft_memmove.c LIBFT/ft_memset.c LIBFT/ft_putchar_fd.c \
    LIBFT/ft_putendl_fd.c LIBFT/ft_putnbr_fd.c LIBFT/ft_putstr_fd.c LIBFT/ft_split.c \
    LIBFT/ft_strchr.c LIBFT/ft_striteri.c LIBFT/ft_strjoin.c LIBFT/ft_strlcat.c \
    LIBFT/ft_strmapi.c LIBFT/ft_strncmp.c LIBFT/ft_strnstr.c LIBFT/ft_strrchr.c \
    LIBFT/ft_strtrim.c LIBFT/ft_substr.c LIBFT/ft_tolower.c LIBFT/ft_toupper.c \
    LIBFT/ft_strlcpy.c LIBFT/ft_strdup.c

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
