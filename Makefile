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
NAME_MANDATORY = .pipex_mandatory
NAME_BONUS = .pipex_bonus

.PHONY: clean $(OBJ_DIR)

UTILS_DIR = $(SRC_DIR)/utils
UTILS_FILES = \
	$(UTILS_DIR)/create_zombie.c \
	$(UTILS_DIR)/dprints.c \
	$(UTILS_DIR)/free_array.c \
	$(UTILS_DIR)/ft_itoa.c \
	$(UTILS_DIR)/ft_split.c \
	$(UTILS_DIR)/ft_strchr.c \
	$(UTILS_DIR)/ft_strjoin.c \
	$(UTILS_DIR)/ft_strlcat.c \
	$(UTILS_DIR)/ft_strlen.c \
	$(UTILS_DIR)/ft_strncmp.c \
	$(UTILS_DIR)/get_next_line.c \
	$(UTILS_DIR)/get_next_line_utils.c \
	$(UTILS_DIR)/pathjoin.c \
	$(UTILS_DIR)/xsleep.c

SRC_FILES = \
	$(SRC_DIR)/close_stdio.c \
	$(SRC_DIR)/create_child.c \
	$(SRC_DIR)/execute_child.c \
	$(SRC_DIR)/init_stdio.c \
	$(SRC_DIR)/pipex.c \
	$(SRC_DIR)/terminate.c \
	$(UTILS_FILES)

INC_FILES = \
	$(INC_DIR)/get_next_line.h \
	$(INC_DIR)/pipex.h \
	$(INC_DIR)/utils.h

MANDATORY_SRCS = $(SRC_FILES) $(SRC_DIR)/main.c
BONUS_SRCS = $(SRC_FILES) $(SRC_DIR)/main_bonus.c $(SRC_DIR)/heredoc.c

MANDATORY_OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(MANDATORY_SRCS))
BONUS_OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

all: $(NAME_MANDATORY) $(NAME_BONUS)

bonus: $(NAME_BONUS)

$(NAME_MANDATORY): $(INC_FILES) $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MANDATORY_OBJS)
	ln -sf $(NAME_MANDATORY) $(NAME)

$(NAME_BONUS): $(INC_FILES) $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJS)
	ln -sf $(NAME_BONUS) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -v -p $(OBJ_DIR)
	@mkdir -v -p $(OBJ_DIR)/utils

clean:
	@rm -v -rf $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -v -rf $(NAME) $(NAME_MANDATORY) $(NAME_BONUS)

re: fclean all
