CLANG=cc
# CFLAGS=-Wall -Werror -Wextra -MMD
INCL=-Iinclude -Ilibft
LDFLAGS=-Llibft -Lminilibx-linux -lft -lmlx -lXext -lX11 -lz -lm
NAME=win
SRC_DIR=src/
OBJ_DIR=obj/

SRCS += $(SRC_DIR)window.c
SRCS += $(SRC_DIR)utils.c
SRCS += $(SRC_DIR)load_map.c

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
	$(CLANG) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

-include $(DEPS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CLANG) $(CFLAGS) $(INCL) -c $< -o $@

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

