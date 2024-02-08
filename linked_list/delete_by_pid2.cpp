#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a process
typedef struct Process {
    int pid;             // Process ID
    char name[20];       // Process name
    struct Process* next; // Pointer to the next process in the linked list
} Process;

// Function to create a new process
Process* createProcess(int pid, const char* name) {
    Process* newProcess = (Process*)malloc(sizeof(Process));
    if (newProcess != NULL) {
        newProcess->pid = pid;
        snprintf(newProcess->name, sizeof(newProcess->name), "%s", name);
        newProcess->next = NULL;
    }
    return newProcess;
}

// Function to insert a process at the front of the linked list
void insertFront(Process** head, Process* newProcess) {
    if (*head == NULL) {
        *head = newProcess; // If list is empty, make the new process the head
    } else {
        newProcess->next = *head;
        *head = newProcess;
    }
}

// Function to delete a process from the linked list by process ID
void deleteByPID(Process** head, int pid) {
    if (*head == NULL) {
        return; // Empty list, nothing to delete
    }
    if ((*head)->pid == pid) {
        Process* temp = *head;
        *head = (*head)->next;
        free(temp); // Free memory of the deleted node
        return;
    }
    Process* current = *head;
    Process* prev = NULL;
    while (current != NULL && current->pid != pid) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return; // Process with given PID not found
    }
    prev->next = current->next;
    free(current); // Free memory of the deleted node
}

// Function to display the process list
void displayList(Process* head) {
    Process* current = head;
    while (current != NULL) {
        printf("PID: %d, Name: %s\n", current->pid, current->name);
        current = current->next;
    }
}

int main() {
    // Initialize the process list
    Process* head = NULL;

    // Create processes and insert them at the front of the list
    Process* process1 = createProcess(1, "Process1");
    Process* process2 = createProcess(2, "Process2");
    Process* process3 = createProcess(3, "Process3");

    insertFront(&head, process1);
    insertFront(&head, process2);
    insertFront(&head, process3);

    // Display the process list before deletion
    printf("Process List before deletion:\n");
    displayList(head);

    // Delete the process with PID 2 from the list
    deleteByPID(&head, 2);

    // Display the process list after deletion
    printf("\nProcess List after deletion:\n");
    displayList(head);

    // Free allocated memory
    free(process1);
    free(process2);
    free(process3);

    return 0;
}
