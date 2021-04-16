



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

#include <types.h>
#include <lib.h>
#include <kern/errno.h>
#include <array.h>
#include <machine/spl.h>
#include <machine/pcb.h>
#include <thread.h>
#include <curthread.h>
#include <scheduler.h>
#include <addrspace.h>
#include <vnode.h>
#include "opt-synchprobs.h"

//Description
//Cause the current process to exit. The exit code exitcode is reported back to other process(es) via the waitpid() call. The process id of the exiting process should not be reused until all processes interested in collecting the exit code with waitpid have done so. (What "interested" means is intentionally left vague; you should design this.) 

//return int err
int sys_fork(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  

    //kprintf("AAAAAAAAAAAAAAAA\n"); 

    //label the parent here
    pid_t parent = curthread->lab3_thread_pid; //could be wrong//confirmed to be curhtread
    //lab3_pid_array[parent] 
    
    //fork will call the glen_lab3_child_entry funciton
    struct addrspace * child_address_space;// = as_create();//do i need this step and is this step nessesary?
    as_copy(curthread->t_vmspace , &child_address_space);
    
    struct trapframe *child_tf = kmalloc(sizeof(struct trapframe));
    if (child_tf == NULL) {
        return ENOMEM;
    }
    *child_tf = *tf;
    struct thread *the_child_thread = NULL;
    int error_code = thread_fork("child_process", (void *)child_address_space, (unsigned long) child_tf, glen_lab3_forkentry, &the_child_thread);
    
    //now the child is created, label the child here
    pid_t child = the_child_thread->lab3_thread_pid;
    
    //add the parent child relationship here
    lab3_pid_array[parent].child = child;
    lab3_pid_array[child].parent = parent;
    //kprintf("BBBBBBBBBBBBBBBB\n"); 
    if(error_code){;}//error checking, will do it after implemented waitpid

    *retval = the_child_thread->lab3_thread_pid;
    return 0;
}
//glen coded above


