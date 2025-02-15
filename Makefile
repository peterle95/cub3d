# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 12:57:19 by pmolzer           #+#    #+#              #
#    Updated: 2025/02/15 15:31:11 by pmolzer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -lXfixes not allowed by subject but only fix to mouse hide memory issues
CLANG=cc
CFLAGS=-Wall -Werror -Wextra -MMD -g
INCL=-Iinclude -Ilibft
LIBFLAGS=-Llibft -Lminilibx-linux -lft -lmlx -lXext -lX11 -lz -lm -lXfixes
PFLAGS=-D DEBUG=1
NAME=cub3d
SRC_DIR=src/
OBJ_DIR=obj/

SRCS += $(SRC_DIR)debug.c
SRCS += $(SRC_DIR)main.c
SRCS += $(SRC_DIR)utils.c
SRCS += $(SRC_DIR)utils2.c
SRCS += $(SRC_DIR)utils3.c
SRCS += $(SRC_DIR)load_map.c
SRCS += $(SRC_DIR)map_validation.c
SRCS += $(SRC_DIR)map_validation_utils.c
SRCS += $(SRC_DIR)map_validation_utils2.c
SRCS += $(SRC_DIR)map_validation_utils3.c
SRCS += $(SRC_DIR)map_validation_utils4.c
SRCS += $(SRC_DIR)error_msg.c
SRCS += $(SRC_DIR)get_next_line.c
SRCS += $(SRC_DIR)get_next_line_utils.c
SRCS += $(SRC_DIR)load_map_utils.c
SRCS += $(SRC_DIR)load_map_utils2.c
SRCS += $(SRC_DIR)load_map_utils3.c
SRCS += $(SRC_DIR)load_map_utils4.c
SRCS += $(SRC_DIR)load_map_utils5.c
SRCS += $(SRC_DIR)load_map_utils6.c
SRCS += $(SRC_DIR)load_map_utils7.c
SRCS += $(SRC_DIR)free_data.c
SRCS += $(SRC_DIR)graphics_image.c
SRCS += $(SRC_DIR)graphics_lines.c
SRCS += $(SRC_DIR)graphics_grid.c
SRCS += $(SRC_DIR)keyboard_input.c
SRCS += $(SRC_DIR)mouse_input.c
SRCS += $(SRC_DIR)player_movement.c
SRCS += $(SRC_DIR)raycasting.c
SRCS += $(SRC_DIR)raycasting_utils.c
SRCS += $(SRC_DIR)raycasting_utils2.c
SRCS += $(SRC_DIR)raycasting_utils3.c
SRCS += $(SRC_DIR)raycasting_utils4.c
SRCS += $(SRC_DIR)raycasting_visualisation.c
SRCS += $(SRC_DIR)draw.c
SRCS += $(SRC_DIR)draw_utils.c
SRCS += $(SRC_DIR)initialization.c

LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
MINILIBX_DIR=minilibx-linux
MINILIBX=$(MINILIBX_DIR)/libmlx_Linux.a

OBJS=$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPS=$(OBJS:.o=.d)

all: $(OBJ_DIR) $(NAME)

$(LIBFT):
		$(MAKE) -C $(dir $@)

$(MINILIBX):
		$(MAKE) -C $(dir $@)

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CLANG) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

-include $(DEPS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CLANG) $(CFLAGS) $(PFLAGS) $(INCL) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJS) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(MINILIBX)

re: fclean all

.PHONY: all clean fclean re
