#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 10e-13
#define OPTIONS "sctea"
#define pi acos(-1)

double my_sin(double x);
double my_cos(double x);
double my_tan(double x);
double my_exp(double x);
// return sin, cos, tan, and exp value
int print_sin(void);
int print_cos(void);
int print_tan(void);
int print_exp(void);
// print the value in specific foramt
int main(int argc, char **argv) {

  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 's':
      print_sin();
      break;
    case 'c':
      print_cos();
      break;
    case 't':
      print_tan();
      break;
    case 'e':
      print_exp();
      break;
    case 'a':
      print_sin();
      print_cos();
      print_tan();
      print_exp();
      break;
    }
  }
  return 0;
}
double my_sin(double x) {
  return (x * ((x * x * (52785432 - 479249 * x * x) - 1640635920) * x * x +
               11511339840)) /
         (((18361 * x * x + 3177720) * x * x + 277920720) * x * x +
          11511339840);
}
double my_cos(double x) {
  return ((x * x * (1075032 - 14615 * x * x) - 18471600) * x * x + 39251520) /
         (((127 * x * x + 16632) * x * x + 1154160) * x * x + 39251520);
}
double my_tan(double x) {
  return (x * ((((x * x - 990) * x * x + 135135) * x * x - 4729725) * x * x +
               34459425)) /
         (45 * ((((x * x - 308) * x * x + 21021) * x * x - 360360) * x * x +
                765765));
}
double my_exp(double x) {
  double result = 1;
  double n = 1;
  double t = 1;
  while (t > EPSILON) {
    t *= x / n;
    result += t;
    n += 1;
  }
  return result;
}
int print_sin(void) {
  double x;
  printf("x\tSin\t\tLibrary\t\tDifference\n");
  printf("-\t---\t\t-------\t\t----------\n");
  for (x = -2 * pi; x <= 2 * pi; x += (pi / 16.0)) {
    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, my_sin(x), sin(x),
           my_sin(x) - sin(x));
  }
  return 0;
}
int print_cos(void) {
  double x;
  printf("x\tCos\t\tLibrary\t\tDifference\n");
  printf("-\t---\t\t-------\t\t----------\n");
  for (x = -2 * pi; x <= 2 * pi; x += (pi / 16.0)) {
    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, my_cos(x), cos(x),
           my_cos(x) - cos(x));
  }
  return 0;
}
int print_tan(void) {
  double x;
  printf("x\tTan\t\tLibrary\t\tDifference\n");
  printf("-\t---\t\t-------\t\t----------\n");
  for (x = pi / (-3.0); x <= pi / 3.0; x += (pi / 16.0)) {
    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, my_tan(x), tan(x),
           my_tan(x) - tan(x));
  }
  return 0;
}
int print_exp(void) {
  double x;
  printf("x\tExp\t\tLibrary\t\tDifference\n");
  printf("-\t---\t\t-------\t\t----------\n");
  for (x = 0; x <= 9; x += 0.1) {
    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, my_exp(x), exp(x),
           my_exp(x) - exp(x));
  }
  return 0;
}
