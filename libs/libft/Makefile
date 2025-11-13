# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/25 15:39:13 by jarregui          #+#    #+#              #
#    Updated: 2025/09/10 22:49:16 by jarregui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# INCLUDE COLOR VARIABLES DECLARATION:
include ../colors.mk

# VARIABLES DECLARATION:
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LIB_NAME	= 	LIBFT LIBRARY
NAME		=	libft.a
RM			=	/bin/rm -f
SRCS		=	$(addprefix functions/, \
				ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c)


OBJS		=	${SRCS:.c=.o}

# RULES DECLARATION:
all:	${NAME}

%.o: %.c
	@echo "${ORANGE}${LIB_NAME} compiling file: $(BROWN)[$<]...${DEF_COLOR}"
	@${CC} ${CFLAGS} -c $< -o $@

# CREAMOS BIBLIOTECA ESTATICA Y NO UN EJECUTABLE (NO HAY MAIN)
${NAME}:	${OBJS}
	ar -rc ${NAME} ${OBJS}
	ranlib ${NAME}
	@echo "$(GREEN)✓ Created ${NAME}$(DEF_COLOR)\n"

clean:
	${RM} ${OBJS}
	@echo "\n$(GREEN)✓ All objects from ${LIB_NAME} cleaned successfully$(DEF_COLOR)\n"

fclean:	clean
	${RM} ${NAME}
	@echo "\n$(GREEN)✓ All executable from ${LIB_NAME} cleaned successfully $(DEF_COLOR)\n"

re:	fclean all

.PHONY:	all clean fclean re