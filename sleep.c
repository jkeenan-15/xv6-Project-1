#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {  //argc is integer 2. argv bumps to argv[1]
  int time;
  
  if (argc !=2) {  //counter doesn't equal 2 then it continues sleeping
    fprintf(2, "Usage: sleep time\n\n");
    exit(1);
    }
    
    time = atoi(argv[1]); //atoi converts the counter to an integer until
    sleep(time);          // sleep equals 2. 
    exit(0);
}
