struct test {int a;int b;};

int main (void){  /* Initial example program */
    struct test t;
    int c;
    t.a =10;
    t.b =20;
    c = t.a;
    return c + t.b;
}
