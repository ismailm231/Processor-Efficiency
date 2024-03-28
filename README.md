### Job Processing Simulation

This C++ project simulates a job processing system using object-oriented programming (OOP) principles. It generates 10,000 jobs with different priorities and processes them through a series of queues and processors. The simulation aims to determine the most efficient configuration for processing jobs.

#### Features:

- **Job Generation**: 10,000 jobs are created with varying priorities.
- **Queues and Processors**: Jobs are organized into queues and processed by a configurable number of processors (1 to 8).
- **Efficiency Testing**: The simulation tests different configurations of processors to determine the most efficient setup.
- **Metrics Calculation**: Metrics such as average queue times and number of completed jobs are calculated and logged to a `log.txt` file for further analysis.

#### How to Run:

1. Clone the repository to your local machine.
2. Compile the `main.cpp` file using a C++ compiler.
3. Run the compiled executable.
4. The simulation will run and output results to the console.
5. Metrics and results will also be logged to a `log.txt` file in the project directory for further analysis.

#### Requirements:

- C++ compiler

#### Usage:

```bash
$ g++ main.cpp -o job_simulation
$ ./job_simulation
```

#### Log File:

- The `log.txt` file contains detailed metrics and results from the simulation.
- It provides insights into the performance of different processor configurations and job processing efficiency.



