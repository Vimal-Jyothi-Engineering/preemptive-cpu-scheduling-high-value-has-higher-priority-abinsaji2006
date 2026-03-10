[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/BgqfLQuW)
# Preemptive Priority CPU Scheduling (C)

## Objective

Implement **Preemptive Priority CPU Scheduling** in C.

In this scheduling algorithm, the process with the **highest priority is executed first**.
If a new process arrives with **higher priority than the currently running process**, the CPU is **preempted** and assigned to the new process.

**Note:** Higher numeric value means **higher priority**.

---

## Input Format

```
n
PID1 AT1 BT1 PR1
PID2 AT2 BT2 PR2
...
PIDn ATn BTn PRn
```

Where:

* `n` – Number of processes
* `PID` – Process ID
* `AT` – Arrival Time
* `BT` – Burst Time
* `PR` – Priority (higher value = higher priority)

---

## Output Format

```
Waiting Time:
PID WT
...

Turnaround Time:
PID TAT
...

Average Waiting Time: X.XX
Average Turnaround Time: X.XX
```

---

## Example

### Sample Input

```
5
P1 0 5 2
P2 1 3 4
P3 2 4 1
P4 3 2 3
P5 4 6 5
```

### Sample Output

```
Waiting Time:
P1 5
P2 6
P3 14
P4 8
P5 0

Turnaround Time:
P1 14
P2 9
P3 18
P4 10
P5 6

Average Waiting Time: 7.40
Average Turnaround Time: 11.40
```

---

## Files Provided

```
priority.c        → Program file to implement
run.sh            → Script to compile and run the program
tests/            → Input and expected output test cases
.github/workflows → GitHub Actions autograding workflow
```

---

## How Autograding Works

When you push your solution:

1. GitHub Actions compiles your program.
2. The program runs on **5 test cases**.
3. Output is compared with expected results using `diff`.
4. If outputs match, the test case passes.

---

## Compilation

You can test locally using:

```
gcc priority.c -o priority
./priority
```

or

```
bash run.sh
```

---

## Submission Instructions

1. Implement the solution in **priority.c**.
2. Do not change file names.
3. Push your code to the repository.
4. GitHub Actions will automatically run the tests.

---

## Evaluation

| Test Cases   | Marks |
| ------------ | ----- |
| 5 Test Cases | 100   |

Each test case contributes equally to the final score.

---

## Academic Integrity

* Work on the assignment individually.
* Do not copy code from other students.
* Plagiarism detection may be used.
