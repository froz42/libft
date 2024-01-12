NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror -fPIE

ifneq ($(filter debug redebug unit,$(MAKECMDGOALS)),)
	CFLAGS += -g
endif

# Directories
SRCSDIR := srcs
OBJSDIR_RELEASE := .build/release
OBJSDIR_DEBUG := .build/debug
INCDIR := includes

# string files
SRCS +=	string/ft_strlen.c \
		string/ft_strnlen.c \
		string/ft_strcmp.c \
		string/ft_strncmp.c \
		string/ft_memcpy.c \
		string/ft_memmove.c \
		string/ft_atoi.c \
		string/ft_strlcpy.c \
		string/ft_strchr.c \
		string/ft_strpbrk.c \
		string/ft_strspn.c \
		string/ft_strtok.c \
		string/ft_strdup.c \
		string/ft_memcmp.c \
		string/ft_strerror.c \
		string/ft_escape.c \
		string/ft_errnoname.c \
		string/ft_signalname.c \
		string/ft_sicodename.c

# char files

SRCS += char/ft_isdigit.c \
		char/ft_isalpha.c \
		char/ft_isupper.c \
		char/ft_islower.c \
		char/ft_tolower.c \
		char/ft_isalnum.c \
		char/ft_isprint.c

# gnl files

SRCS += gnl/ft_gnl.c

# printf family files
SRCS +=	printf/buffer/buffer_printf.c \
		printf/parse_format/parse_format.c \
		printf/parse_format/conversions/int_conversion.c \
		printf/parse_format/conversions/float_conversion.c \
		printf/parse_format/conversions/uint_conversion.c \
		printf/parse_format/conversions/octal_conversion.c \
		printf/parse_format/conversions/hex_conversion.c \
		printf/parse_format/conversions/char_conversion.c \
		printf/parse_format/conversions/str_conversion.c \
		printf/parse_format/conversions/ptr_conversion.c \
		printf/utils/int_to_array_base.c \
		printf/utils/uint_to_array_base.c \
		printf/utils/float_to_array.c \
		printf/utils/paddings.c \
		printf/ft_printf.c

# unit test files

SRCS += units/units.c \
		units/record_output.c

# rbtree files

SRCS += rbtree/ft_rbtree_new.c \
		rbtree/ft_rbtree_insert.c \
		rbtree/ft_rbtree_search.c \
		rbtree/ft_rbtree_destroy.c \
		rbtree/ft_rbtree_delete.c \
		rbtree/ft_rbtree_foreach.c

# misc files

SRCS += misc/ft_calloc.c

OBJS_RELEASE := $(addprefix $(OBJSDIR_RELEASE)/,$(SRCS:.c=.o))
OBJS_DEBUG := $(addprefix $(OBJSDIR_DEBUG)/,$(SRCS:.c=.o))

DEPS_RELEASE := $(addprefix $(OBJSDIR_RELEASE)/,$(SRCS:.c=.d))
DEPS_DEBUG := $(addprefix $(OBJSDIR_DEBUG)/,$(SRCS:.c=.d))

DFLAGS	= -MMD -MF $(@:.o=.d)

NAME_DEBUG := libftdebug.a
# Rules

all: $(NAME)

$(NAME): $(OBJS_RELEASE)
	ar -rcs $(NAME) $(OBJS_RELEASE)

debug: $(NAME_DEBUG)

$(NAME_DEBUG): $(OBJS_DEBUG)
	ar -rcs $(NAME_DEBUG) $(OBJS_DEBUG)

-include $(DEPS_RELEASE)
$(OBJSDIR_RELEASE)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCDIR) $(DFLAGS) -c $< -o $@

-include $(DEPS_DEBUG)
$(OBJSDIR_DEBUG)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCDIR) $(DFLAGS) -c $< -o $@

unit: $(OBJS_DEBUG)
	@LIBFT_TEST=true scripts/car.sh $(OBJS_DEBUG)

clean:
	rm -rf .build

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean all

.PHONY: all clean fclean re debug unit