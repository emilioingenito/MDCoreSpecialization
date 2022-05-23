#include <stdio.h>
#include <stdlib.h>
//function used to print a float as an int
void print_float(double f){
    double y_float;
    double small_float;
    double y_cut;
    int small_int;
    int y_int;

    y_int = (int) f; 
    y_float = f;
    y_cut = (double) y_int;
    small_float = y_float - y_int;
    small_float = small_float * 100;
    small_int = (int) small_float;
    printf("%d.%d", y_int, abs(small_int));
}