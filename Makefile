# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/05 13:15:15 by vomelchu          #+#    #+#              #
#    Updated: 2019/02/05 13:15:17 by vomelchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

FLAG = -Wall -Wextra -Werror

SRC :=	$(wildcard ./src/*.cpp)

INCLUDES	=	-I ./inc

RUN = clang++

OBJ	= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ $(RUN) -o $(NAME) $(OBJ) $(INCLUDES) #-fsanitize=address
	@ echo "Done ✓" $(NAME)

%.o: %.cpp
	@ $(RUN) $(INCLUDES) -c -o $@ $<

clean:
	@ rm -rf $(OBJ)

fclean:
	@ rm -rf $(OBJ)
	@ rm -f $(NAME)

re: fclean all
