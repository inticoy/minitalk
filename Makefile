# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 16:44:08 by gyoon             #+#    #+#              #
#    Updated: 2023/01/30 16:12:33 by gyoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef BONUS
    NAME = $(SERVER_BONUS) $(CLIENT_BONUS)
else
    NAME = $(SERVER) $(CLIENT)
endif

CC = cc
AR = ar
RM = rm -rf

ARFLAGS = -rcs
CFLAGS = -Wall -Wextra -Werror

S_SRCS = 	./src/server.c \
			./src/raise_exception.c
C_SRCS = 	./src/client.c \
			./src/raise_exception.c

B_S_SRCS = ${S_SRCS:.c=_bonus.c}
B_C_SRCS = ${C_SRCS:.c=_bonus.c}

S_OBJS = $(S_SRCS:.c=.o)
C_OBJS = $(C_SRCS:.c=.o)

B_S_OBJS = ${S_OBJS:.o=_bonus.o}
B_C_OBJS = ${C_OBJS:.o=_bonus.o}

INCLUDES = ./include

LIBFT = ./libft/libft.a

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

all : $(NAME)

$(SERVER) : $(S_OBJS) $(LIBFT)
	$(CC) $(S_OBJS) -o $@ -I $(INCLUDES) -l ft -L ./libft

$(CLIENT) : $(C_OBJS) $(LIBFT)
	$(CC) $(C_OBJS) -o $@ -I $(INCLUDES) -l ft -L ./libft

$(SERVER_BONUS) : $(B_S_OBJS) $(LIBFT)
	$(CC) $(B_S_OBJS) -o $@ -I $(INCLUDES) -l ft -L ./libft

$(CLIENT_BONUS) : $(B_C_OBJS) $(LIBFT)
	$(CC) $(B_C_OBJS) -o $@ -I $(INCLUDES) -l ft -L ./libft

$(LIBFT) :
	make -C libft

bonus :
	make BONUS=1 all


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I include

clean :
	make -C libft clean
	$(RM) $(S_OBJS)
	$(RM) $(C_OBJS)
	$(RM) $(B_S_OBJS)
	$(RM) $(B_C_OBJS)

fclean :
	make -C libft fclean
	make clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)
	$(RM) $(SERVER_BONUS)
	$(RM) $(CLIENT_BONUS)

re :
	make fclean
	make all

.PHONY : all clean fclean re .c.o