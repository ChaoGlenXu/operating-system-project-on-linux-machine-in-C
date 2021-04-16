#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);

//glen coded below
int sys_exit(int exitcode);//return int err
int sys_write(struct trapframe *tf, int32_t *retval);
int sys_sleep(struct trapframe *tf, int32_t *retval);
int sys_time(struct trapframe *tf, int32_t *retval);
int sys_read(struct trapframe *tf, int32_t *retval);
int sys_fork(struct trapframe *tf, int32_t *retval);
int sys_getpid(struct trapframe *tf, int32_t *retval);
int sys_waitpid(struct trapframe *tf, int32_t *retval);
void glen_lab3_forkentry(void *data1, unsigned long data2);

//sysCall.h   syscall.h

#define pid_maximum_number 3000  //1 -29 //29 in tatal since 0 is reserved 

struct lab3_thread_pid_management{
    pid_t pid_array[pid_maximum_number];
    int status_array[pid_maximum_number];
};


struct pid_structure{
    pid_t pid;
    int taken; //0 = not taken | 1 = ready  | 2 = waiting | 3 = running | 4 = zombie 
    int status; //exitcode
    pid_t parent;
    pid_t child;
    struct thread * thread;
};

//ready, zombie, running, waiting, put into taken
//int32_t  varialbe = -5; could work

struct lab3_thread_pid_management the_pid_system;
struct pid_structure lab3_pid_array[pid_maximum_number];

void initialize_pid_array(void );
pid_t add_pid_to_pid_array(struct thread * thread);
int add_status_to_pid_array(int exitcode, pid_t thread_pid);

/*
void initialize_pid_system_to_zero(struct lab3_thread_pid_management *the_pid_system);
pid_t add_pid_to_pid_system(struct lab3_thread_pid_management *the_pid_system);
int add_status_to_pid_system(struct lab3_thread_pid_management *the_pid_system, int exitcode, pid_t thread_pid);
*/
//glen coded above

#endif /* _SYSCALL_H_ */
