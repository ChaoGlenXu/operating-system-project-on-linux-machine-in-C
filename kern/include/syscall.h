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
//sysCall.h   syscall.h
//glen coded above

#endif /* _SYSCALL_H_ */
