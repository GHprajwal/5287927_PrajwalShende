#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct Date {
    int day;
    int month;
    int year;
};

int isLeapYear(int y) {
    if (y % 400 == 0) return 1;
    if (y % 100 == 0) return 0;
    return (y % 4 == 0);
}

int getMonthDays(int m, int y) {
    int monthLen[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeapYear(y)) return 29;
    return monthLen[m - 1];
}

int dateLessOrEqual(struct Date a, struct Date b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day <= b.day;
}

void incrementDate(struct Date *d) {
    d->day++;
    if (d->day > getMonthDays(d->month, d->year)) {
        d->day = 1;
        d->month++;
        if (d->month > 12) {
            d->month = 1;
            d->year++;
        }
    }
}

int isLucky(struct Date d) {
    long num = (d.day * 100 + d.month) * 10000L + d.year;
    return (num % d.day == 0) || (num % d.month == 0);
}

int main(void) {
    struct Date start, end;
    scanf("%d-%d-%d", &start.day, &start.month, &start.year);
    scanf("%d-%d-%d", &end.day, &end.month, &end.year);

    int count = 0;
    struct Date current = start;

    while (dateLessOrEqual(current, end)) {
        if (isLucky(current)) {
            count++;
        }
        incrementDate(&current);
    }

    printf("%d\n", count);
    return 0;
}
