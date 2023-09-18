/*In this experiment, we have one victim main thread and one victim encryption thread having AES 192*/

#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include <time.h>
#include <sys/printk.h>
#include <timing/timing.h>
#include "aes.c"




void main(void)
{

// start the encryption function as a seperate thread
K_THREAD_DEFINE(my_victim_thread, MY_STACK_SIZE,
                Cipher, &state, &RoundKey,
                MY_PRIORITY, 0, 0);

  k_thread_start(my_victim_thread);

return 0;
}
