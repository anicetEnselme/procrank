#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/mm.h>
#include <linux/poll.h>

/*
	
*/

static int procinfo_proc_show(struct seq_file *m, void *v)
{
	struct task_struct *p; 
	int nr_process = 0;
	int test = 0;

	//test = emery();
	for_each_process(p) // Traverse all processes
	{	

		struct vm_area_struct *vma;
		u64 pss;
		
		printk(KERN_INFO "Iteration \"%d\" \n", test);
		seq_printf(m, "Process_NAME: %s 		 ===> PID: %u\n", p->comm, p->pid);	// print PID
        printk(KERN_INFO "I am here");
        if(p->mm)
		for (vma = p->mm->mmap; vma ; vma = vma->vm_next)
		{
			printk(KERN_INFO "I am here 2 ");
			pss = gather_procrank(vma);
			printk(KERN_INFO "I am here 3");
			seq_printf(m, "PSS : %lld ", pss);
			printk(KERN_INFO "Je suis apres le seq_printf");
		}
		printk(KERN_INFO "I am here4");

		nr_process += 1;					
	}
	seq_printf(m, "number of process: %d\n", nr_process);	// print number of process
	/////////////////////////

	return 0;
}

static int __init procrank_init(void)
{
	proc_create_single("procrank", 0, NULL, procinfo_proc_show); // create proc file
    printk("Welcome Anicet\n");
	return 0;
}

static void __exit procrank_exit(void)
{
	remove_proc_entry("procrank", NULL);	// delete proc file
	printk("Good bye Anicet!\n");
}

module_init(procrank_init);
module_exit(procrank_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("procrank module");
MODULE_AUTHOR("Enselme AGUIDIGODO");


