#include <stdio.h>
#include <mpi.h>
#include <chrono>
#include <iostream>

// brute force is prime
bool IsPrime(long long num)
{
    for (long long i = 2; i < num; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    int process_Rank, size_Of_Cluster;
    MPI_Request send_request, recv_request;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    printf("Hello World from process %d of %d\n", process_Rank, size_Of_Cluster);

    auto start = std::chrono::system_clock::now();
    auto end = start;
    std::chrono::duration<double> elapsed_seconds = end - start;

    long long inp = 1;
    long long latestPrime = 1;
    long long received_progress[size_Of_Cluster] = {0}; // Initialize to zero
    int checkTime = 1;

    while (elapsed_seconds.count() < 60)
    {
        // Compute if the current number is prime
        bool isPrime = IsPrime(inp);
        if (isPrime)
            latestPrime = inp;

        // Periodically send and receive data
        if (elapsed_seconds.count() > checkTime)
        {
            // Send latest prime to all other processes
            for (int dest = 0; dest < size_Of_Cluster; dest++)
            {
                if (dest != process_Rank)
                    MPI_Isend(&latestPrime, 1, MPI_LONG_LONG_INT, dest, 0, MPI_COMM_WORLD, &send_request);
            }

            // Receive data from all other processes
            for (int src = 0; src < size_Of_Cluster; src++)
            {
                if (src != process_Rank)
                {
                    MPI_Irecv(&received_progress[src], 1, MPI_LONG_LONG_INT, src, 0, MPI_COMM_WORLD, &recv_request);
                    MPI_Wait(&recv_request, &status); // Ensure the receive is complete
                }
            }

            bool winning = true;

            for (int i = 0; i < size_Of_Cluster; i++)
            {
                if (i != process_Rank)
                {
                    if (received_progress[i] > latestPrime)
                        winning = false;
                }
            }

            // Print progress
            if (winning)
            {
                for (int i = 0; i < size_Of_Cluster; i++)
                {
                    if (i == process_Rank)
                        printf("|$%lld$|", latestPrime);
                    else
                        printf("|-%lld-|", received_progress[i]);
                }

                auto start2 = std::chrono::system_clock::now();
                auto end2 = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds2 = end2 - start2;

                while (elapsed_seconds2.count() < 0.002)
                {
                    end2 = std::chrono::system_clock::now();
                    elapsed_seconds2 = end2 - start2;
                }

                // printf("slept for %lf", elapsed_seconds2.count());
                printf("\n");
            }

            checkTime += 5;
        }

        inp++; // Increment the input value
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start; // Update elapsed time
    }

    if (process_Rank == 0)
        printf("Done\n");

    MPI_Finalize();
    return 0;
}
