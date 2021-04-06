



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
// sleep makes the calling thread sleep until seconds seconds have elapsed or a signal arrives which is not ignored. 

//return int err
int sys_sleep(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  
    //thread_sleep(address); use clock sleep
    return 0;
}
//glen coded above


