/*In this experiment, we have one victim main thread, one victim encryption thread having RSA 512, one benchmark code*/

//Headers
#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include <time.h>
#include <sys/printk.h>
#include <timing/timing.h>
#include "cubic.c"
#define LENGTH 512
#define MY_STACK_SIZE 500
#define MY_PRIORITY 5
#define BUFFER_SIZE 1024
#define SENSITIVE __attribute__((section(".secret")))

//Encryption function that will be bound to a thread
void encrypt(const char* message, int message_len, char* publicKey, unsigned long long modulus, unsigned long long* encryptedMessage) {
    for (int i = 0; i < message_len; ++i) {
        unsigned long long m = message[i];
        unsigned long long c = modExp(m, publicKey, modulus);
        encryptedMessage[i] = c;
    }
}


//Annotate the sensitive section
unsigned long long SENSITIVE modExp(unsigned long long base, char* exponent, unsigned long long modulus) {
    unsigned long long result = 1;
   for(int i=0; i< LENGTH ; i++){
        if (exponent[i] & 1) {
            result = (result * base) % modulus;
        }

        base = (base * base) % modulus;
    }

    return result;
}





//main function present in victim main code as there is only one victim code in this experiment
void main(void)
{
    const unsigned long long p = 17; // Choose two prime numbers p and q
    const unsigned long long q = 19;
    char publicKey[LENGTH]; // Choose a public key
    const unsigned long long modulus = p * q; // Calculate modulus n
    double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
      double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
      double  x1[3],x2[3];
      int     solutions1,solutions2;
    srand(time(0));
    //generate key
    for (int i = 0; i < LENGTH; i++) {
        publicKey[i] = (rand() % 2) ? '1' : '0';
    }


    const char* message = "Hello, RSA dear!";
    size_t message_len = strlen(message);

    if (message_len >= BUFFER_SIZE) {
        printf("Error: Input message is too large!\n");
        return 1;
    }

    unsigned long long* encryptedMessage = (unsigned long long*)malloc(message_len * sizeof(unsigned long long));
//Thread of victim that does secret code execution
K_THREAD_DEFINE(my_victim_thread, MY_STACK_SIZE,
                encrypt, message, message_len, publicKey, modulus, encryptedMessage,
                MY_PRIORITY, 0, 0);
//thread of benchmark code
K_THREAD_DEFINE(my_benchmark1_thread1, MY_STACK_SIZE,
                SolveCubic, a1, b1, c1, d1, &solutions1,x1,
                MY_PRIORITY, 0, 0);
    // Encrypt the message
    k_thread_start(my_victim_thread);
    k_thread_start(my_benchmark1_thread1);

    // Print the encrypted message
    printf("Encrypted message: ");
    for (size_t i = 0; i < message_len; ++i) {
        printf("%llu ", encryptedMessage[i]);
    }
    
    //printf("\n");
  //  printf("Address of modExp: %p\n",modExp);
//	k_thread_join(my_victim_thread, K_FOREVER);

//	k_thread_runtime_stats_t my_victim_thread;

//	k_thread_runtime_stats_get(k_current_get(), &my_victim_thread);
//	printk("Victim Cycles: %llu\n and Attacking Cycles: %llu\n", my_victim_thread.execution_cycles);

	
//	printk("Namaste %s\n", CONFIG_BOARD);
	//timing_stop();
	return 0;
	
}
