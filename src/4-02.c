// Exercise 4-2.
// Extend atof to handle scientific notation of the form 
// 123.45e-6
// where a floating-point number may be followed by e or E and an optionally
// signed exponent.
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

double atof(char s[]);

int main()
{
    printf("%f\n", atof("-123.56"));
    printf("%f\n", atof("+54"));
    printf("%f\n", atof("1e1"));
    printf("%f\n", atof("1E1"));
    printf("%f\n", 1E1);
    assert(atof("1E10") == 1E10);
    printf("%f\n", atof("-2.14E1"));
    printf("%f\n", -2.14E+1);
    printf("%f\n", -2.14E1);
    assert(atof("2.14e10") == 2.14e10);
    printf("%f\n", -2.14E1);
    printf("%f\n", atof("21.4e-1"));
    printf("%f\n", atof("214e-2"));
    printf("%f\n", atof("123.45e-6"));
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (toupper(s[i]) == 'E')
        i++;
    int esign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    int exponent = 0;
    for (; isdigit(s[i]); i++) {
        exponent = 10.0 * exponent + (s[i] - '0');
    }
    return (sign * val / power) * pow(10, exponent*esign);
}

/* atof: convert string s to double */
double _atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}
