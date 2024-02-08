/*

round-robin scheduling algorithm with priority scheduling using a linked list of processes in C for the USLOSS operating system

*/


#include <stdio.h>
#include <stdlib.h>

#define QUANTUM 80

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

int main() {
    Process* head = NULL;

    // Example usage: Creating and inserting processes
    insertProcess(&head, createProcess(1, "Process1", 2, 20));
    insertProcess(&head, createProcess(2, "Process2", 1, 30));
    insertProcess(&head, createProcess(3, "Process3", 3, 15));

    // Simulate round-robin with priority scheduling
    while (head != NULL) {
        Process* currentProcess = removeHighestPriorityProcess(&head);
        runProcess(currentProcess);
    }

    return 0;
}


