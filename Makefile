CFLAGS	:= -O2 -Wall


source	:= main.c network.c

all: scratch_rsp

scratch_rsp:	 main.o network.o
	gcc $(LDFLAGS) $^ -o $@

main.o:	main.c rsp.h
	gcc $(CFLAGS) -c $^ -o $@ 
	
network.o: network.c
	gcc $(CFLAGS) -c $^ -o $@ 
