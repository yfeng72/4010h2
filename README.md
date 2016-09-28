# Authors

Yu Feng, Julian Rosker

# Compilation and Run Instructions

To Compile Simulation: gcc -std=c99 -o Simulation simulation.c fifoQueue.c Node.c priorityQueue.c RNG.c -lm
To Compile Priority Queue Performance Benchmark: gcc -std=c99 -o Benchmark benchmark.c priorityQueue.c Node.c RNG.c -lm

To Run Simulation with 3 stations (default): ./Simulation
To Run Simulation with a single station: ./Simulation -singleStation

To Run Benchmark of Priority Queue Insertion/Deletion Performance: ./Benchmark

# Files

## Discrete Event Simulator

### simulation.c:

Implemented by Yu Feng
Main executable of the Discrete Event Simulator, details see documentations inside this file

## Priority Queue Run Time Benchmark

Implemented by Yu Feng
benchmark.c: Main executable of the Priority Queue Benchmark, details see documentations inside this file

## Libraries

### RNG.h/.c:

Implemented by Julian Rosker
Library for Uniform and Exponential RNGs, details see RNG.h documentations

### Node.h/.c:

Implemented by Yu Feng and Julian Rosker
Library for Event Node and Entity Node used in Queues, details see Node.h documentations

### fifoQueue.h/.c:

Implemented by Yu Feng and Julian Rosker
Library for FIFO Queue used in stations of Discrete Event Simulators, details see fifoQueue.h documentations

### priorityQueue.h/.c:

Implemented by Julian Rosker
Library for Priority Queue used in Future Event Lists of Discrete Event Simulators, details see priorityQueue.h documentations

## Outputs

Output files for the simulations and benchmarks ran on the jinx cluster

### output.csv/.xlsx:

Output file for the 3-station simulation. output.xlsx contains a graph comparing simulated results with theoretical ones.

### singleStation.csv/.xlsx:

Output file for the 1-station simulation. singleStation.xlsx contains a graph comparing simulated results with theoretical ones.

### benchmark.csv/.xlsx:

Output file for the insertion/deletion performance benchmark on the priority queue. benchmark.xlsx has the fitted line with regression equation and R-square statistics.