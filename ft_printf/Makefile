CC = cc
CFLAGS = -Werror -Wall -Wextra
NAME = libftprintf.a
MANDATORY_SRCS = ft_printf.c print_addr.c print_char.c print_hex.c print_nbr_u.c print_nbr.c print_str.c
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

LIBFT_DIR = ../libft
LIBFT_LIB = libft.a

all : $(NAME)

$(NAME) : $(MANDATORY_OBJS) $(LIBFT_DIR)/*.c
	make -C $(LIBFT_DIR) all
	cp $(LIBFT_DIR)/$(LIBFT_LIB) ./$(NAME)
	ar rcs $@ $(MANDATORY_OBJS)

$(MANDATORY_OBJS) : $(MANDATORY_SRCS)
	$(CC) $(CFLAGS) -c $(MANDATORY_SRCS)

clean :
	make -C $(LIBFT_DIR) clean
	rm -rf $(MANDATORY_OBJS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re