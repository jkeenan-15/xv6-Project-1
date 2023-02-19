#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
filter(int pipe_1[])
{
  int rpipe[2];
  pipe(rpipe);
  int primes[50];
  int cnt = 0; //counting up is set to 0
  char buf[1];
  
  while ((read(pipe_1[0], buf, sizeof(buf))) != 0) {
    primes[cnt++] = buf[0];
  }
  close(pipe_1[0]);
  
  if (cnt == 0) return; 
  int first = primes[0]; 
  printf("prime %d\n", first);
  
  for (int i = 1; i < cnt; i++) { 
    if (primes[i] % first != 0) {
      char p = primes[i];
      write(rpipe[1], &p, 1);
    }
  }
  close(rpipe[1]);
  
  int pid = fork();
  if (pid == 0) {
    // child
    filter(rpipe);
  }  
}  
//2-35 are fed through the first process into the pipline. Each prime number found is arranged and sent to the 2nd process below. 
int
main()
{
  int pipe_1[2];
  
  pipe(pipe_1);
  
  for (int i = 2; i <= 35; i++) {
    char p = i;
    write(pipe_1[1], &p, 1);
  }
  close(pipe_1[1]);
  
  filter(pipe_1);
  
  wait((int *) 0);
  
  exit(0);
}
// This process ensures prime numbers found in process 1 are correct and then writes them to terminal to be printed. 
