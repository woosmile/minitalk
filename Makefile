CC = cc
CFLAGS = -Werror -Wall -Wextra
NAME = server client
MANDATORY_SRCS = server.c client.c
BONUS_SRCS = server_bonus.c client_bonus.c minitalk_utils_bonus.c
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

FT_PRINTF_DIR = ft_printf
FT_PRINTF_LIB = libftprintf.a

LIBFT_DIR = libft

ifdef WITH_BONUS
        SERVER_OBJS = server_bonus.o minitalk_utils_bonus.o
else
        SERVER_OBJS = server.o
endif

ifdef WITH_BONUS
		CLIENT_OBJS = client_bonus.o minitalk_utils_bonus.o
else
		CLIENT_OBJS = client.o
endif

all : $(NAME)

bonus :
	make WITH_BONUS=1 all

server : $(SERVER_OBJS) $(FT_PRINTF_DIR)/*.c $(LIBFT_DIR)/*.c
	make -C $(FT_PRINTF_DIR) all
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) -L./ft_printf -lftprintf

client : $(CLIENT_OBJS) $(FT_PRINTF_DIR)/*.c $(LIBFT_DIR)/*.c
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -L./ft_printf -lftprintf

server.o : server.c
	$(CC) $(CFLAGS) -c $^

client.o : client.c
	$(CC) $(CFLAGS) -c $^

server_bonus.o : server_bonus.c minitalk_utils_bonus.c
	$(CC) $(CFLAGS) -c $^

client_bonus.o : client_bonus.c minitalk_utils_bonus.c
	$(CC) $(CFLAGS) -c $^

clean :
	make -C $(FT_PRINTF_DIR) clean	
	rm -rf $(MANDATORY_OBJS)
	rm -rf $(BONUS_OBJS)

fclean : clean
	make -C $(FT_PRINTF_DIR) fclean
	rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re