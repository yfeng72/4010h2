# Authors

Yu Feng, Julian Rosker

# Compilation and Run Instructions

To Compile Simulation: gcc -std=c99 -o sim.o simulation.c fifoQueue.c Node.c priorityQueue.c RNG.c -lm
To Compile Priority Queue Performance Benchmark: gcc -std=c99 -o bm.o benchmark.c priorityQueue.c Node.c RNG.c -lm

To Run Simulation with 3 stations (default): ./sim.o
To Run Simulation with a single station: ./sim.o -singleStation

To Run Benchmark of Priority Queue Insertion/Deletion Performance: ./bm.o

# Files

## Discrete Event Simulator

simulation.c: Main executable of the Discrete Event Simulator, details see documentations inside this file

## Priority Queue Run Time Benchmark

benchmark.c: Main executable of the Priority Queue Benchmark, details see documentations inside this file

## Libraries

RNG.h/.c: Library for Uniform and Exponential RNGs, details see RNG.h documentations

Node.h/.c: Library for Event Node and Entity Node used in Queues, details see Node.h documentations

fifoQueue.h/.c: Library for FIFO Queue used in stations of Discrete Event Simulators, details see fifoQueue.h documentations

priorityQueue.h/.c: Library for Priority Queue used in Future Event Lists of Discrete Event Simulators, details see priorityQueue.h documentations
