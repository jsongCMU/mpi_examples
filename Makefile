OUTPUTDIR := bin/

CFLAGS := -std=c++14 -fvisibility=hidden -lpthread -Wall -Wextra

ifeq (,$(CONFIGURATION))
	CONFIGURATION := release
endif

ifeq (debug,$(CONFIGURATION))
CFLAGS += -g
else
CFLAGS += -O2
endif

HEADERS := src/*.h

CXX = mpic++

.SUFFIXES:
.PHONY: all clean

all: hello_world.o basic_comms.o mpi_scatter.o mpi_gather.o mpi_allgather.o mpi_allgatherv.o mpi_bcast.o vector_test.o

hello_world.o: hello_world.cpp
	$(CXX) -o $@ $(CFLAGS) hello_world.cpp

basic_comms.o: basic_comms.cpp
	$(CXX) -o $@ $(CFLAGS) basic_comms.cpp

mpi_scatter.o: mpi_scatter.cpp
	$(CXX) -o $@ $(CFLAGS) mpi_scatter.cpp

mpi_gather.o: mpi_gather.cpp
	$(CXX) -o $@ $(CFLAGS) mpi_gather.cpp

mpi_allgather.o: mpi_allgather.cpp
	$(CXX) -o $@ $(CFLAGS) mpi_allgather.cpp

mpi_allgatherv.o: mpi_allgatherv.cpp
	$(CXX) -o $@ $(CFLAGS) mpi_allgatherv.cpp

mpi_bcast.o: mpi_bcast.cpp
	$(CXX) -o $@ $(CFLAGS) mpi_bcast.cpp

vector_test.o: vector_test.cpp
	$(CXX) -o $@ $(CFLAGS) vector_test.cpp

clean:
	rm *.o
