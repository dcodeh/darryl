// test2.c
// @author dcodeh
// 
// Yet another demonstration of how darryl can be used
// 
// Usage: ./test2 a b p q n
// where a, b, p, and q are a mpz_t's (gmp integers)
// see main() for details...
//
// Calculates lucas numbers using a String array to store the
// intermediate results. This DEFINITELY is not the most efficient way to
// do this. If you are really trying to implement something like this,
// please just make an array of mpz_t's and do that.
// 
// ////////////////////////////////////////////////////////////////////////
#include "darryl.h" // obvious reasons
#include <stdlib.h> // atoi
#include <stdio.h> // for printfing
#include <gmp.h> // for Big Integers
#include <stdbool.h> // for bools

#define BASE 10

/**
  * This is a very simple cleanup function that I define for whatever data
  * I slap into darryl. A pointer to this function is passed in on creation,
  * so darryl handles the deallocation of all of the data on destruction
  * to ideally prevent leaks. Obviously, if you write a bad cleanup
  * function you could still have a leaky program.
  */
void cleanup(char * ptr) {
    // this is a very simple example for freeing char pointers
    free(ptr);

    // you could add more complicated things here depending on the type
    // of data you're using darryl for

    // Here's some pseudo code for example
    // calculate pi
    // cast pi to an int
    // ...
    // free the first (int) pi pointers in an array
    // free the pointer to the pointer
    // ...
}

/**
  * Calculates lucas numbers based on the following formula:
  * U_a,b,p,q(0) = a
  * U_a,b,p,q(1) = b
  * U_a,b,p,q(n) = p( U(n-1) ) - q( U(n-2) )
  * 
  * Usage: $ lucas a b p q n
  * a, b, p, and q must be base 10 integers, and n must be an int
  */
int main(int argc, char ** argv) {

    if(argc != 6) {
        // bail out if the user is stupid, and enters the wrong arguments
        printf("Usage: $ ./test2 a b p q n\n");
        return EXIT_FAILURE;
        // Don't take it personally, I didn't mean to hurt your feelings...
    }

    // initialize and create all of the Big Integers, and n
    mpz_t a, b, p, q;
    bool valid = true; // give the wetware the benefit of the doubt
    valid &= (mpz_init_set_str(a, argv[1], BASE) == 0);
    valid &= (mpz_init_set_str(b, argv[2], BASE) == 0);
    valid &= (mpz_init_set_str(p, argv[3], BASE) == 0);
    valid &= (mpz_init_set_str(q, argv[4], BASE) == 0);
    int n = atoi(argv[5]);

    if(!valid) {
        printf("Check your arguments to make sure they are valid numbers\n");
        return EXIT_FAILURE;
    }

    // it's a cat because I gave it a self-cleaning function pointer
    Darryl d = create_darryl_cat(cleanup);

    // calculates lucas numbers using a calculation array
    mpz_t n1, pn1, n2, qn2, final_result;
    for(int i = 0; i <= n; ++i) {
        char * result_str = NULL;
        switch(i) {
            case 0:
                // just put the a parameter in the first index of the array
                result_str = mpz_get_str(result_str, BASE, a);
                break;
            case 1:
                // put the b parameter in the second index of the array
                result_str = mpz_get_str(result_str, BASE, b);
                break;

            default:
                // calculate the intermediate value for this index based
                // on n-1 and n-2

                // read in the n-1 and n-2 value strings into mpg integers
                mpz_init_set_str(n1, (char *) get(d, i - 1), BASE);
                mpz_init_set_str(n2, (char *) get(d, i - 2), BASE);
                mpz_init(p1); // just pretend that there's a minus (p-1)
                mpz_init(qn2); // I would use a minus in the name if I could
                mpz_init(final_result);

                // p * n-1
                mpz_mul(pn1, p, n1);

                // q * n-2
                mpz_mul(qn2, q, n2);

                // (p * n-1) - (q * n-2)
                mpz_sub(final_result, pn1, qn2);

                result_str = mpz_get_str(result_str, BASE, final_result);

                mpz_clears(n1, pn1, n2, qn2, final_result, NULL); // null term
                break;
        }
        add_at(d, i, result_str); // throw it darryl
    }

    // print the result
    printf("%s\n", (char *) get(d, n));

    // all of the stored mpz_t pointers will be cleared by the cleanup function
    // passed in at construction time
    destroy_darryl(d);
    mpz_clears(a, b, p, q, NULL);
    return EXIT_SUCCESS;
}
