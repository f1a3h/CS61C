#include <mpi.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TERMINATE -1
#define READY 0

void hello_world(int message) {
    int procID;

    // TODO: get the ID of the current program, and store in `procID`

    // Sleep for message % 5 seconds
    sleep(message % 5);

    // Print message
    printf("Hello world from task %d with process %d\n", message, procID);
}

int main(int argc, char** argv) {
    int numTasks = atoi(argv[1]);

    // TODO: use MPI_Init to initialize the program

    int procID, totalProcs;
    // TODO: get the total number of processes and store in `totalProcs`

    // TODO: get the ID of the current program, and store in `procID`

    // TODO: check if the current process is the manager
    if (__________) {
        // Manager node
        int nextTask = 0;
        MPI_Status status;
        int32_t message;

        // TODO: loop until we've completed `numTasks`
        while (__________) {
            // TODO: receive a message from any source (so we know that this node is done with its task)

            // TODO: get the source process using the `status` struct

            // TODO: send `nextTask` as the message to the process we just received a message from

            // TODO: increment `nextTask` by 1
        }

        // Wait for all processes to finish
        // TODO: loop through all processes
        // Hint: we have `totalProcs - 1` total, since there's a manager node
        for (________________________________________) {
            // TODO: receive a message from any source (so we know that this node is done with its task)

            // TODO: get the source process using the `status` struct

            // TODO: send `TERMINATE` as the message to the process we just received a message from

        }
    } else {
        // Worker node
        int32_t message;

        while (true) {
            // TODO: let the manager node know that this worker is ready
            // Hint: use MPI_Send to send a message

            // TODO: receive 1 message from the manager and store it in `message`
            // Hint: use MPI_Recv to receive a message

            // TODO: if the `message` is TERMINATE, break out of the loop to terminate

            // TODO: call `hello_world` and pass `message` as the argument
        }
    }

    // TODO: call MPI_Finalize since it is the end of the program
}
