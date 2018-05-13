all: mypipeline

mypipeline:  main.o
	gcc -g -Wall -o mypipeline main.o

	
main.o: main.c
	gcc -g -Wall -c -o main.o main.c

clean:
	rm -f *.o
 
