/*
 * Synchronization primitives.
 * See synch.h for specifications of the functions.
 */

#include <types.h>
#include <lib.h>
#include <synch.h>
#include <thread.h>
#include <curthread.h>
#include <machine/spl.h>







////////////////////////////////////////////////////////////
//
// Semaphore.

struct semaphore *
sem_create(const char *namearg, int initial_count)
{
	struct semaphore *sem;

	assert(initial_count >= 0);

	sem = kmalloc(sizeof(struct semaphore));
	if (sem == NULL) {
		return NULL;
	}

	sem->name = kstrdup(namearg);
	if (sem->name == NULL) {
		kfree(sem);
		return NULL;
	}

	sem->count = initial_count;
	return sem;
}

void
sem_destroy(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);

	spl = splhigh();
	assert(thread_hassleepers(sem)==0);
	splx(spl);

	/*
	 * Note: while someone could theoretically start sleeping on
	 * the semaphore after the above test but before we free it,
	 * if they're going to do that, they can just as easily wait
	 * a bit and start sleeping on the semaphore after it's been
	 * freed. Consequently, there's not a whole lot of point in 
	 * including the kfrees in the splhigh block, so we don't.
	 */

	kfree(sem->name);
	kfree(sem);
}

void 
P(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);

	/*
	 * May not block in an interrupt handler.
	 *
	 * For robustness, always check, even if we can actually
	 * complete the P without blocking.
	 */
	assert(in_interrupt==0);

	spl = splhigh();
	while (sem->count==0) {
		thread_sleep(sem);
	}
	assert(sem->count>0);
	sem->count--;
	splx(spl);
}
//thread A currently runing, called p, thread B 
void
V(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);
	spl = splhigh();
	sem->count++;
	assert(sem->count>0);
	thread_wakeup(sem);
	splx(spl);
}

////////////////////////////////////////////////////////////
//
// Lock.

struct lock *
lock_create(const char *name)
{
	struct lock *lock;

	lock = kmalloc(sizeof(struct lock));
	if (lock == NULL) {
		return NULL;
	}

	lock->name = kstrdup(name);
	if (lock->name == NULL) {
		kfree(lock);
		return NULL;
	}
	
	// add stuff here as needed
    //glen code below
    lock->lecture_held = 0;
    //glen code above
	
	return lock;
}

void
lock_destroy(struct lock *lock)
{
	assert(lock != NULL);

	// add stuff here as needed
	
	kfree(lock->name);
	kfree(lock);
}

void
lock_acquire(struct lock *lock)
{
	// Write this
    //glen code below

	int spl;
	assert(lock != NULL);

	/*
	 * May not block in an interrupt handler.
	 *
	 * For robustness, always check, even if we can actually
	 * complete the P without blocking.
	 */
	//assert(in_interrupt==0);

	spl = splhigh();
	while (lock->lecture_held==1) {
		thread_sleep(lock);
	}
    lock->lecture_held = 1; 
	splx(spl);



    //interrupts_on();
/*   
    int lecture_spl; 
    lecture_spl = splhigh();//within this, this act like atomic instruction
    
    while(lock->lecture_held == 1){ ; }
    lock->lecture_held = 1;

    splx(lecture_spl);
    
*/
    //lock->lab2_lock = splhigh();//disable all the interrupts
    
    //glen code above    
	(void)lock;  // suppress warning until code gets written
}

void
lock_release(struct lock *lock)
{
	// Write this
    //glen code below
    //interrupts_off();
    int lecture_spl; 
    lecture_spl = splhigh(); //within this, this act like atomic instruction
    lock->lecture_held = 0;
	thread_wakeup(lock);
    splx(lecture_spl);

    //splx(lock->lab2_lock);
    //glen code above
	(void)lock;  // suppress warning until code gets written
}

int
lock_do_i_hold(struct lock *lock)
{
	// Write this
    //glen code below
    if(lock->lecture_held == 1){return 1;}
    else{return 0;}
    //return (curthread)
    //glen code above

	(void)lock;  // suppress warning until code gets written
    
	return 1;    // dummy until code gets written
}

////////////////////////////////////////////////////////////
//
// CV


struct cv *
cv_create(const char *name)
{
	struct cv *cv;

	cv = kmalloc(sizeof(struct cv));
	if (cv == NULL) {
		return NULL;
	}

	cv->name = kstrdup(name);
	if (cv->name==NULL) {
		kfree(cv);
		return NULL;
	}
	
	// add stuff here as needed
    //glen code below
    //cv->the_conditional_variable = 0;
    //glen code above
	
	return cv;
}

void
cv_destroy(struct cv *cv)
{
	assert(cv != NULL);

	// add stuff here as needed
	
	kfree(cv->name);
	kfree(cv);
}

void
cv_wait(struct cv *cv, struct lock *lock)
{
	// Write this

    //glen code below
    int lecture_spl = splhigh();
    lock_release(lock);
    thread_sleep(cv);    
    splx(lecture_spl); 
    //glen code above

	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
}

void
cv_signal(struct cv *cv, struct lock *lock)
{
	// Write this

    //glen code below
    int lecture_spl = splhigh();
    lock_acquire(lock);
    lab2_thread_wakeup_one_only(cv); 
    splx(lecture_spl);   
    //glen code above

	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
}

void
cv_broadcast(struct cv *cv, struct lock *lock)
{
	// Write this

    //glen code below
    int lecture_spl = splhigh();
    thread_wakeup(cv); 
    splx(lecture_spl);    
    //glen code above

	(void)cv;    // suppress warning until code gets written
	(void)lock;  // suppress warning until code gets written
}
