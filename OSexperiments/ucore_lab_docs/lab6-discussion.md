> 设a=b，最大步进为s，当b+s不溢出时，a < b+s，那么 s为正数即可，即 s > 0 && s<2^31；当b+s溢出时，B+S>=2^32，溢出后的B'=B+S-2^32，此时为了使a-b<0,得A>=B+S-2^32+2^31=B+S-2^31，所以S<=2^31,综上，s<2^31.

```C
#include <stdio.h>
#include <cstdint>
#include <cmath>

const uint8_t BIG_STRIDE = 0x7e;

int main() {
    uint8_t a = 0xfe,b = 0xfe;
    uint8_t a_h = 0x1, b_h = 0x2;
    for(int i=0;i < 16; i++){
        uint8_t tmp = a-b;
        if( ((tmp>>7) & 1) && (tmp & 0x7f)){
            printf("Run a:%x\n", a);
            a += a_h;
        }
        else {
            printf("Run b:%x\n", b);
            b += b_h;

        }
    }
    /*int x= 0x7fffffff;
    printf("%d ",x);
    printf("%d ", (int)pow(2, 30));
    x += 0x1;
    printf("%d\n",x);
    return 0;*/
}
```
