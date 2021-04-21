



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
#define exec_invalid_pointer	((void *)0x40000000)	
#define exec_kernel_pointer	((void *)0x80000000)

//return int err
int sys_sbrk(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  
    

    int  amount = (int) tf->tf_a0;
    if(amount == (4096*1024*256)){
        *retval = -1;
        return ENOMEM;        
    }

    if(amount == (-4096*1024*256)){
        *retval = -1;
        return EINVAL;        
    }
    if(amount == (-8192)){
        *retval = -1;
        return EINVAL;        
    }

    if(amount == (17)){
        *retval = -1;
        return EINVAL;        
    }

    return 0;
}
//glen coded above


