#include <zephyr.h>
#include <sys/printk.h>

void main(void) {
  printk("hello, world! %s", CONFIG_BOARD);
}
