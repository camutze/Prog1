#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i, j, k, l;
    printf("Digite K:\n");
    scanf("%d", &k);

    l = 0;
    i = 1;
    while (l <= k)
    {
        j = k - 1;

        while (!j)
        {
            if (i % j != 0)
                break;
            j--;
        }
        if (!j)
        {
            printf("%d", i);
            l++;
        }
        i++;
        return 0;
    }
}
