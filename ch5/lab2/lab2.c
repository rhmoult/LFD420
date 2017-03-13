#include <linux/module.h>
#include <linux/init.h>
#include <linux/utsname.h>

static int __init my_init(void)
{
  struct new_utsname* uname = init_utsname();
  pr_info("Hello: module loaded at 0x%p\n", my_init);
  pr_info(
           "%s %s %s %s\n",
           uname->sysname,
           uname->nodename,
           uname->release,
           uname->version);
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
