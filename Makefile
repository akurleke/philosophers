# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akurleke <akurleke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 12:09:30 by akurleke          #+#    #+#              #
#    Updated: 2022/06/17 15:16:43 by akurleke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

HEADER	= 	philo.h

LIST	=	main.c			philo_utils.c

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror -I$(HEADER)

OBJS	=	$(patsubst %.c, %.o, $(LIST))

.PHONY = all clean fclean re bonus

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER) $?
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "OBJECTS deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all
