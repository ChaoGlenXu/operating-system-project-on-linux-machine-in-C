/* 
 * stoplight.c
 *
 * You can use any synchronization primitives available to solve
 * the stoplight problem in this file.
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

//glen coded below
#include <synch.h>
//glen coded above

/*
 * Number of cars created.
 */

#define NCARS 20

//glen coded below
//global variables for maintainance
struct semaphore *ne_1;
struct semaphore *nw_2;
struct semaphore *sw_3;
struct semaphore *se_4 ;
struct semaphore *lock_all_four_quadrant;
int does_not_matter_number = 1;
int north = 0;
int east = 1;
int south = 2;
int west = 3;
//glen coded above

/*
 *
 * Function Definitions
 *
 */

static const char *directions[] = { "N", "E", "S", "W" };

static const char *msgs[] = {
        "approaching:",
        "region1:    ",
        "region2:    ",
        "region3:    ",
        "leaving:    "
};

/* use these constants for the first parameter of message */
enum { APPROACHING, REGION1, REGION2, REGION3, LEAVING };

static void
message(int msg_nr, int carnumber, int cardirection, int destdirection)
{
        kprintf("%s car = %2d, direction = %s, destination = %s\n",
                msgs[msg_nr], carnumber,
                directions[cardirection], directions[destdirection]);
}
 
/*
 * gostraight()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement passing straight through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
gostraight(unsigned long cardirection,
           unsigned long carnumber)
{
        /*
         * Avoid unused variable warnings.
         */
       
        
        //glen coded below
        P(lock_all_four_quadrant);
        if(cardirection == 0){//from north
            P(nw_2);
            P(sw_3);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, south);
            message(REGION1, carnumber, cardirection, south);
            message(REGION2, carnumber, cardirection, south);
            message(LEAVING, carnumber, cardirection, south);
            V(nw_2);
            V(sw_3);
        }else if(cardirection == 1){//from east
            P(ne_1);
            P(nw_2);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, west);
            message(REGION1, carnumber, cardirection, west);
            message(REGION2, carnumber, cardirection, west);
            message(LEAVING, carnumber, cardirection, west);
            V(ne_1);
            V(nw_2);
        }else if(cardirection == 2){//from south
            P(se_4);
            P(ne_1);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, north);
            message(REGION1, carnumber, cardirection, north);
            message(REGION2, carnumber, cardirection, north);
            message(LEAVING, carnumber, cardirection, north);
            V(se_4);
            V(ne_1);
        }else if(cardirection == 3){//from west
            P(sw_3);
            P(se_4);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, east);
            message(REGION1, carnumber, cardirection, east);
            message(REGION2, carnumber, cardirection, east);
            message(LEAVING, carnumber, cardirection, east);
            V(sw_3);
            V(se_4);
        }
        //V(lock_all_four_quadrant);
        //glen coded above            

        (void) cardirection;
        (void) carnumber;
}


/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnleft(unsigned long cardirection,
         unsigned long carnumber)
{
        /*
         * Avoid unused variable warnings.
         */

        //glen coded below
        P(lock_all_four_quadrant);
        if(cardirection == 0){//from north
            P(nw_2);
            P(sw_3);
            P(se_4);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, east);
            message(REGION1, carnumber, cardirection, east);
            message(REGION2, carnumber, cardirection, east);
            message(REGION3, carnumber, cardirection, east);
            message(LEAVING, carnumber, cardirection, east);            
            V(nw_2);
            V(sw_3);
            V(se_4);
        }else if(cardirection == 1){//from east
            P(ne_1);
            P(nw_2);
            P(sw_3);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, south);
            message(REGION1, carnumber, cardirection, south);
            message(REGION2, carnumber, cardirection, south);
            message(REGION3, carnumber, cardirection, south);
            message(LEAVING, carnumber, cardirection, south);
            V(ne_1);
            V(nw_2);
            V(sw_3);
        }else if(cardirection == 2){//from south
            P(se_4);
            P(ne_1);
            P(nw_2);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, west);
            message(REGION1, carnumber, cardirection, west);
            message(REGION2, carnumber, cardirection, west);
            message(REGION3, carnumber, cardirection, west);
            message(LEAVING, carnumber, cardirection, west);
            V(se_4);
            V(ne_1);
            V(nw_2);
        }else if(cardirection == 3){//from west
            P(sw_3);
            P(se_4);
            P(ne_1);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, north);
            message(REGION1, carnumber, cardirection, north);
            message(REGION2, carnumber, cardirection, north);
            message(REGION3, carnumber, cardirection, north);
            message(LEAVING, carnumber, cardirection, north);
            V(sw_3);
            V(se_4);
            V(ne_1);
        }
        //V(lock_all_four_quadrant);
        //glen coded above      

        (void) cardirection;
        (void) carnumber;
}


