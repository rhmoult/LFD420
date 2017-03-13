#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

static int __init my_init(void)
{
  struct task_struct *p;
  char cmdline[1024];

  pr_info("Hello: module loaded at 0x%p\n", my_init);

  for_each_process(p) {
    pr_info("Process ID is %d\n", p->tgid);
    pr_info("State is %d\n", p->state);

    get_task_comm(cmdline, p);

    pr_info("Command line is %s\n", cmdline);

    pr_info("Stack canary is %lu\n", p->stack_canary);
  }
  
  return 0;
}

static void __exit my_exit(void)
{
  pr_info("Bye: module unloaded from 0x%p\n", my_exit);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_LICENSE("GPL v2");
