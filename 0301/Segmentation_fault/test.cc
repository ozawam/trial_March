#include <stdlib.h>
void
f1(p)
    char *p;
{
    int     i;

    for (i = 0; i < 4096; i++)
        *(p + i) = 1;
}


void
main()
{
    char    *p;

    while (1) {
        if ((p = (char *)malloc(4096)) != NULL)
            f1(p);
    }
}
