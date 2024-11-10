# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 10:05:31 by mes-salh          #+#    #+#              #
#    Updated: 2024/11/10 04:33:58 by mes-salh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philosofers.c initialisation.c safesyscall.c tools.c tools1.c tools2.c routine.c

HEADER = philosofers.h

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

TFLAGS = -pthread
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) 

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@ $(TFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

go: all clean

.PHONY: all clean fclean re