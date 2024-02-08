#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep() function

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

// Function to remove and return the process with the specified PID from the linked list
Process* removeProcess(Process** head, int pid) {
    Process* current = *head;
    Process* prev = NULL;
    while (current != NULL && current->pid != pid) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return NULL; // Process with given PID not found
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    current->next = NULL;
    return current;
}

/*
takes the process's head pointer and the process's PID as arguments. It searches for the process with the specified PID in the linked list, removes it from the list, and frees the memory allocated for the process.
*/
// Function to zap (terminate) a process with the specified PID
void zapProcess(Process** head, int pid) {
    Process* process = removeProcess(head, pid);
    if (process != NULL) {
        printf("Zapping process: PID=%d, Name=%s\n", process->pid, process->name);
        free(process); // Free the memory allocated for the process
    } else {
        printf("Process with PID=%d not found.\n", pid);
    }
}

int main() {
    Process* head = NULL;

    // Example usage: Creating and inserting processes
    insertProcess(&head, createProcess(1, "Process1", 2, 20));
    insertProcess(&head, createProcess(2, "Process2", 1, 30));
    insertProcess(&head, createProcess(3, "Process3", 3, 15));

    // Zap process with PID 2
    zapProcess(&head, 2);

    // Simulate clock interrupts
    while (head != NULL) {
        // Run the process for a quantum
        printf("Running process: PID=%d, Name=%s\n", head->pid, head->name);
        head = head->next;
        // Sleep to simulate the passage of time
        sleep(1);
    }

    return 0;
}
