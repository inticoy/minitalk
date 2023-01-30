# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 16:44:08 by gyoon             #+#    #+#              #
#    Updated: 2023/01/30 15:55:29 by gyoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(SERVER) $(CLIENT)

CC = cc
AR = ar
RM = rm -rf

ARFLAGS = -rcs
CFLAGS = -Wall -Wextra -Werror

S_SRCS = 	./src/server.c \
			./src/raise_exception.c
C_SRCS = 	./src/client.c \
			./src/raise_exception.c

S_OBJS = $(S_SRCS:.c=.o)
C_OBJS = $(C_SRCS:.c=.o)

INCLUDES = ./include

LIBFT = ./libft/libft.a
SERVER = server
CLIENT = client

all : $(NAME)

$(SERVER) : $(S_OBJS) $(LIBFT)
	$(CC) $(S_OBJS) -o $@ -I $(INCLUDES) -l ft -L ./libft

$(CLIENT) : $(C_OBJS) $(LIBFT)
	$(CC) $(C_OBJS) -o $@ -I $(INCLUDES) -l ft -L ./libft

$(LIBFT) :
	make -C libft

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I include

clean :
	make -C libft clean
	$(RM) $(S_OBJS)
	$(RM) $(C_OBJS)

fclean :
	make -C libft fclean
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re .c.o