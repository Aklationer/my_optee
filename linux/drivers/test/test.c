#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>

#define IOC_MAGIC '\x66'
#define PLUSONE_IOC_ADDONE _IOWR(IOC_MAGIC, 0, int)
#define DRIVER_NAME "test"

static struct cdev test_cdev;
static dev_t dev;
static struct class  *test_class;

static int test_open(struct inode *inode, struct file *file){

     pr_info("device open\n");
     return 0;

}

static int test_release(struct inode *inode, struct file *file){

    pr_info("device close\n");
    return 0;

}


static long test_ioctl(struct file *filp, unsigned int cmd,unsigned long arg){
    int data;

    switch(cmd){
        case PLUSONE_IOC_ADDONE:
            if(copy_from_user(&data,(void __user *)arg,sizeof(int))){
                return -1;
            }
            data++;
            if(copy_to_user((void __user*)arg,&data,sizeof(int))){
                return -1;
            }
            break;
        default:
            return -1;
    }
    return 0;
}

static struct file_operations fops = {
    .open = test_open,
    .release = test_release,
    .unlocked_ioctl = test_ioctl,
};

static int __init init(void){

    int alloc_ret = -1;
    int cdev_ret = -1;
    alloc_ret = alloc_chrdev_region(&dev,0,1,DRIVER_NAME);

    if(alloc_ret)
        goto error;
    
    cdev_init(&test_cdev,&fops);
    cdev_ret = cdev_add(&test_cdev,dev,1);

    if (cdev_ret)
        goto error;

    test_class = class_create("test");
    device_create(test_class, NULL, dev, NULL, DRIVER_NAME);

    return 0;

    error:
        if (cdev_ret == 0)
            cdev_del(&test_cdev);
        if(alloc_ret == 0)
            unregister_chrdev_region(dev,1);
        return -1;
}

static void __exit exit(void){

    device_destroy(test_class, dev);
    class_destroy(test_class);
    cdev_del(&test_cdev);
    unregister_chrdev_region(dev, 1);

}

module_init(init);
module_exit(exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This is test module");