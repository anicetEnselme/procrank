#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/mm.h>
//#include <linux/poll.h>

//#include "internal.h"

#define PSS_SHIFT 12

/*
	
*/

static int procinfo_proc_show(struct seq_file *m, void *v)
{
	struct task_struct *p; 
	struct vm_area_struct *vma;
	struct mem_size_stats mss;
	unsigned long vss, uss, shared;
	u64 pss;
	int nr_process = 0;
	shared=0;

	//int test = 0;

	//test = emery();
	seq_printf(m, "-------------------------------------------------------------------\n");
	seq_printf(m, "%5s %17s %10s %10s %10s %10s\n", "PID", " | Process_NAME", " | VSS", " | RSS", " | USS", " | PSS"); 
	seq_printf(m, "-------------------------------------------------------------------\n");	
	for_each_process(p) // Traverse all processes
	{	
		
		memset(&mss, 0, sizeof(mss));
		printk(KERN_INFO "Iteration \"%d\" \n", nr_process);
        printk(KERN_INFO "I am here");
        /*if (nr_process == 1)
        {
        	break;
        }*/
       // seq_printf(m, "NAME: %s, PID: %u", p->comm, p->pid);	// print PID

        vss=0, uss=0, pss=0;

        if(p->mm){
        //seq_printf(m, "VSS: %ld", p->mm->mmap->vm_end - p->mm->mmap->vm_start);	// print PID
			for (vma = p->mm->mmap; vma ; vma = vma->vm_next)
			{
				smap_gather_stats(vma, &mss);
				vss += (vma->vm_end - vma->vm_start);
				//seq_printf(m, " PSS : %lld, rss: %ld", mss.my_pss, mss.rss);
			}
			//printk(KERN_INFO "I am here4");
			//seq_printf(m, "\n");	// print PID
			//seq_printf(m, " PSS : %lld \n", mss.my_pss);
			shared = mss.shared_clean + mss.shared_dirty;
			uss = mss.resident - shared;
			pss = mss.pss>>PSS_SHIFT;

			seq_printf(m, "%5d | %17s | %10ld | %10ld | %10ld | %10lld \n", p->pid, p->comm, vss>>10, mss.resident>>10, uss>>10, pss>>10; 
			// seq_put_decimal_ull_width(m,"%10ldK",vss>>(PAGE_SHIFT-10),8);
			// seq_put_decimal_ull_width(m," %10ldK",mss.rss>>(PAME_SHIFT-10),8);
			// seq_put_decimal_ull_width(m,"%10dK", 0,8);
			// seq_put_decimal_ull_width(m,"%10lldK \n",pss>>(PAGE_SHIFT-10),8);
			nr_process += 1;					
		}

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


