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

// Function to insert a process at the rear of the linked list
void insertRear(Process** head, Process* newProcess) {
    if (*head == NULL) {
        *head = newProcess; // If list is empty, make the new process the head
    } else {
        Process* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newProcess; // Insert new process at the rear
    }
}

// Function to delete the process at the rear of the linked list by process ID
void deleteRearByPID(Process** head, int pid) {
    if (*head == NULL) {
        return; // Empty list, nothing to delete
    }
    if ((*head)->next == NULL) {
        if ((*head)->pid == pid) {
            free(*head); // Only one node in the list, free it
            *head = NULL; // Update head to NULL
        }
        return;
    }
    Process* current = *head;
    Process* prev = NULL;
    while (current->next != NULL) {
        if (current->next->pid == pid) {
            Process* temp = current->next;
            current->next = temp->next;
            free(temp); // Free memory of the last node
            return;
        }
        prev = current;
        current = current->next;
    }
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

    // Create processes and insert them at the rear of the list
    Process* process1 = createProcess(1, "Process1");
    Process* process2 = createProcess(2, "Process2");
    Process* process3 = createProcess(3, "Process3");

    insertRear(&head, process1);
    insertRear(&head, process2);
    insertRear(&head, process3);

    // Display the process list before deletion
    printf("Process List before deletion:\n");
    displayList(head);

    // Delete the process at the rear of the list by process ID
    deleteRearByPID(&head, 3);

    // Display the process list after deletion
    printf("\nProcess List after deletion:\n");
    displayList(head);

    // Free allocated memory
    free(process1);
    free(process2);
    free(process3);

    return 0;
}
