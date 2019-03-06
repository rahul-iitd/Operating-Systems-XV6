#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "date.h"

int
main(int argc, char *argv[]){

  int sender_pid=atoi(argv[1]);
  int rec_pids=atoi(argv[2]);
  void *msg=argv[3];
  send_multi(sender_pid,rec_pids,msg);
  exit();
}
