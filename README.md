# CPU Scheduling Algorithms Project

## Project Overview
This project simulates various CPU scheduling algorithms using the C programming language. CPU scheduling is an essential part of process management in an operating system, and these algorithms determine how processes are assigned to the CPU for execution.

### Algorithms Implemented:
1. **First-Come, First-Served (FCFS)**
   - Non-preemptive scheduling algorithm.
   - Processes are executed in the order they arrive in the queue.
   - Simple but can cause the "convoy effect" where short jobs are delayed by longer ones.

2. **Shortest Job First (SJF)**
   - Non-preemptive scheduling algorithm.
   - Processes with the shortest burst time are executed first.
   - Minimizes the average waiting time but requires accurate knowledge of burst times.

3. **Longest Job First (LJF)**
   - Non-preemptive scheduling algorithm.
   - Processes with the longest burst time are given priority.
   - Results in longer waiting times for short processes.

4. **Round Robin (RR)**
   - Preemptive scheduling algorithm.
   - Each process is assigned a fixed time slot (time quantum).
   - After its time quantum, the process is moved to the end of the queue if it’s not completed.
   - Fair for all processes and suitable for time-sharing systems.

---

## Language Used:
- **C Programming Language**

---

## How to Run the Project:
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/CPU-Scheduling.git
