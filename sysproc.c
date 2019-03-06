#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  if (toggle_value==1) {
    countCalls[7]+=1;
  }
  return fork();
}


int
sys_exit(void)
{
  if (toggle_value==1) {
    countCalls[6]+=1;
  }
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  if (toggle_value==1) {
    countCalls[27]+=1;
  }
  return wait();
}

int
sys_kill(void)
{
  int pid;
  if (toggle_value==1) {
    countCalls[10]+=1;
  }
  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  if (toggle_value==1) {
    countCalls[9]+=1;
  }
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  if (toggle_value==1) {
    countCalls[20]+=1;
  }
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  if (toggle_value==1) {
    countCalls[23]+=1;
  }
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  if (toggle_value==1) {
    countCalls[26]+=1;
  }
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_print_count(void)
{
  if (toggle_value==1) {
    countCalls[16]+=1;
  }
  return print_count();
}

int
sys_toggle(void)
{
  if (toggle_value==1) {
    countCalls[24]+=1;
  }
  return toggle();
}

int
sys_add(void)
{
  int a;
  int b;
  argint(0,&a);
  argint(1,&b);
  // cprintf("%d\n",a+b);
  if (toggle_value==1) {
    countCalls[1]+=1;
  }
  return a+b;
}

int
sys_ps(void)
{
  if (toggle_value==1) {
    countCalls[17]+=1;
  }
  return ps();
}

int
sys_send(void)
{
  if (toggle_value==1) {
  countCalls[21]+=1;
}

  return send();
}

int
sys_recv(void *msg)
{
  if (toggle_value==1) {
    countCalls[19]+=1;
  }
  char* mess;
  argstr(0,&mess);
  if (queues_initialized!=1){
    intitialize_queues();
    queues_initialized=1;
  }
  struct proc *curproc = myproc();

  if (isEmpty(message_queues[curproc->pid])==1){
    // cprintf("If me ghus gaya %s\n");
    curproc->state=SLEEPING;
    enqueue(wait_queues[curproc->pid],curproc->pid);
    sched();
  }
  int msg_no=dequeue(message_queues[curproc->pid]);
  // cprintf("msg mila hai  %s\n",message_buffer[msg_no]);

  // for(int i=0;i<8;i++){
  //   mess[i]=message_buffer[msg_no][i];
  // }
  // cprintf("msg_no %d\n",msg_no);
  safestrcpy(mess,message_buffer[msg_no],8);
// cprintf(" s me hai  %s\n",s);
  // while (len-->0) {
  //   *mess++= *s++;
  // }
  // *mess=message_buffer[msg_no];
  // cprintf("msg mila hai and  %s\n",mess);
  // FreeMessageBuffer(msg_no);
  return 0;
  // recv_msg();
}

int
sys_send_multi(void)
{
  if (toggle_value==1) {
    countCalls[22]+=1;
  }
  return send_multi();
}
