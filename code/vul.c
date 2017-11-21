#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);
static loff_t dev_llseek(struct file *, loff_t, int);
static long dev_ioctl(struct file *, unsigned int, unsigned long);

static struct file_operations dev_fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .release = dev_release,
    .read = dev_read,
    .write = dev_write,
    .llseek = dev_llseek,
    .unlocked_ioctl = dev_ioctl,
};

static struct miscdevice dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "vul",
    .fops = &dev_fops,
    .mode = S_IRUGO | S_IWUGO,
};

static int __init mod_init(void)
{
    int ret = misc_register(&dev);

    if (ret < 0) {
        printk(KERN_INFO "vul: misc_register() = %d\n", ret);
        return ret;
    }
    printk(KERN_INFO "vul: init\n");
    
    return ret;
}

static void __exit mod_exit(void)
{
    misc_deregister(&dev);
    printk(KERN_INFO "vul: exit\n");
}

module_init(mod_init);
module_exit(mod_exit);

static int dev_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int dev_release(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t dev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    return 0;
}

static ssize_t dev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    long stack[2];
    long *pstack = stack;

    copy_from_user(pstack, buf, count);
    pstack[pstack[0]] = pstack[1];

    printk(KERN_INFO "vul: dev_write()\n");
    printk(KERN_INFO "vul: stack[0] = 0x%lx\n", pstack[0]);
    printk(KERN_INFO "vul: stack[1] = 0x%lx\n", pstack[1]);
    printk(KERN_INFO "vul: stack[2] = 0x%lx\n", pstack[2]);
    printk(KERN_INFO "vul: stack[3] = 0x%lx\n", pstack[3]);
    printk(KERN_INFO "vul: stack[4] = 0x%lx\n", pstack[4]);
    printk(KERN_INFO "vul: stack[5] = 0x%lx\n", pstack[5]);
    printk(KERN_INFO "vul: stack[6] = 0x%lx\n", pstack[6]);
    
    return 0;
}

static loff_t dev_llseek(struct file *file, loff_t offset, int whence)
{
    return 0;
}

static long dev_ioctl(struct file *file, unsigned int request, unsigned long param)
{
    return 0;
}

