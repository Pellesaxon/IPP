/*
 * Copyright (C) 2023  Xiaoyue Chen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_NAME_SIZE 42
#define MAX_MSG_SIZE 2

int main(int argc, char *argv[argc + 1]) {
  int msg[MAX_MSG_SIZE], name[MAX_NAME_SIZE];
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int loser;
  int counter = -1;
  
  if (!rank) {
    loser = rank;
    counter = atoi(argv[1]);
    msg[0] = loser;
    msg[1] = counter;
    MPI_Send(msg, 2, MPI_INT, ((rank+1)%(size)), 0, MPI_COMM_WORLD);
  }

  while (true){
    MPI_Recv(msg, MAX_MSG_SIZE, MPI_INT, ((rank-1)%(size)), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    loser = msg[0];
    counter = msg[1];
    if (counter == 0){
      if (!rank) {
        printf("Process %d lost. Total %d processes.\n", loser, size);
      }
      if (loser != rank){
        MPI_Send(msg, 2, MPI_INT, ((rank+1)%(size)), 0, MPI_COMM_WORLD);
      }
      break;
      }
    else{
      counter--;
      loser = rank;
      msg[0] = loser;
      msg[1] = counter;
      MPI_Send(msg, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  }
  MPI_Finalize();
  return 0;
}
  /* TODO: In a loop: */
  /* TODO: Receive loser and counter from the previous process. */
  /* TODO: Check if counter is 0, decrement it, and set loser accordingly. */
  /* TODO: Send loser and counter to the next process. */
