#define LENGTH 1024


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
