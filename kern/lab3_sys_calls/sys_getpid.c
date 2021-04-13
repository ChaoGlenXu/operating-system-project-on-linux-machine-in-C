



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
#include <machine/pcb.h>
#include <machine/spl.h>
#include <machine/trapframe.h>
#include <kern/callno.h>
#include <kern/unistd.h>
// Debug
#include <thread.h>
#include <curthread.h>
#include <lamebus/ltrace.h>

//struct lab3_thread_pid_management *the_pid_system;


//return int err
int sys_getpid(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  
    
	*retval = (pid_t) curthread->lab3_thread_pid;
    return 0;
}



//the code below are not syscall but the functions for managment of thread pid system
void initialize_pid_system_to_zero(struct lab3_thread_pid_management *the_pid_system){
    int i;
    for(i = 0; i < pid_maximum_number ; i++){
        the_pid_system->pid_array[i] = 0;
    }   
    return;
}

pid_t add_to_pid_system(struct lab3_thread_pid_management *the_pid_system){
    int i;
    for(i = 1; i < pid_maximum_number ; i++){
        if (the_pid_system->pid_array[i] == 0){
            the_pid_system->pid_array[i] = 1;
            return (pid_t)i;
        }
    }   
    return -5;//the arrary is full
}

//glen coded above


