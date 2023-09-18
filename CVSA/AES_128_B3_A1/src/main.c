/*In this experiment, we have one victim main thread , one victim encryption thread having AES 128, one benchmark thread and one attacker thread*/

#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include <time.h>
#include <sys/printk.h>
#include <timing/timing.h>
#include "aes.c"
#include "cubic.c"
#include "basicmath_small.c"
#include "attack.c"





void main(void)
{
double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
      double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
      double  x1[3],x2[3];
      int     solutions1,solutions2;
      
// start the encryption function as a seperate thread
K_THREAD_DEFINE(my_victim_thread, MY_STACK_SIZE,
                Cipher, &state, &RoundKey, NULL,
                MY_PRIORITY, 0, 0);
K_THREAD_DEFINE(my_benchmark1_thread1, MY_STACK_SIZE,
                do_basicmath_small,NULL,NULL,NULL,
                MY_PRIORITY, 0, 0);
    // Encrypt the message
    k_thread_start(my_victim_thread);
    k_thread_start(my_benchmark1_thread1);
        k_thread_start(attack_thread);                       

return 0;
}
