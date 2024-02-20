.PHONY: all re clean fclean libft
SERVER= server
CLIENT= client

SERVER_SRCS= $(addprefix srcs/server/, \
server.c)
SERVER_OBJS= $(SERVER_SRCS:.c=.o)

CLIENT_SRCS= $(addprefix srcs/client/, \
client.c)
CLIENT_OBJS= $(CLIENT_SRCS:.c=.o)

FLAGS= -Wall -Werror -Wextra

LFT_DIR= libs/libft
LFT_A= $(LFT_DIR)/libft.a

$(SERVER): $(LFT_A) $(SERVER_OBJS)
	gcc -g $(FLAGS) $(SERVER_OBJS) $(LFT_A) -o $(SERVER)

$(CLIENT): $(LFT_A) $(CLIENT_OBJS)
	gcc -g $(FLAGS) $(CLIENT_OBJS) $(LFT_A) -o $(CLIENT)

all: $(SERVER) $(CLIENT)

clean:
	make -C $(LFT_DIR) clean BONUS=1
	rm -rf $(SERVER_OBJS) $(CLIENT_OBJS)

fclean:
	make clean
	make -C $(LFT_DIR) fclean BONUS=1
	rm -rf $(SERVER) $(CLIENT)

re:
	make fclean
	make all

%.o: %.c
	gcc -c $< -o $@ $(FLAGS) -I.

$(LFT_A):
	make -C $(LFT_DIR) BONUS=1
