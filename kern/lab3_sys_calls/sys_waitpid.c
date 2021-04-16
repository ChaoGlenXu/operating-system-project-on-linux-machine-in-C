



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
#include <synch.h>
#include <thread.h>
#include <curthread.h>
#include <machine/spl.h>

#include <array.h>

//Description
//Cause the current process to exit. The exit code exitcode is reported back to other process(es) via the waitpid() call. The process id of the exiting process should not be reused until all processes interested in collecting the exit code with waitpid have done so. (What "interested" means is intentionally left vague; you should design this.) 

struct lock lock_sys_waitpid;

//return int err
int sys_waitpid(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  
    

    pid_t child_pid = (pid_t) tf->tf_a0;
    int* status = (int*) tf->tf_a1;
    //int options = (int) tf->tf_a2;

    (void)child_pid;
    
    if(status == NULL ){
        *retval = -1;
        return EFAULT;
    }

    //check if the pid value is valid, pid has to be a real process that exist
    //the pid has to be a direct child 
/*    if(lab3_pid_array[child].parent == -4){//invalid pid
        tf->tf_v0 = EINVAL;// Invalid argument 
        return -1;
    }
    if(lab3_pid_array[child].status == -4){//invalid pid
        tf->tf_v0 = EFAULT; // Bad memory reference 
        return -1;
    }
*/
    //lab session note: thread_join(struct thread * thread) should be called in sys_waitpid in parallel to sys_exit calls ..

    int s = splhigh(); //lock here   like pid arrary or etc
    //lock_acquire(&lock_sys_waitpid);


	//for (i=0; i<array_getnum(sleepers); i++) {
	//	struct thread *t = array_getguy(sleepers, i);
    //struct thread *child_thread = array_getguy(sleepers, child_pid);
    //check if the specified pid exist or not
    if(lab3_pid_array[child_pid].parent != curthread->lab3_thread_pid){
        *retval = -1;
        splx(s);
        return EINVAL;
    }
    if(lab3_pid_array[child_pid].taken >= 1){ //this case: the child thread exits
        *retval = child_pid;
        // 2 possibilities: 1. child still running 2. child already exited
        if (lab3_pid_array[child_pid].thread != NULL) {
            thread_join(lab3_pid_array[child_pid].thread);
        }
        *status = lab3_pid_array[child_pid].status;
        lab3_pid_array[child_pid].taken = 0;
        //thread_exit();//not sure if it should be thread exit the current thread
    }else{ //this case: the child thread exits
        *retval = -1;
        splx(s);
        return EINVAL;
    }

    //lock_release(&lock_sys_waitpid);
    splx(s); //release the lock
    return 0;
}
//glen coded above


