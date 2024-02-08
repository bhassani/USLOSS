#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QUANTUM 5
#define TIME_SLICE 1

// Define a structure to represent a process
typedef struct Process {
    int pid;             // Process ID
    char name[20];       // Process name
    int priority;        // Process priority
    int remainingTime;   // Remaining CPU time
    struct Process* next; // Pointer to the next process in the linked list
} Process;

// Function to create a new process
Process* createProcess(int pid, const char* name, int priority, int cpuTime) {
    Process* newProcess = (Process*)malloc(sizeof(Process));
    if (newProcess != NULL) {
        newProcess->pid = pid;
        snprintf(newProcess->name, sizeof(newProcess->name), "%s", name);
        newProcess->priority = priority;
        newProcess->remainingTime = cpuTime;
        newProcess->next = NULL;
    }
    return newProcess;
}

// Function to insert a process into the linked list according to priority
void insertProcess(Process** head, Process* newProcess) {
    if (*head == NULL || (*head)->priority < newProcess->priority) {
        newProcess->next = *head;
        *head = newProcess;
    } else {
        Process* current = *head;
        while (current->next != NULL && current->next->priority >= newProcess->priority) {
            current = current->next;
        }
        newProcess->next = current->next;
        current->next = newProcess;
    }
}

// Function to remove and return the process with the highest priority from the linked list
Process* removeHighestPriorityProcess(Process** head) {
    if (*head == NULL) {
        return NULL;
    }
    Process* removedProcess = *head;
    *head = (*head)->next;
    removedProcess->next = NULL;
    return removedProcess;
}

// Function to simulate running a process for a quantum
void runProcess(Process* process) {
    printf("Running process: PID=%d, Name=%s, Priority=%d\n", process->pid, process->name, process->priority);
    // Simulate running the process for a quantum
    process->remainingTime -= QUANTUM;
    if (process->remainingTime <= 0) {
        printf("Process PID=%d finished execution.\n", process->pid);
        free(process); // Free the memory allocated for the process
    } else {
        // Reinsert the process into the linked list based on priority
        insertProcess(&process, process);
    }
}

/*
called whenever a clock interrupt occurs. This function decrements the remaining time of the currently running process by a fixed time slice (TIME_SLICE).

If the remaining time of the process becomes zero or less, indicating that the process has completed its execution, it is removed from the linked list.

*/
// Clock interrupt handler
void clockInterruptHandler(Process** head) {
    printf("Clock interrupt occurred.\n");
    // Decrement remaining time for the currently running process
    if (*head != NULL) {
        (*head)->remainingTime -= TIME_SLICE;
        if ((*head)->remainingTime <= 0) {
            // If the process has completed its execution, remove it
            printf("Process PID=%d finished execution.\n", (*head)->pid);
            free(*head);
            *head = NULL;
        }
    }
}

int main() {
    Process* head = NULL;

    // Example usage: Creating and inserting processes
    insertProcess(&head, createProcess(1, "Process1", 2, 20));
    insertProcess(&head, createProcess(2, "Process2", 1, 30));
    insertProcess(&head, createProcess(3, "Process3", 3, 15));

    // Simulate clock interrupts
    while (head != NULL) {
        // Simulate clock interrupt occurring
        clockInterruptHandler(&head);
        // Run the process for a quantum
        if (head != NULL) {
            runProcess(head);
        }
        // Sleep to simulate the passage of time
        sleep(1);
    }

    return 0;
}
