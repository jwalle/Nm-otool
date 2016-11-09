# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/07/09 15:06:36 by jwalle            #+#    #+#              #
#    Updated: 2016/11/01 14:51:13 by jwalle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm
CFLAGS = -Wall -Werror -Wextra -g

FAT_FLAGS = -arch x86_64 -arch arm

TAF_FLAGS = -arch i386 -arch x86_64

CC = clang $(FAT_FLAGS)
SRCDIR = ./srcs/
ODIR = ./objs/
INC = -I./includes -I./libft -I./ft_printf/includes/
LINK = -L./libft -lft -L./ft_printf -lftprintf
BLU = tput setaf 4
GRN = tput setaf 2
WHT = tput setaf 7
RESET = tput sgr 0

SRC = main.c \
	  sort.c \
	  handle_library.c \
	  handle_64.c \
	  handle_32.c \
	  handle_fat.c \
	  common_functions.c \


OBJ		=	$(SRC:.c=.o)
OBJS	= 	$(addprefix $(ODIR), $(OBJ))

all :	$(LIB) $(NAME)

$(NAME) : $(OBJS)
	@$(BLU)
	mkdir -p $(ODIR)
	make -C libft
	make -C ft_printf
	@echo "Making $(NAME)..."
	@$(CC)  -o $(NAME) $^ $(LINK)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

$(ODIR)%.o : $(SRCDIR)%.c
	@$(BLU)
	@echo "making objects..."
	mkdir -p $(ODIR)
	@$(CC) $(CFLAGS) -c $^ $(INC) -o $@
	@$(GRN)
	@echo "Done !"
	@$(RESET)


$(LIB):
	@$(BLU)
	@echo "Compiling libft..."
	@make -C libft
	@$(GRN)
	@echo "Done !"
	@$(BLU)
	@echo "Compiling printf..."
	make -C ft_printf
	@$(GRN)
	@echo "Done !"
	@$(RESET)

clean:
	@make -C libft fclean
	@make -C ft_printf fclean
	@$(BLU)
	@echo "Cleaning objects..."
	@rm -rf $(ODIR)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

fclean: clean
	@$(BLU)
	@echo "Deleting executable..."
	@rm -rf $(NAME)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

re: fclean all
	@$(GRN)
	@echo "Project reset and Rebuild !"
	@$(RESET)


