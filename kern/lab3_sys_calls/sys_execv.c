



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
int sys_execv(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  
    
/*
    char *program = (char *) tf->tf_a0;
    //char **args = (char **) tf->tf_a1;

    //kprintf("AAAAAAAAAAAAAAAA\n"); 

    if(program == NULL){
        *retval = -1;
        return EFAULT;        
    }
     if(program == (char *)exec_invalid_pointer){
        *retval = -1;
        return EFAULT;        
    }
    if(program == (char *)exec_kernel_pointer){
        *retval = -1;
        return EFAULT;        
    }
    //if(program > pid_maximum_number|| child_pid < 0){
    //    *retval = -1;
    //    return EINVAL;        
    //}



*/

    return 0;
}
//glen coded above

