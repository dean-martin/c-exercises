// Exercise 5-9.
// Rewrite the routines of day_of_year and mon_day with
// pointers instead of indexing.
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    p = daytab[leap];
    while (month--)
        day += *++p;
    return day;
}

// month_day:   set month, day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    p = daytab[leap];
    while (yearday > *++p)
        yearday -= *p;
    *pmonth = p - *(daytab + leap);
    *pday = yearday;
}

int main()
{
    int month;
    int day;
    month_day(1988, 60, &month, &day); // 2/29
    printf("%i/%i\n", month, day);
    printf("%i\n", day_of_year(2024, 2, 4));

    month_day(1989, 365, &month, &day); // 2/29
    printf("%i/%i\n", month, day);
    printf("%i\n", day_of_year(1, 5, 3));

    printf("%i\n", **(daytab+1));
}
