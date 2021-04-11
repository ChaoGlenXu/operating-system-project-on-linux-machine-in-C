



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

//read

//To get some of the testing programs to work, you will also need to implement a read system call that reads one character at a time. The implementation of this system call should be straightforward. However, similar to the printing system call, its correctness is critical. Therefore we strongly suggest that you test it in isolation and only move on after you're confident about its correctness. 
//Description
//read reads up to buflen bytes from the file specified by fd, at the location in the file specified by the current seek position of the file, and stores them in the space pointed to by buf. The file must be open for reading.

//The current seek position of the file is advanced by the number of bytes read.

//Each read (or write) operation is atomic relative to other I/O to the same file. 

//return int err
int sys_read(struct trapframe *tf, int32_t *retval){
    (void) tf;
    (void) retval;  

    int the_fd_value = (int)tf->tf_a0;
    void * local_buffer = (void *)tf->tf_a1;
    size_t local_buflen = (size_t) tf->tf_a2;
    char *the_string_needed_to_put_into_buffer;
    //void * returned_buffer;
 /*   
    if(local_buffer == NULL){ 
        // *retval = -1;
        return EFAULT;
    }

    if ((char *)local_buflen == (char *)0xbadbeef ) {
        // *retval = -1;
        return EFAULT;
    }
    if((char *)local_buflen == (char *)0xdeadbeef){ 
        // *retval = -1;
        return EFAULT;
    }
    if(the_fd_value == STDIN_FILENO ){
        // *retval = -1;
        return EBADF;
    }
*/
    if(the_fd_value == STDIN_FILENO ){ // 0 is read based on the unistd.h
        the_string_needed_to_put_into_buffer = kmalloc(local_buflen);
        //glen has a idea, if sys_read has kprintf, then this should be kgets// kgets read a string off the console.
        //kgets((char *)the_string_needed_to_put_into_buffer, (size_t) local_buflen);//kgets() will always cause problem for the lab3 , so decided use the getch()
        int i = 0;        
        while (i != (int)local_buflen) {
		the_string_needed_to_put_into_buffer[i] = getch();
        i++;
		}

        copyout((const void *) the_string_needed_to_put_into_buffer, (userptr_t) local_buffer, (size_t) local_buflen);
        //copyin((const_userptr_t) the_string_needed_to_put_into_buffer, local_buffer, local_buflen);
        *retval =  local_buflen;

    }

    return 0;
}
//glen coded above


