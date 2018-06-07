a.out: kolko_i_krzyzyk.o main.o
	g++ -Wall -pedantic kolko_i_krzyzyk.o main.o

kolko_i_krzyzyk.o: kolko_i_krzyzyk.cpp kolko_i_krzyzyk.hh
	g++ -Wall -pedantic kolko_i_krzyzyk.hh
	g++ -Wall -pedantic -c kolko_i_krzyzyk.cpp

main.o: main.cpp
	g++ -Wall -pedantic -c main.cpp

clear:
	rm *.o
