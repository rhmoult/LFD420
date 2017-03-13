#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/atomic.h>
#include <linux/slab.h>

static LIST_HEAD(duck_list);

struct duck_entry{
  char name[20];
  int sequence_number;
  struct list_head dlist;
};

static int __init my_init(void)
{
  struct duck_entry *mrducks;

  int i;

  for (i = 0;i < 5; i++) {
    mrducks = kmalloc(sizeof(struct duck_entry), GFP_KERNEL);
    if(!mrducks) {
      pr_info(" No memory for ducks!\n");
      return -ENOMEM;
    }
    mrducks->sequence_number = i;
    sprintf(mrducks->name, "My_%d", i + 1);
    list_add(&mrducks->dlist, &duck_list); 
  }
  return 0;
}

static void walk_list(void) {
  int i = 0;
  struct list_head *l;
 
  if (list_empty(&duck_list))
    return 0;

  list_for_each(l, &duck_list) {
    struct duck_entry *me = list_entry(l, struct duck_entry, dlist);
    pr_info("%s", &me->name);
  }

  return;
}

static void __exit my_exit(void)
{
  walk_list();
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_LICENSE("GPL v2");
