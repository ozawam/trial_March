collision: calc_force.o leap_frog.o collision.o
	g++ -Wall -o -g collision calc_force.o leap_frog.o collision.o

calc_force.o: calc_force.cc
	g++ -Wall -c calc_force.cc

leap_frog.o: leap_frog.cc
	g++ -Wall -c leap_frog.cc

collision.o: collision.cc
	g++ -Wall -c collision.cc

clean:
	rm -f *.o collision
