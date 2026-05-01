*This project has been created as part of the 42 curriculum by esezalor.*

# Philosophers

## Description

Philosophers is a classic concurrency exercise. A group of philosophers sits around a table with a bowl of food. Each philosopher needs two forks to eat, but there is only one fork between each pair of neighbors. Philosophers alternate between eating, sleeping, and thinking, and they must not starve.

The goal of the project is to learn the basics of multithreading in C: creating threads, protecting shared resources with mutexes, and avoiding common pitfalls like deadlocks and race conditions. Each philosopher runs in its own thread, each fork is represented by a mutex, and a separate monitor thread watches for any philosopher who has died or for the moment when everyone has eaten enough.

## Instructions

### Compilation

Clone the repository and run `make` at the root of the project:

```
make        # builds the philo binary
make clean  # removes object and dependency files
make fclean # also removes the binary
make re     # rebuilds from scratch
```

### Execution

The program takes 4 mandatory arguments and 1 optional one, all in milliseconds (except the first and last):

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: number of philosophers and forks at the table
- `time_to_die`: if a philosopher does not start eating within this time after their last meal (or the start of the simulation), they die
- `time_to_eat`: time it takes a philosopher to eat
- `time_to_sleep`: time a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` *(optional)*: simulation stops once every philosopher has eaten at least this many times

Example:

```
./philo 5 800 200 200
./philo 4 410 200 200 5
```

### Output

Each event is logged in the format `timestamp_in_ms philosopher_id action`, for instance:

```
0 3 has taken a fork
0 3 is eating
200 3 is sleeping
400 3 is thinking
```

## Resources

- *The Linux Programming Interface* by Michael Kerrisk — chapters on threads, mutexes, and time-related system calls
- Stanford CS110, *Lecture 08: Introduction to Threads* — https://web.stanford.edu/class/archive/cs/cs110/cs110.1206/lectures/08-slides.pdf
- *Threads, Mutexes and Concurrent Programming in C* — https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/

### Use of AI

AI (Claude) was used as a study and review companion, specifically for:

- Clarifying conceptual questions about thread synchronization, mutex behavior, and how to avoid deadlocks.
- Helping draft this README.

All code in this repository was written and debugged by me; AI was not used to generate the implementation.