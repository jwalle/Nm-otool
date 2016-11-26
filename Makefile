# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/07/09 15:06:36 by jwalle            #+#    #+#              #
#    Updated: 2016/11/26 14:08:33 by jwalle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_NM = ft_nm
FT_OTOOL = ft_otool

CFLAGS = -Wall -Werror -Wextra -g

AT_FLAGS = -arch x86_64 -arch arm

TAF_FLAGS = -arch i386 -arch x86_64

CC = clang $(FAT_FLAGS)
SRCDIR_NM = ./srcs_nm/
SRCDIR_OTOOL = ./srcs_otool/
ODIR_NM = ./objs_nm/
ODIR_OTOOL = ./objs_otool/
INC = -I./includes -I./libft -I./ft_printf/includes/
LINK = -L./libft -lft -L./ft_printf -lftprintf
BLU = tput setaf 4
GRN = tput setaf 2
WHT = tput setaf 7
RESET = tput sgr 0

SRC_NM = main.c \
	  handle_library.c \
	  handle_64.c \
	  handle_32.c \
	  handle_fat.c \
	  common_functions.c \

SRC_OTOOL = main.c \
		handle_otool_32_64.c \
		handle_otool_fat.c \
		handle_otool_lib.c \
	  	common_otool.c \


OBJ_NM	=	$(SRC_NM:.c=.o)
OBJ_OTOOL	=	$(SRC_OTOOL:.c=.o)
OBJS_NM	= 	$(addprefix $(ODIR_NM), $(OBJ_NM))
OBJS_OTOOL	= 	$(addprefix $(ODIR_OTOOL), $(OBJ_OTOOL))

all :	$(LIB) $(FT_NM) $(FT_OTOOL)

$(FT_NM) : $(OBJS_NM)
	@$(BLU)
	mkdir -p $(ODIR_NM)
	make -C libft
	make -C ft_printf
	@echo "Making $(NAME)..."
	@$(CC)  -o $(FT_NM) $^ $(LINK)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

$(ODIR_NM)%.o : $(SRCDIR_NM)%.c
	@$(BLU)
	@echo "making objects..."
	mkdir -p $(ODIR_NM)
	@$(CC) $(CFLAGS) -c $^ $(INC) -o $@
	@$(GRN)
	@echo "Done !"
	@$(RESET)

$(FT_OTOOL) : $(OBJS_OTOOL)
	@$(BLU)
	mkdir -p $(ODIR_OTOOL)
	make -C libft
	make -C ft_printf
	@echo "Making $(NAME)..."
	@$(CC)  -o $(FT_OTOOL) $^ $(LINK)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

$(ODIR_OTOOL)%.o : $(SRCDIR_OTOOL)%.c
	@$(BLU)
	@echo "making objects..."
	mkdir -p $(ODIR_OTOOL)
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
	@rm -rf $(ODIR_NM)
	@rm -rf $(ODIR_OTOOL)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

fclean: clean
	@$(BLU)
	@echo "Deleting executable..."
	@rm -rf $(FT_NM)
	@rm -rf $(FT_OTOOL)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

re: fclean all
	@$(GRN)
	@echo "Project reset and Rebuild !"
	@$(RESET)


