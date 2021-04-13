#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);

//glen coded below
int sys_exit(struct trapframe *tf, int32_t *retval);//return int err
int sys_write(struct trapframe *tf, int32_t *retval);
int sys_sleep(struct trapframe *tf, int32_t *retval);
int sys_time(struct trapframe *tf, int32_t *retval);
int sys_read(struct trapframe *tf, int32_t *retval);
int sys_fork(struct trapframe *tf, int32_t *retval);
int sys_getpid(struct trapframe *tf, int32_t *retval);
int sys_waitpid(struct trapframe *tf, int32_t *retval);
void glen_lab3_forkentry(void *data1, unsigned long data2);

//sysCall.h   syscall.h

#define pid_maximum_number 30  //1 -29 //29 in tatal since 0 is reserved 

struct lab3_thread_pid_management{
    pid_t pid_array[pid_maximum_number];
};

struct lab3_thread_pid_management the_pid_system;
void initialize_pid_system_to_zero(struct lab3_thread_pid_management *the_pid_system);
pid_t add_to_pid_system(struct lab3_thread_pid_management *the_pid_system);
//glen coded above

#endif /* _SYSCALL_H_ */
