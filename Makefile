# ---------- #
# Debug mode #
# ---------- #

DEBUG = no

# --------- #
# Directory #
# --------- #

LIBDIR = libft/
PATHLIBDIR = libft/
SRCDIR = srcs/
OBJDIR = objs/
INCDIR = include/
INCLIBDIR = libft

VPATH = srcs:\
		srcs/prompt:\
		srcs/prompt/edition:\
		srcs/prompt/history:\
		srcs/prompt/multiline:\
		srcs/prompt/others:\
		srcs/prompt/selection:\

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = gcc
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -g3
else
	CFLAGS = -Wall -Wextra -g3 -fsanitize=address
endif
CPPFLAGS = -I $(INCDIR) -I $(INCLIBDIR)
LDLIBS = -lft
LDFLAGS = -L $(PATHLIBDIR)
LFLAGS = -lncurses

# --------------- #
# Different names #
# --------------- #

NAME = minishell

SRCS_NAMES = main.c \
			 cursortools.c \
			 dlist.c \
			 dlist_plus.c \
			 editiontools.c \
			 editline.c \
			 history.c \
			 prompt.c \
			 keyhook.c \
			 morekeyhook.c \
			 del_keyhook.c \
			 othertools.c \
			 stalkcursor.c \
			 terminit.c \
			 multiline.c \
			 text_selection.c \
			 copy_paste.c \
			 undo_selection.c \
			 delete_selection.c \
			 builtins.c \
			 env.c \
			 exec.c \
			 expand.c \
			 get_next_line.c \
			 parser.c \
			 utils.c


OBJS_NAMES = $(SRCS_NAMES:.c=.o)
HEADERS_NAMES = sh21.h minishell.h
LIBS_NAMES = libft.a

OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))
LIBS = $(addprefix $(PATHLIBDIR), $(LIBS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = printf
PHONY = all clean cleans fclean re libs cleanlibs fcleanlibs lldb norm help
REMOVE = "\r\033[K"
FUNC = "%-60b\r"

# PROGRESS BAR | Original author Cpirlot
T = $(words $(OBJ))
N = 0
C = $(words $N)$(eval N := x $N)
ECHO = "[`expr $C  '*' 100 / $T`%]"

# ----- #
# Rules #
# ----- #

all : libs $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) "Debug mode : on\n"
else
	@$(PRINT) "Debug mode : off\n"
endif

$(NAME) : $(LIBS) $(OBJS_NAMES)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS) $(LFLAGS) $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) $(REMOVE)"Executable built\n"

libs :
	@$(MAKE) -j3 -C $(LIBDIR)

%.o : %.c $(HEADER)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)

clean : cleanlibs
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

cleans :
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

fclean : cleans fcleanlibs
	@$(DEL) $(NAME)
	@$(PRINT) "Executable destroyed\n"

cleanlibs :
	@$(MAKE) -C $(LIBDIR) clean

fcleanlibs :
	@$(MAKE) -C $(LIBDIR) fclean

lldb :
	@lldb ./$(NAME)

norm :
	@norminette ./$(NAME)

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, cleans, fclean, re, libs, cleanlibs, fcleanlibs, lldb, norm and help\n"

.PHONY : $(PHONY)

