# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 20:07:18 by mait-oub          #+#    #+#              #
#    Updated: 2025/02/01 23:17:24 by mait-oub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)

NAME = pipex
NAME_MANDATORY = pipex_mandatory
NAME_BONUS = pipex_bonus

.PHONY: clean
#vpath

UTILS_DIR = $(SRC_DIR)/utils
UTILS_FILES = \
	$(UTILS_DIR)/create_zombie.c \
	$(UTILS_DIR)/dprints.c \
	$(UTILS_DIR)/free_array.c \
	$(UTLIS_DIR)/ft_itoa.c \
	$(UTLIS_DIR)/ft_strjoin.c \
	$(UTILS_DIR)/ft_strlcat.c \
	$(UTILS_DIR)/ft_strlen.c \
	$(UTILS_DIR)/ft_strnmp.c \
	$(UTILS_DIR)/pathjoin.c \
	$(UTILS_DIR)/xsleep.c

SRC_FILES = \
	$(SRC_DIR)/pipex.c \
	$(SRC_DIR)/init_stdio.c \
	$(SRC_DIR)/create_child.c \
	$(SRC_DIR)/execute_child.c \
	$(SRC_DIR)/terminate.c \
	$(UTILS_FILES)

MANDATORY_SRCS = $(SRC_FILES) $(SRC_DIR)/main.c
MANDATORY_OBJS = $(patsubst %.c, %.o, $(MANDATORY_SRCS))

BONUS_SRCS = $(SRC_FILES) $(SRC_DIR)/main_bonus.c $(SRC_DIR)/heredoc.c
BONUS_OBJS = $(patsubst %.c, %.o, $(BONUS_SRCS))

all: $(NAME_MANDATORY)

bonus: $(NAME_BONUS)

$(NAME_MANDATORY): $(MANDATORY_OBJS)
	

$(NAME_BONUS): $(BONUS_OBJS)
	

clean:
	@rm -rfv $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -rfv $(NAME)

re: fclean re
