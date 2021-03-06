#ifndef _SCHED_H
#define _SCHED_H

#define THREAD_CPU_CONTEXT			0 		// offset of cpu_context in task_struct 

#ifndef __ASSEMBLER__

#define THREAD_SIZE				4096

// #define NR_TASKS				3			// we don't need more 

// #define FIRST_TASK task[0]				// we don't need more 
// #define LAST_TASK task[NR_TASKS-1]		// we don't need more 

#define TASK_RUNNING				0

extern struct task_struct *current;
extern struct task_struct *initial_task;			// we declare here as extern to be accessible from other files
//extern struct task_struct * task[NR_TASKS];		// we don't need more
//extern int nr_tasks;								// we don't need more

struct cpu_context {
	unsigned long x19;
	unsigned long x20;
	unsigned long x21;
	unsigned long x22;
	unsigned long x23;
	unsigned long x24;
	unsigned long x25;
	unsigned long x26;
	unsigned long x27;
	unsigned long x28;
	unsigned long fp;
	unsigned long sp;
	unsigned long pc;
};

// Change the structure task
struct task_struct {
	struct cpu_context cpu_context;
	long state;	
	long counter;
	long priority;
	long preempt_count;
	struct task_struct* next_task;					// point to the next task
};

extern void sched_init(void);
extern void schedule(void);
extern void timer_tick(void);
extern void preempt_disable(void);
extern void preempt_enable(void);
extern void switch_to(struct task_struct* next);
extern void cpu_switch_to(struct task_struct* prev, struct task_struct* next);

// Change the INIT_TASK adding 0
#define INIT_TASK \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	0,0,1, 0, 0 \
}

#endif
#endif
