#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int toggle_value = 0;
extern int ps(void);
extern int setpriority(int pid, int priority);
extern int getpriority(int pid);

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
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
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// toggle whether to print the trace of the program
int
sys_toggle (void)
{

  toggle_value = (toggle_value + 1) % 2;
  return toggle_value;
}

// add two numbers
int
sys_add (void)
{

  int arg1, arg2;
  argint(0, &arg1);
  argint(1, &arg2);

  return (arg1 + arg2);
}

// print
int
sys_ps (void)
{
  ps();
  return 1;   
}

int
sys_setpriority (void)
{
  int arg1, arg2;
  argint(0, &arg1);
  argint(1, &arg2);
  setpriority(arg1, arg2);
  return 1;   
}

int
sys_getpriority (void)
{
  int arg1;
  argint(0, &arg1);
  return getpriority(arg1);; 
}