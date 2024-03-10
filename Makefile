# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 20:08:54 by ishenriq          #+#    #+#              #
#    Updated: 2024/03/10 18:28:46 by ishenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
#NAME_BONUS = pipex_bonus
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3 -O3
CC	:= cc
PRINTF	:= lib/printf/
LIBFT	:= lib/libft/
BUILD_DIR = objects/
MKDIR  := mkdir -p

HEADERS	:= -I ./include -I $(LIBFT) -I $(PRINTF) $(LIBS)

LIBS 	:= -lm $(LIBFT)libft.a \
	-lm $(PRINTF)libftprintf.a

LDFLAGS	:= $(HEADERS) $(LIBS)

SRCS	= $(wildcard src/mandatory/*.c)
SRCS_BONUS      = $(wildcard src/bonus/*.c)

OBJS	+=  $(SRCS:%.c=$(BUILD_DIR)%.o)
OBJS_BONUS      += $(SRCS_BONUS:%.c=$(BUILD_DIR)%.o)

ifdef   WITH_BONUS
        #NAME = $(NAME_BONUS)
        OBJS = $(OBJS_BONUS)
endif

define create_dir
	$(MKDIR) $(dir $@)
endef

define bonus
    $(MAKE) WITH_BONUS=TRUE
endef

all: libft printf $(NAME)

$(BUILD_DIR)%.o: %.c
	$(call create_dir)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

libft:
	@make -C $(LIBFT)

printf:
	@make -C $(PRINTF)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

bonus:
	$(call bonus)


clean:
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT) clean
	@make -C $(PRINTF) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@make -C $(LIBFT) fclean
	@make -C $(PRINTF) fclean

re: clean all

re_bonus: clean bonus

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) ./include

.PHONY: all, clean, fclean, re, libft, printf, bonus
.DEFAULT_GOAL := all
