



//glen coded below
#include <types.h> //why error if //
#include <kern/unistd.h>
#include <kern/errno.h>
#include <lib.h>   //why error if //
#include <addrspace.h>
#include <thread.h>
#include <curthread.h>
#include <vm.h>
#include <vfs.h>
#include <test.h>

#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <machine/pcb.h>
#include <machine/spl.h>
#include <machine/trapframe.h>
#include <kern/callno.h>
#include <syscall.h>

//Description
//Cause the current process to exit. The exit code exitcode is reported back to other process(es) via the waitpid() call. The process id of the exiting process should not be reused until all processes interested in collecting the exit code with waitpid have done so. (What "interested" means is intentionally left vague; you should design this.) 
int exitcode;

//return int err
int sys_exit(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  
    exitcode = (int)tf->tf_a0;
    //assume curthread calling this function
    pid_t local_pid = (pid_t) curthread->lab3_thread_pid;
    add_status_to_pid_system( &the_pid_system, exitcode, local_pid);
    
    thread_yield();
    
    
    thread_exit();
    return 0;
}
//glen coded above


