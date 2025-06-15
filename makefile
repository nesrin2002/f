# makefile
myshell: myshell.o utility.o
gcc myshell.o utility.o -o myshell

myshell.o: myshell.c myshell.h
gcc -c myshell.c

utility.o: utility.c myshell.h
gcc -c utility.c

clean:
rm -f *.o myshell

