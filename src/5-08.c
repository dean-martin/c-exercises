// Exercise 5-8.
// There is no error checking in day_or_year or month_day.
// Remedy this defect.
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > daytab[leap][month])
        return -1;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

// month_day:   set month, day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (year < 1) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    if (i > 12 && yearday > daytab[leap][12]) {
        *pmonth = -1;
        *pday = -1;
        return;
    } else {
        *pmonth = i;
        *pday = yearday;
    }
}

int main()
{
    int month;
    int day;
    month_day(1988, 60, &month, &day); // 2/29
    printf("%i/%i\n", month, day);
    printf("%i\n", day_of_year(2024, 2, 4));

    month_day(1989, 366, &month, &day); // 2/29
    printf("%i/%i\n", month, day);
    printf("%i\n", day_of_year(1, 5, 3));
}
