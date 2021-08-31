CC = clang++
#CC = g++
INC = graph.h priorityQueue.h mst.h

all: msTree

msTree: main.o graph.o priorityQueue.o mst.o
	${CC} main.o graph.o priorityQueue.o mst.o -o msTree

main.o: $(INC) main.cpp
	${CC} -c main.cpp

graph.o: graph.h graph.cpp
	${CC} -c graph.cpp

priorityQueue.o: priorityQueue.h priorityQueue.cpp
		${CC} -c priorityQueue.cpp

mst.o: $(INC) mst.cpp
	${CC} -c mst.cpp

clean:
	rm msTree *.o
