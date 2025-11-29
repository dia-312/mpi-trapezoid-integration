CC=mpic++
CFLAGS=-O3 -Wall

OBJ=integrate.o func.o mpi_integrate_v1.o mpi_integrate_v2.o mpi_integrate_v3.o

all: integrate mpi_integrate_v1 mpi_integrate_v2 mpi_integrate_v3

integrate: integrate.cpp func.cpp
	g++ -O3 -Wall -o $@ integrate.cpp func.cpp

mpi_integrate_v1: mpi_integrate_v1.cpp func.cpp
	$(CC) -O3 -Wall -o $@ mpi_integrate_v1.cpp func.cpp

mpi_integrate_v2: mpi_integrate_v2.cpp func.cpp
	$(CC) -O3 -Wall -o $@ mpi_integrate_v2.cpp func.cpp

mpi_integrate_v3: mpi_integrate_v3.cpp func.cpp
	$(CC) -O3 -Wall -o $@ mpi_integrate_v3.cpp func.cpp

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

test1: integrate
	./integrate 1 4 100

test2: mpi_integrate_v1
	mpirun -np 4 ./mpi_integrate_v1 1 4 100

test3: mpi_integrate_v2
	mpirun -np 4 ./mpi_integrate_v2 1 4 100

test4: mpi_integrate_v3
	mpirun -np 4 ./mpi_integrate_v3 1 4 100

clean:
	rm -f *.o *~ core integrate mpi_integrate_v1 mpi_integrate_v2 mpi_integrate_v3
