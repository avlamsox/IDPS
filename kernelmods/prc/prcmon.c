
/* proc_example.c
 * Author: Kiran Kankipati
 * Updated: 22-feb-2017
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/module.h> 
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>  
#include <linux/udp.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/net.h>
#include <linux/netdevice.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/inet.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/if_arp.h>
#include <linux/icmp.h>
#include <linux/proc_fs.h>
#include <linux/netlink.h>
#include <linux/mroute.h>
#include <net/checksum.h>
#include <net/inet_ecn.h>
#include <net/xfrm.h>
#include <net/route.h>
#include <net/sock.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/arp.h>
#include <net/udp.h>
#include <net/icmp.h>
#include <net/inetpeer.h>
#include <net/protocol.h>
#include <net/flow.h>
#include <asm/types.h>

struct proc_dir_entry *tlc_proc_a;

int abc=100;

#define PROCFS_MAX_SIZE 30
char proc_buf[PROCFS_MAX_SIZE];

static ssize_t tlc_proc_a_write(struct file *fp, const char *buf, size_t len, loff_t * off)
{	if(len > PROCFS_MAX_SIZE) { return -EFAULT; }
   if(copy_from_user(proc_buf, buf, len)) { return -EFAULT; }

	abc=simple_strtoul(proc_buf,NULL,10);
	return len;
}

void procs_info_print(void)
{
        struct task_struct* task_list;
        size_t process_counter = 0;
        for_each_process(task_list) {
                pr_info("== %s [%d] and State = [%ld]\n", task_list->comm, task_list->pid, task_list->state);
                ++process_counter;
        }
        printk(KERN_INFO "== Number of process: %zu\n", process_counter);
}

static ssize_t tlc_proc_a_read(struct file *fp, char *buf, size_t len, loff_t * off)
{	static int finished=0; if(finished) {finished=0;return 0;} finished=1;
	
	sprintf(buf, "abc: %d\n", abc);
	procs_info_print();
	return strlen(buf);
}

/*static ssize_t tlc_proc_a_read(struct file *fp, char *buf, size_t len, loff_t * off)
{	static int finished=0; if(finished) {finished=0;return 0;} finished=1;
	//int abc=100;
	strcpy(buf, "Linux proc entry\n");
	//strcpy(buf, "abc: %d\n", abc);
	//sprintf(buf, "abc: %d\n", abc);
//	memset(buf,0xaa,10);
	return strlen(buf);
	//return 10;
}*/

static long prcmon_ioctl (struct file *filp, unsigned int cmd, unsigned long arg) {
	
	switch(cmd) {
	
	case PRCMON_GET_PROC:

	case PRCMON_REFRESH_TL:

	case default:

	return 0;
}

static int prcmon_open (struct inode *inode, struct file *filp){
	int count = 0;
	//Refresh process list
	return count++;	
}

static struct file_operations tlc_proc_a_fops = { .owner=THIS_MODULE, .read=tlc_proc_a_read, .write=tlc_proc_a_write, .unlocked_ioctl=prcmon_ioctl, .open=prcmon_open, };

static int prc_init(void)
{
	/*Register Procfs Entry*/
 	tlc_proc_a = proc_create( "tlc_proc_a", 0444, NULL, &tlc_proc_a_fops); 
 	if(tlc_proc_a==NULL) {	printk(KERN_ALERT "Error: Could not initialize %s\n", "tlc_proc_a"); }

	/*Setup IOCTL Interface*/
	
	return 0;
}

static void prc_exit(void) 
{  remove_proc_entry("tlc_proc_a", NULL);
}

module_init(prc_init);
module_exit(prc_exit);
