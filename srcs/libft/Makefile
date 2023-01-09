
SRCS_L				=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
						ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
						ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
						ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \

SRCS_P				=	args.c bonus_conditions.c bonus_func.c bonus_utils.c conditions.c ft_printf.c main_file.c pass_index.c print.c utils.c 

SRCS_G				=	get_next_line.c get_next_line_utils.c

L_DIR				=	./vanilla

P_DIR				=	./ft_printf

G_DIR				=	./gnl

SRCS_FILES			=	$(addprefix $(P_DIR)/,$(SRCS_P)) $(addprefix $(G_DIR)/,$(SRCS_G)) $(addprefix $(L_DIR)/,$(SRCS_L))

INC					=	./include

OBJS_DIR			=	./objs

OBJS				=	 $(addprefix $(OBJS_DIR)/,$(SRCS_P:%.c=%.o)) $(addprefix $(OBJS_DIR)/,$(SRCS_G:%.c=%.o)) $(addprefix $(OBJS_DIR)/,$(SRCS_L:%.c=%.o))

LIB_NAME			=	libft.a

CC					=	gcc

CFLAGS				=	-Wall -Wextra -Werror -g3

RM					=	rm -f

all					:		${LIB_NAME}

$(OBJS_DIR)/%.o		:		$(P_DIR)/%.c
						@mkdir -p ${OBJS_DIR}
						${CC} ${CFLAGS} -I$(INC) -c $< -o $@

$(OBJS_DIR)/%.o		:		$(G_DIR)/%.c
						@mkdir -p ${OBJS_DIR}
						${CC} ${CFLAGS} -I$(INC) -c $< -o $@

$(OBJS_DIR)/%.o		:		$(L_DIR)/%.c
						@mkdir -p ${OBJS_DIR}
						${CC} ${CFLAGS} -I$(INC) -c $< -o $@

${LIB_NAME}			:		${OBJS}	
						ar rcs ${LIB_NAME} ${OBJS}

norm				:
						@norminette $(SRCS_FILES)
						@norminette $(INC)

clean				:
						${RM} ${OBJS}

fclean				:		clean
						${RM} ${LIB_NAME}

re					:		fclean all

.PHONY				:		all clean fclean re
