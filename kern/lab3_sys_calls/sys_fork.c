



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

//return int err
int sys_fork(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  
    //thread_yield();
    //thread_sleep(const void *addr);
    //size_t size = tf->tf_a2;
    int the_fd_value = tf->tf_a0;
    size_t local_buflen = (size_t) tf->tf_a2;
    if((the_fd_value == 1 )||(the_fd_value == 2) ){ //assume 1 is write
        //void *new_dynamic_data = kmalloc(size);

        //strcpy(new_dynamic_data, buf); //
        //copyout((int *)tf->tf_a1, new_dynamic_data, size);  
        kprintf("%s", (char *)tf->tf_a1);  //  void *
        *retval =  local_buflen;  
    }

    return 0;
}
//glen coded above


