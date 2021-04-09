



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
#include <kern/errno.h>
#include <lib.h>
#include <clock.h>
#include <generic/rtclock.h>
#include "autoconf.h"

//Description
// sleep makes the calling thread sleep until seconds seconds have elapsed or a signal arrives which is not ignored. 

//return int err
int sys_time(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  
    //thread_yield();
    //time_t *secs = (time_t *) tf->tf_a0;
    //u_int32_t *nsecs = (u_int32_t *) tf->tf_a1; // unsigned long
    /*gettime(secs, nsecs); // secs == NULL -> gettime(NULL, nsecs);
    if((secs != NULL )&&(nsecs!= NULL)){ return 0;}
    if(secs != NULL ){
        gettime(0, nsecs);
        return 0;
    }
    if(nsecs!= NULL){
        gettime(secs, 0);
        return 0;
    }
    */

    //gettime(secs, nsecs);
    //*retval = *secs;
    //copyout(buf, new_dynamic_data, size);
    //kprintf("secs, nsecs: %d, %u\n", secs, nsecs);
    
    time_t *usr_secs = (time_t *) tf->tf_a0;
    u_int32_t *usr_nsecs = (u_int32_t *) tf->tf_a1;
    time_t secs;  //time_t *secs is wrong because this is a null pointer
    u_int32_t nsecs;
    gettime(&secs, &nsecs);
    if (usr_secs != NULL) {
    copyout((void *)&secs, (userptr_t)usr_secs, sizeof(time_t));
    }
    if (usr_nsecs != NULL) {
    copyout((void *)&nsecs, (userptr_t)usr_nsecs, sizeof(u_int32_t));
    }
    //copyout(&nsecs .....
    *retval = secs;
    
    return 0;
}

//fork key idea:
//key point 1: copy the address space, address space is the loose memory the process use, every process has differen virtual address space,



//glen coded above


