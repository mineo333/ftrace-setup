

all:
	make ftrace_util.o

ftrace_util.o : ftrace_util.c
	gcc -o $@ -I . -c $^