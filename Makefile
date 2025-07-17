CC := gcc
FLAGS := -lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
SRCS := $(wildcard *.c)
SRCS += $(wildcard glad/*.c)
OBJS := $(SRCS:.c=.o)

all: app

app: $(OBJS)
	$(CC) -o $@ $^ $(FLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm $(OBJS)
	rm ./app

#export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
#code --enable-features=UseOzonePlatform --ozone-platform=wayland
