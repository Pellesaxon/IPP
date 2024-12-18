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

int main(int argc, char *argv[argc + 1]) {

  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int loser;
  int counter;
  int prev;
  int next;

  if (!rank) {
    loser = -1;
    counter = atoi(argv[1]);
    prev = -1;
    
  }
  else{
    prev = rank -1;
  }

  

  if(rank == size-1){
    next = 0;
  }
  else {
    next = rank +1;
  }
  if (!rank){
    loser = rank;
    MPI_Send(&loser,1,MPI_INT,next,0,MPI_COMM_WORLD);
    MPI_Send(&counter,1,MPI_INT,next,0,MPI_COMM_WORLD);
  }

  while (1)
  {
    MPI_Recv(&loser,1,MPI_INT,prev,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    MPI_Recv(&counter,1,MPI_INT,prev,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    if (counter != 0){
      counter--;
      loser = rank;
      MPI_Send(&loser,1,MPI_INT,next,0,MPI_COMM_WORLD);
      MPI_Send(&counter,1,MPI_INT,next,0,MPI_COMM_WORLD);
    }
    else {
      
      MPI_Send(&loser,1,MPI_INT,next,0,MPI_COMM_WORLD);
      MPI_Send(&counter,1,MPI_INT,next,0,MPI_COMM_WORLD);
      break;
    }
  }
  
  /* TODO: In a loop: */
  /* TODO: Receive loser and counter from the previous process. */
  /* TODO: Check if counter is 0, decrement it, and set loser accordingly. */
  /* TODO: Send loser and counter to the next process. */

  if (!rank) {
    printf("Process %d lost. Total %d processes.\n", loser, size);
  }

  MPI_Finalize();
  return 0;
}
