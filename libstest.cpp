#include "mbed.h"
#include "libstest_lib.h"
libstest_lib libs(45);

int main(void)
{
    while (1)
    {
        libs.updateAllState(Auto);
    }
}