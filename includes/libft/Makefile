# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glecler <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/14 23:54:14 by glecler           #+#    #+#              #
#    Updated: 2018/12/04 14:43:41 by glecler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAG = -Wall -Wextra -Werror -Wno-nullability-completeness

SOURCE = ./ft_memset.c \
		./ft_bzero.c \
		./ft_memcpy.c \
		./ft_memccpy.c \
		./ft_memmove.c \
		./ft_memchr.c \
		./ft_memcmp.c \
		./ft_strlen.c \
		./ft_strdup.c \
		./ft_strcpy.c \
		./ft_strncpy.c \
		./ft_strcat.c \
		./ft_strncat.c \
		./ft_strlcat.c \
		./ft_isalpha.c \
		./ft_isprint.c \
		./ft_isdigit.c \
		./ft_isalnum.c \
		./ft_isascii.c \
		./ft_toupper.c \
		./ft_tolower.c \
		./ft_memalloc.c \
		./ft_memdel.c \
		./ft_strchr.c \
		./ft_strrchr.c \
		./ft_strnstr.c \
		./ft_strstr.c \
		./ft_strcmp.c \
		./ft_strncmp.c \
		./ft_atoi.c \
		./ft_putchar.c \
		./ft_putstr.c \
		./ft_strsplit.c \
		./ft_putendl.c \
		./ft_putchar_fd.c \
		./ft_putstr_fd.c \
		./ft_putendl_fd.c \
		./ft_strequ.c \
		./ft_strnequ.c \
		./ft_putnbr.c \
		./ft_putnbr_fd.c \
		./ft_itoa.c \
		./ft_strnew.c \
		./ft_strdel.c \
		./ft_strclr.c \
		./ft_striter.c \
		./ft_striteri.c \
		./ft_strmap.c \
		./ft_strmapi.c \
		./ft_strsub.c \
		./ft_strjoin.c \
		./ft_strtrim.c \
		./get_next_line.c \
		./ft_strjoin_free_s1.c \
		./ft_strjoin_free_s1s2.c

CC 	= clang
	CL=\x1b[35m
	GREEN=\033[1;32m
	RED=\033[1;31m
	CL2=\x1b[36m
	NC=\033[0m

SRCS = $(SOURCE:.c=.o)

GCC = gcc -c $(FLAG) $(SOURCE)

AR = ar rc $(NAME) $(SRCS)

all : $(NAME)

$(NAME) : 
	@$(GCC); $(AR); ranlib $(NAME)
	@@echo "$(GREEN)[✓]$(NC)$(CL) $(NAME) built$(NC)"

clean :
	@rm -rf $(SRCS)
	@@echo "$(RED)[-]$(NC)$(CL2) Objects of $(NAME) cleaned$(NC)"

fclean : clean
	@rm -rf $(NAME)
	@echo "$(RED)[-]$(NC)$(CL2) libft.a cleaned$(NC)"

re : fclean, all, clean, $(NAME)
