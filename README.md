os161
=====

The project is completed as a part of the course ECE344: Operating System offered by University of Toronto. The project was done exclusively by Chao Glen Xu.

major updates
-------------

* added/modified various testbin programs used by os161-tester
* improved make process so depend.mk does not need to be checked into repository
* moved all executables into root directory under build folder so that so students cannot access DISK#.img 

assignment 1
------------

### Deliverables

* `df` command: toggle debug flags
* `dbflags` command:  view current debug flags
* `read` and `write` system call for console input and output
* `sleep` system call
* `__time` system call
* `_exit` system call


assignment 2
------------

### Deliverables

* lock implementation
* cv implementation
* catsem or catlock
* stoplight

assignment 3
------------

### Deliverables

* `waitpid` system call
* `fork` system call
* `getpid` system call
* `execv` system call
* `_exit` system call (needs to be updated)
* menu synchronization
* menu arguments (similar to execv)

### TODO

* `pipe` system call (to allow communication between processes)

assignment 4
------------

### Deliverables

* `sbrk` system call
* page reclamation
* demand paging
* swap
* copy-on-write

