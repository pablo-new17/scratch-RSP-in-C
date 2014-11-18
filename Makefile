CFLAGS	:= -O2 -Wall


source	:= main.c

all: scratch_rsp

scratch_rsp:	main.o
	gcc $(LDFLAGS) $^ -o $@

main.o:	main.c
	gcc $(CFLAGS) -c $^ -o $@ 

