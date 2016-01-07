#include <stdlib.h>
#include <time.h>

struct test {int a;int b;};

int access_counter;                        /* Obfuscated code */
int access_array[4] = { 0, 1, 0, 1, };
int *address_array[2];
int rand_a_b(int M, int N) {
    return M + rand() / (RAND_MAX / (N - M + 1) + 1);
}  /* Returns an int in [a;b] */


int *access(){
    int nb_elem = 2, id1, id2, t, *ptr;
    id2 = rand_a_b(0, nb_elem - 1);
    id1 = rand_a_b(0, nb_elem - 1);
    t = **(address_array + id1);
    **(address_array + id1) = **(address_array + id2);
    **(address_array + id2) = t;
    ptr = *(address_array + id1);
    *(address_array + id1) = *(address_array + id2);
    *(address_array + id2) = ptr;
    access_counter = access_counter + 1;
    return *(address_array + *(access_array + (access_counter-1)));
}

int main(void) {
    srand(time(NULL));
    struct test t;
    int c;
    access_counter = 0;
    *(address_array + 1) = &t.b;
    *(address_array + 0) = &t.a;
    *access()= 10;
    *access()= 20;
    c = *access();
    return (c + *access());
}
