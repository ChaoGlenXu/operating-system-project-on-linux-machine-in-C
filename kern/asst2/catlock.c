/*
 * catlock.c
 *
 * Please use LOCKS/CV'S to solve the cat syncronization problem in 
 * this file.
 */


/*
 * 
 * Includes
 *
 */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include "catmouse.h"

//glen code below
#include <synch.h>
struct lock *two_cat_dishs;
int lab2_mouse = 0;
int lab2_cats = 0;
int current_food_available = 2;
int food_0 = 1;
int food_1 = 2;
int current_food_being_eaten = 0;
//glen code above

/*
 * 
 * Function Definitions
 * 
 */

/*
 * catlock()
 *
 * Arguments:
 *      void * unusedpointer: currently unused.
 *      unsigned long catnumber: holds the cat identifier from 0 to NCATS -
 *      1.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Write and comment this function using locks/cv's.
 *
 */

static
void
catlock(void * unusedpointer, 
        unsigned long catnumber)
{
        /*
         * Avoid unused variable warnings.
         */

        //glen code below
        //struct lock *two_cat_dishs;
        int i;
        for (i = 0; i < NMEALS; i++){
            lock_acquire(two_cat_dishs);
            
            if(lab2_mouse > 0){
                lock_release(two_cat_dishs);
            //current_food_available--;
            }else{//not mose present
               //lock_acquire(two_cat_dishs); 
                //this case, only one cat can be present at a time
                lab2_cats ++; 
                current_food_available --;
                if(current_food_being_eaten == food_0){
                     current_food_being_eaten = food_1;       
                }else{current_food_being_eaten = food_0;}
                catmouse_eat("cat", catnumber, current_food_being_eaten, i);
                lab2_cats --;
                current_food_available++;
                lock_release(two_cat_dishs);
            }
        }
        //glen code above


        (void) unusedpointer;
        (void) catnumber;
}
	

/*
 * mouselock()
 *
 * Arguments:
 *      void * unusedpointer: currently unused.
 *      unsigned long mousenumber: holds the mouse identifier from 0 to 
 *              NMICE - 1.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Write and comment this function using locks/cv's.
 *
 */

static
void
mouselock(void * unusedpointer,
          unsigned long mousenumber)
{
        /*
         * Avoid unused variable warnings.
         */

        //glen code below
        //struct lock *two_cat_dishs;
        int i;
        for (i = 0; i < NMEALS; i++){
            lock_acquire(two_cat_dishs);
            
            if(lab2_cats > 0){
                lock_release(two_cat_dishs);
            //current_food_available--;
            }else{//not mose present
               //lock_acquire(two_cat_dishs); 
                //this case, only one mouse can be present at a time
                lab2_mouse ++; 
                current_food_available --;
                if(current_food_being_eaten == food_0){
                     current_food_being_eaten = food_1;       
                }else{current_food_being_eaten = food_0;}
                catmouse_eat("mouse", mousenumber, current_food_being_eaten, i);
                lab2_mouse --;
                lock_release(two_cat_dishs);
            }
        }
        //glen code above
        
        (void) unusedpointer;
        (void) mousenumber;
}


/*
 * catmouselock()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up catlock() and mouselock() threads.  Change
 *      this code as necessary for your solution.
 */

int
catmouselock(int nargs,
             char ** args)
{
        int index, error;
   
        /*
         * Start NCATS catlock() threads.
         */
        
        //glen code below
            two_cat_dishs = lock_create("two_cat_dishs");
        //glen code above 

    
        for (index = 0; index < NCATS; index++) {
           
                error = thread_fork("catlock thread", 
                                    NULL, 
                                    index, 
                                    catlock, 
                                    NULL
                                    );
                
                /*
                 * panic() on error.
                 */

                if (error) {
                 
                        panic("catlock: thread_fork failed: %s\n", 
                              strerror(error)
                              );
                }
        }

        /*
         * Start NMICE mouselock() threads.
         */

        for (index = 0; index < NMICE; index++) {
   
                error = thread_fork("mouselock thread", 
                                    NULL, 
                                    index, 
                                    mouselock, 
                                    NULL
                                    );
      
                /*
                 * panic() on error.
                 */

                if (error) {
         
                        panic("mouselock: thread_fork failed: %s\n", 
                              strerror(error)
                              );
                }
        }
        
        /*
         * wait until all other threads finish
         */
        
        while (thread_count() > 1)
                thread_yield();

        (void)nargs;
        (void)args;
        kprintf("catlock test done\n");

        return 0;
}