/*
 * turnright()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnright(unsigned long cardirection,
          unsigned long carnumber)
{
        /*
         * Avoid unused variable warnings.
         */

        //glen coded below
        P(lock_all_four_quadrant);
        if(cardirection == 0){//from north
            P(nw_2);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, west);
            message(REGION1, carnumber, cardirection, west);
            message(LEAVING, carnumber, cardirection, west);
            V(nw_2);
        }else if(cardirection == 1){//from east
            P(ne_1);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, north);
            message(REGION1, carnumber, cardirection, north);
            message(LEAVING, carnumber, cardirection, north);
            V(ne_1);
        }else if(cardirection == 2){//from south
            P(se_4);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, east);
            message(REGION1, carnumber, cardirection, east);
            message(LEAVING, carnumber, cardirection, east);
            V(se_4);
        }else if(cardirection == 3){//from west
            P(sw_3);
            V(lock_all_four_quadrant);
            message(APPROACHING, carnumber, cardirection, south);
            message(REGION1, carnumber, cardirection, south);
            message(LEAVING, carnumber, cardirection, south);
            V(sw_3);
        }
        //V(lock_all_four_quadrant);
        //glen coded above      

        (void) cardirection;
        (void) carnumber;
}


/*
 * approachintersection()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long carnumber: holds car id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createcars().  Each one must choose a direction
 *      randomly, approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 */
 
static
void
approachintersection(void * unusedpointer,
                     unsigned long carnumber)
{
        int cardirection;

        /*
         * Avoid unused variable and function warnings.
         */

        (void) unusedpointer;
        (void) carnumber;
        (void) gostraight;
        (void) turnleft;
        (void) turnright;

        /*
         * cardirection is set randomly.
         */

        cardirection = random() % 4; 
        //glen coded below
        // car direction is that the car approach from N = 0, E = 1, S = 2, W = 3
        
        int destination_direction = (random()+random())%3;
        //if destination_direction = 0, go straight
        //if destination_direction = 1, turn right
        //if destination_direction = 2, turn left

        if(destination_direction == 0){ gostraight(cardirection, carnumber);}
        else if(destination_direction == 1){ turnright(cardirection, carnumber);}
        else if(destination_direction == 2){ turnleft(cardirection, carnumber);}

        
        //glen coded above    
        
}


/*
 * createcars()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int
createcars(int nargs,
           char ** args)
{
        int index, error;
    
        //glen coded below
        int initial_semaphore_number = 1; //if the count is 1, then the semaphore is unlocked
        ne_1 =sem_create("ne_1", initial_semaphore_number);
        nw_2 =sem_create("nw_2", initial_semaphore_number);
        sw_3 =sem_create("sw_3", initial_semaphore_number);
        se_4 =sem_create("se_4", initial_semaphore_number);
        lock_all_four_quadrant = sem_create("lock_all_four_quadrant", initial_semaphore_number);
        //glen coded above


        /*
         * Start NCARS approachintersection() threads.
         */

        for (index = 0; index < NCARS; index++) {
                error = thread_fork("approachintersection thread",
                                    NULL, index, approachintersection, NULL);

                /*
                * panic() on error.
                */

                if (error) {         
                        panic("approachintersection: thread_fork failed: %s\n",
                              strerror(error));
                }
        }
        
        /*
         * wait until all other threads finish
         */

        while (thread_count() > 1)
                thread_yield();

	    (void)message;
        (void)nargs;
        (void)args;
        kprintf("stoplight test done\n");
        //glen coded below
        //kprintf("%d \n",random());
        //glen coded above
        
        return 0;
}

