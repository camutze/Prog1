#include <stdio.h>
void troca(float *p_a, float *p_b){
    float troca;
    troca= *p_a;
    *p_a=*p_b;
    *p_b=troca;

}
int main()
{
    float a=10, b=20;
    float *p_a, *p_b;
    p_a= &a;
    p_b = &b;
    printf("%2.f, %2.f\n",a, b);
    troca(p_a, p_b);
    printf("%2.f, %2.f\n",a, b);

    return 0;
}
