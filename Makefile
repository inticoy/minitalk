# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyoon <gyoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 16:44:08 by gyoon             #+#    #+#              #
#    Updated: 2023/01/30 16:24:09 by gyoon            ###   ########.fr        #
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

ifdef BONUS
   F_S_OBJS = $(B_S_OBJS)
   F_C_OBJS = $(B_C_OBJS)
else
   F_S_OBJS = $(S_OBJS)
   F_C_OBJS = $(C_OBJS)
endif

all : $(NAME)

$(SERVER) : $(F_S_OBJS) $(LIBFT)
	$(CC) $(F_S_OBJS) -o $@ -I $(INCLUDES) -l ft -L ./libft

$(CLIENT) : $(F_C_OBJS) $(LIBFT)
	$(CC) $(F_C_OBJS) -o $@ -I $(INCLUDES) -l ft -L ./libft

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

re :
	make fclean
	make all

.PHONY : all clean fclean re .c.o