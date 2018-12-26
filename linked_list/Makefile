CC = gcc

CFLAGS = -g -Wall -Werror 

SRCS = ll_basic.c ll.c 

INCLUDE = -I ../linked_list ../include/common.h

OBJS = $(SRCS:.c=.o) 

MAIN = ll_test

all: $(MAIN)

$(MAIN): $(OBJS)	
	$(CC) -c $(SRCS)
	$(CC) -o $(MAIN) $(OBJS)  $(INCLUDE)
	

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

