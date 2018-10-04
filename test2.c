// test2.c
// @author dcodeh
// 
// Yet another demonstration of how darryl works
// /////////////////////////////////////////////////////
#include "darryl.h" // obvious reasons
#include <stdlib.h> // atoi
#include <stdio.h> // for printfing
#include <gmp.h> // for Big Integers
#include <stdbool.h> // for bools

#define BASE 10

void cleanup(char * ptr) {
    free(ptr);
}

/**
  * Calculates lucas numbers based on the following formula:
  * U_a,b,p,q(0) = a
  * U_a,b,p,q(1) = b
  * U_a,b,p,q(n) = p( U(n-1) ) - q( U(n-2) )
  * 
  * Usage: $ lucas a b p q n
  * a, b, p, and q must be base 10 integers, and n must be an int >= 0
  */
int main(int argc, char ** argv) {

    if(argc != 6) {
        // bail out if the user is stupid, and enters the wrong arguments
        printf("Usage: $ ./lucas a b p q n\n");
        return EXIT_FAILURE;
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

    Darryl d = create_darryl_cat(cleanup);
    printf("Darryl created\n");
    printf("   size: %d\n", get_allocated_size(d));

    // calculates lucas numbers using a calculation array
    mpz_t n1, pn1, n2, qn2, final_result;
    for(int i = 0; i <= n; ++i) {
        char * result_str = NULL;
        switch(i) {
            case 0:
                result_str = mpz_get_str(result_str, BASE, a);
                break;
            case 1:
                result_str = mpz_get_str(result_str, BASE, b);
                break;

            default:
                mpz_init_set_str(n1, (char *) get(d, i - 1), BASE);
                mpz_init_set_str(n2, (char *) get(d, i - 2), BASE);
                mpz_init(pn1);
                mpz_init(qn2);
                mpz_init(final_result);
                mpz_mul(pn1, p, n1);
                mpz_mul(qn2, q, n2);
                mpz_sub(final_result, pn1, qn2);

                result_str = mpz_get_str(result_str, BASE, final_result);

                mpz_clears(n1, pn1, n2, qn2, final_result, NULL);
                break;
        }
        add_at(d, i, result_str);
    }

    printf("%s\n", (char *) get(d, n));

    // all of the stored mpz_t pointers will be cleared by the cleanup function
    // passed in at construction time
    destroy_darryl(d);
    mpz_clears(a, b, p, q, NULL);
    return EXIT_SUCCESS;
}
