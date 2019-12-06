# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/06 01:39:55 by trobicho          #+#    #+#              #
#    Updated: 2019/12/06 03:02:05 by trobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			=	g++
CXXFLAGS	=	-std=c++14 -g #-Wall -Wextra
NAME		=	space_colonisation2d

SRCS_PATH	=	./
HDRS_PATH	=	./
OBJS_PATH	=	./obj

SDL_LOC		=	$(HOME)/.brew/Cellar/sdl2/2.0.10
SDL_LFLAGS	=	-L $(SDL_LOC)/lib -lSDL2
SDL_IFLAGS	=	-I $(HDRS_PATH) -I $(SDL_LOC)/include/SDL2 -I $(SDL_LOC)/include

ifeq ($(UNAME), Linux)
	INCS_FLAGS	= -I../my_lib_cpp/ -I$(GLM_PATH)/include -I $(INCLUDE_PATH)
	LIBS_FLAGS = -lm -L ../my_lib_cpp/ -ltrl
else
	INCS_FLAGS	= -I../QGen/my_lib_cpp/ -I$(GLM_PATH)/include -I $(INCLUDE_PATH)
	LIBS_FLAGS = `pkg-config --static --libs glm` -lm -L ../QGen/my_lib_cpp/ -ltrl
endif

SRCS_NAME	=	main.cpp \
				Renderer.cpp \
				Space_colonisation.cpp

HDRS_NAME	=	Renderer.h \
				Space_colonisation.h

OBJS_NAME	=	$(SRCS_NAME:.cpp=.o)

SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
HDRS = $(addprefix $(HDRS_PATH)/, $(HDRS_NAME))
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))

all: $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(CXXFLAGS) $(INCS_FLAGS) $(SDL_IFLAGS) $(OBJS) $(LIBS_FLAGS) $(SDL_LFLAGS) -o $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.cpp $(HDRS) Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[38;2;0;255;0m[cc]\033[0m: $< -> $@"
	@printf "\e[1A"
	@$(CC) $(CXXFLAGS) -I $(HDRS_PATH) $(INCS_FLAGS) $(SDL_IFLAGS) -c $< -o $@
	@printf "\e[0K"

clean:
	rm -f $(OBJS) $(GEN_OBJS) $(ENV_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re logo test
