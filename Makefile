# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 15:03:33 by jdhallen          #+#    #+#              #
#    Updated: 2025/01/13 17:44:49 by jdhallen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

exec = philosopher

SRCS = main.c parent.c init.c philosopher.c utils.c

OBJS = $(SRCS:.c=.o)

all: $(exec)

$(exec): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(exec)
	echo "exec ok"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	echo "clean ok"

fclean: clean
	@rm -f $(exec)
	echo "fclean ok"

re: fclean all

.PHONY: all clean fclean re
