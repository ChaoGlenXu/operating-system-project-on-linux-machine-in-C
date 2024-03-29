#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <machine/pcb.h>
#include <machine/spl.h>
#include <machine/trapframe.h>
#include <kern/callno.h>
#include <syscall.h>


//glen coded below
//#include <sy_exit.c>
//#include "sy_exit.c"
//void sys_exit(struct trapframe *tf, int32_t *retval, int *err);
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
//glen coded above


/*
 * System call handler.
 *
 * A pointer to the trapframe created during exception entry (in
 * exception.S) is passed in.
 *
 * The calling conventions for syscalls are as follows: Like ordinary
 * function calls, the first 4 32-bit arguments are passed in the 4
 * argument registers a0-a3. In addition, the system call number is
 * passed in the v0 register.
 *
 * On successful return, the return value is passed back in the v0
 * register, like an ordinary function call, and the a3 register is
 * also set to 0 to indicate success.
 *
 * On an error return, the error code is passed back in the v0
 * register, and the a3 register is set to 1 to indicate failure.
 * (Userlevel code takes care of storing the error code in errno and
 * returning the value -1 from the actual userlevel syscall function.
 * See src/lib/libc/syscalls.S and related files.)
 *
 * Upon syscall return the program counter stored in the trapframe
 * must be incremented by one instruction; otherwise the exception
 * return code will restart the "syscall" instruction and the system
 * call will repeat forever.
 *
 * Since none of the OS/161 system calls have more than 4 arguments,
 * there should be no need to fetch additional arguments from the
 * user-level stack.
 *
 * Watch out: if you make system calls that have 64-bit quantities as
 * arguments, they will get passed in pairs of registers, and not
 * necessarily in the way you expect. We recommend you don't do it.
 * (In fact, we recommend you don't use 64-bit quantities at all. See
 * arch/mips/include/types.h.)
 */

void
mips_syscall(struct trapframe *tf)
{
	int callno;
	int32_t retval;
	int err;

	assert(curspl==0);

	callno = tf->tf_v0;

	/*
	 * Initialize retval to 0. Many of the system calls don't
	 * really return a value, just 0 for success and -1 on
	 * error. Since retval is the value returned on success,
	 * initialize it to 0 by default; thus it's not necessary to
	 * deal with it except for calls that return other values, 
	 * like write.
	 */

	retval = 0;
//kprintf("AoooooA\n");
	switch (callno) {
	    case SYS_reboot:
		err = sys_reboot(tf->tf_a0);
		break;

	    /* Add stuff here */
 
        //glen coded below
        case SYS__exit:
		//err = sys_exit(&tf, &retval); is the &tf the pass by reference of the pointer
		err = sys_exit((int)tf->tf_a0); //or (tf, retval, err) //a_0 sin //&tf address of the pointer
        // int *status = (int *)tf->tf_a1;
        // copyout: copy from kernelspace "out" to userspace
        // copyin: copy from userpsace "in" to kernelspace
		break;

        case SYS_write:
		err = sys_write(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;

        case SYS_sleep:
		err = sys_sleep(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;

        case SYS___time:
		err = sys_time(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;

        case SYS_read:
		err = sys_read(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;

        case SYS_fork:
        //kprintf("A sys fork called A\n");
		err = sys_fork(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;

        case SYS_getpid:
		err = sys_getpid(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;

        case SYS_waitpid:
		err = sys_waitpid(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;

        case SYS_execv:
		err = sys_execv(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;

        case SYS_sbrk:
		err = sys_sbrk(tf, &retval); //or (tf, retval, err) //a_0 sin
		break;
        //glen coded above

	    default:
		kprintf("Unknown syscall %d\n", callno);
		err = ENOSYS;
		break;
	}


	if (err) {
		/*
		 * Return the error code. This gets converted at
		 * userlevel to a return value of -1 and the error
		 * code in errno.
		 */
		tf->tf_v0 = err;
		tf->tf_a3 = 1;      /* signal an error */
	}
	else {
		/* Success. */
		tf->tf_v0 = retval;
		tf->tf_a3 = 0;      /* signal no error */
	}
	
	/*
	 * Now, advance the program counter, to avoid restarting
	 * the syscall over and over again.
	 */
	
	tf->tf_epc += 4;

	/* Make sure the syscall code didn't forget to lower spl */
	assert(curspl==0);
}

void
md_forkentry(struct trapframe *tf)
{
	/*
	 * This function is provided as a reminder. You need to write
	 * both it and the code that calls it.
	 *
	 * Thus, you can trash it and do things another way if you prefer.
	 */

    //glen coded below
    
    //glen coded above
	(void)tf;
}


void
glen_lab3_forkentry(void *data1, unsigned long data2)//glens' idea for new forkentry and fork
{
	/*
	 * This function is provided as a reminder. You need to write
	 * both it and the code that calls it.
	 *
	 * Thus, you can trash it and do things another way if you prefer.
	 */

    //glen coded below
    (void )data1; //data1 is child address space
    (void)data2; //data2 is the parent trapframe 

    curthread->t_vmspace = (struct addrspace *)data1; 
    as_activate( (struct addrspace *)data1 );

    struct trapframe child_tf = *(struct trapframe *)data2;
    //child_tf =    (struct trapframe *)kmalloc(sizeof(struct trapframe))  ;
    //child_tf = *(   (struct trapframe *)data2  );//child copy the parrent
    child_tf.tf_v0 = 0;
    child_tf.tf_a3 = 0;
    child_tf.tf_epc = (child_tf.tf_epc) + 4; //glen: the epc is the program counter, If system is 32 -bit the size would be 4 bytes for all the pointers.
    
    kfree((struct trapframe *)data2);

    mips_usermode(&child_tf);//continue the process, transfer the control of the process to user mode
    //glen coded above
	
}










