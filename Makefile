NAME						=	minishell

SRCS_DIR					=	./srcs

MANDATORY_DIR				=	${SRCS_DIR}/mandatory

BONUS_DIR					=	${SRCS_DIR}/bonus

COMMON_SRCS					=	history.c \
								redirect.c \
								redirect_utils.c \
								exit.c \
								echo.c \
								quotes.c \
								path.c \
								env.c \
								init.c \
								print.c \
								signals.c \
								split.c \
								commands.c \
								pipex.c \
								input.c \
								manage_input.c \
								pipex_utils.c \
								env_utils.c \
								input_utils.c

MANDATORY_SRCS				=	${COMMON_SRCS} main.c

BONUS_SRCS					=	main.c

LIB_DIR						=	./srcs/libft

LIBFT						=	${LIB_DIR}/libft.a

INCS						=	${NAME}.h

INC_DIR						=	./includes

INC_DIRS					=	${INC_DIR} ${LIB_DIR}/include

INC_FLAG					=	${addprefix -I, ${INC_DIRS}}

INC_FILES					=	${addprefix ${INC_DIR}/, ${INCS}}

CC							=	gcc

CFLAGS						=	-Wall -Wextra -Werror -g3

OBJS_DIR					=	./objs

MANDATORY_OBJS				=	${addprefix ${OBJS_DIR}/mandatory/, ${MANDATORY_SRCS:%.c=%.o}}

BONUS_OBJS					=	${addprefix ${OBJS_DIR}/bonus/, ${BONUS_SRCS:%.c=%.o}} ${addprefix ${OBJS_DIR}/mandatory/, ${COMMON_SRCS:%.c=%.o}}

RM							=	rm -f


${OBJS_DIR}/mandatory/%.o	:		${MANDATORY_DIR}/%.c ${INC_FILES}
								@mkdir -p ${OBJS_DIR}/mandatory
								${CC} ${CFLAGS} ${INC_FLAG} -c $< -o $@

${OBJS_DIR}/bonus/%.o		:		${BONUS_DIR}/%.c ${INC_FILES}
								@mkdir -p ${OBJS_DIR}/bonus
								${CC} ${CFLAGS} ${INC_FLAG} -c $< -o $@

all							:		${NAME}

bonus						:		${NAME}_bonus

${NAME}						:		${MANDATORY_OBJS} ${LIBFT}
								${CC} ${CFLAGS} -o ${NAME} ${MANDATORY_OBJS} -L${LIB_DIR} -lft -lreadline

${NAME}_bonus				:		${BONUS_OBJS} ${LIBFT}
								${CC} ${CFLAGS} -o ${NAME}_bonus ${BONUS_OBJS} -L${LIB_DIR} -lft

${LIBFT}					:	
								make -C ${LIB_DIR}

clean						:	
								${RM} ${MANDATORY_OBJS}
								${RM} ${BONUS_OBJS}
								make -C ${LIB_DIR} clean

fclean						:		clean
								${RM} ${NAME}
								${RM} ${NAME}_bonus
								make -C ${LIB_DIR} fclean

re							:		fclean all

.PHONY						:		all fclean clean re
