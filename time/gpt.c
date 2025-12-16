
#include <time.h>
#include <stdio.h>

int main(void) {
    tzset();

    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    struct tm *gt = gmtime(&t);

    printf("local: %02d:%02d\n", lt->tm_hour, lt->tm_min);
    printf("  utc: %02d:%02d\n", gt->tm_hour, gt->tm_min);

#ifdef __USE_BSD
    printf("gmtoff = %ld\n", lt->tm_gmtoff);
#endif
}
