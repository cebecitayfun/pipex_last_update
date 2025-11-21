# --- Değişkenler ---
NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Kaynak Dosyalar
SRCS		= pipex.c pipex_utils.c
OBJS		= $(SRCS:.c=.o)

# Libft Yolları
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# --- Kurallar ---

# 1. Ana Hedef
all: $(NAME)

# 2. Libft'i Derle
# make -C komutu, "./libft" klasörüne girip oradaki Makefile'ı çalıştırır.
$(LIBFT):
	make -C $(LIBFT_DIR)

# 3. Pipex'i Derle ve Bağla
# Önce $(OBJS) ve $(LIBFT) hazır olmalı.
# Sonra hepsini birleştirip $(NAME) oluşturur.
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# 4. Temizlik Kuralları
clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

# Sahte Hedefler (Dosya adı zannedilmesin diye)
.PHONY: all clean fclean re