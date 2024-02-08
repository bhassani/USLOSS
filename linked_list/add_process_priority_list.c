#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a process
typedef struct Process {
    int pid;             // Process ID
    char name[20];       // Process name
    int priority;        // Process priority
    struct Process* next; // Pointer to the next process in the linked list
} Process;

// Function to create a new process
Process* createProcess(int pid, const char* name, int priority) {
    Process* newProcess = (Process*)malloc(sizeof(Process));
    if (newProcess != NULL) {
        newProcess->pid = pid;
        snprintf(newProcess->name, sizeof(newProcess->name), "%s", name);
        newProcess->priority = priority;
        newProcess->next = NULL;
    }
    return newProcess;
}

// Function to insert a process into the linked list according to priority
void insertByPriority(Process** head, Process* newProcess) {
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

// Function to display the process list
void displayList(Process* head) {
    Process* current = head;
    while (current != NULL) {
        printf("PID: %d, Name: %s, Priority: %d\n", current->pid, current->name, current->priority);
        current = current->next;
    }
}

int main() {
    // Initialize the process list
    Process* head = NULL;

    // Create processes and insert them based on priority
    Process* process1 = createProcess(1, "Process1", 2);
    Process* process2 = createProcess(2, "Process2", 1);
    Process* process3 = createProcess(3, "Process3", 3);

    insertByPriority(&head, process1);
    insertByPriority(&head, process2);
    insertByPriority(&head, process3);

    // Display the process list
    printf("Process List:\n");
    displayList(head);

    // Free allocated memory
    free(process1);
    free(process2);
    free(process3);

    return 0;
}
