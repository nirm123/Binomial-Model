Binomial: Binomial.o
	g++ -g -o Binomial Binomial.o

Binomial.o: Binomial.cpp
	g++ -g -c Binomial.cpp

clean:
	rm -f Binomial Binomial.o
