encode: main.o 
	g++ -o encode main.o

main.o: 
	g++ -Wall -c main.cpp

clean:
	rm *.o dna