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

int
sys_clone(void)
{
  void (*fcn)(void *, void *);
  void *arg1, *arg2, *stack;

  if (argptr(0, (void *)&fcn, sizeof(*fcn)) < 0 ||
      argptr(1, &arg1, sizeof(*arg1)) < 0 ||
      argptr(2, &arg2, sizeof(*arg2)) < 0 ||
      argptr(3, &stack, PGSIZE) < 0)
    return -1;

  int i, pid;
  struct proc *np;
  struct proc *curproc = myproc();

  if ((np = allocproc()) == 0)
    return -1;

  np->pgdir = curproc->pgdir; // Share address space with the parent process
  np->sz = curproc->sz;

  // Set up new thread's stack
  memset(np->tf, 0, sizeof(*np->tf));
  np->tf->esp = (uint)stack + PGSIZE;
  np->tf->ebp = np->tf->esp;
  np->tf->eip = (uint)fcn;

  // Pass arguments to the new thread
  np->tf->edx = (uint)arg1;
  np->tf->ecx = (uint)arg2;

  // Clear %eax so that fork returns 0 in the child process
  np->tf->eax = 0;

  for (i = 0; i < NOFILE; i++)
    if (curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));

  pid = np->pid;

  acquire(&ptable.lock);

  np->state = RUNNABLE;

  release(&ptable.lock);

  return pid;
}

int
sys_join(void)
{
    void **stack;

    // join 함수의 인자를 가져옴
    if (argptr(0, (void*)&stack, sizeof(*stack)) < 0) {
        return -1;
    }

    // 자식 스레드를 대기
    int tid = jointhread((uint)stack);

    // 스레드 id 반환
    return tid;
}


