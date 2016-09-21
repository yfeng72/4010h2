# Authors

Yu Feng, Julian Rosker

# Compilation and Run Instructions

To Compile: gcc -std=c99 -o sim.o simulation.c fifoQueue.c Node.c priorityQueue.c RNG.c -lm
To Run: ./sim.o
To Run Simulation with a single station: ./sim.o -singleStation

# Files

## Discrete Event Simulator

simulation.c: Main executable of the Discrete Event Simulator

## Libraries

RNG.h/.c: Library for Uniform and Exponential RNGs, details see RNG.h documentations

Node.h/.c: Library for Event Node and Entity Node used in Queues, details see Node.h documentations

fifoQueue.h/.c: Library for FIFO Queue used in stations of Discrete Event Simulators, details see fifoQueue.h documentations

priorityQueue.h/.c: Library for Priority Queue used in Future Event Lists of Discrete Event Simulators, details see priorityQueue.h documentations
