int main() {
    int i, j, *p, *q;
    i = 5;
    p = &i;
    *p = 7;
    j = 3;
    p = &j;
    q = p;
    p = &i;
    *q = 2;
    return 0;
}