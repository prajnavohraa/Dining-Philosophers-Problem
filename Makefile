all: d_1a d_1b d_2a d_2b

d_1a: d_1a.c
	gcc -o d_1a d_1a.c

d_1b: d_1b.c
	gcc -o d_1b d_1b.c

d_2a: d_2a.c
	gcc -o d_2a d_2a.c

d_2b: d_2b.c
	gcc -o d_2b d_2b.c
