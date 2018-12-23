CC = gcc

CFLAGS = -g -Wall -Werror 

SRCS = ll_basic.c

TARGETS = ll_basic

OBJS = $(SRCS:.c=.o) 

MAIN = ll_test

all: $(MAIN)

$(MAIN): $(OBJS)	
	$(CC) -c $(SRCS)
	$(CC) -o $(MAIN) $(OBJS)
	

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

