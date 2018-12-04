all: driver.o func.o
	gcc driver.o func.o

driver.o: driver.c func.h
	gcc -c driver.c func.h

func.o: func.c func.h
	gcc -c func.c func.h

run:
	./a.out

test:
	echo NORMAL TEST
	ls
	ls -a -l
	echo CD TEST
	cd ..
	pwd
	echo SEMICOLON TEST
	ps ; echo HELLO
	echo STDOUT REDIRECT TEST
	w > wholist
	cat wholist
	echo STDIN REDIRECT TEST
	tr a-z A-Z < wholist
	echo DOUBLE REDIRECT TEST
	tr a-z A-Z < wholist > foo
	cat foo
	echo PIPE TEST
	ls | wc
	rm wholist foo
	echo EXIT
	exit
