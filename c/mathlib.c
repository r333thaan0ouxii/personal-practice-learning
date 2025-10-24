#include "mathlib.h"

double add(int a, int b) {
    return a + b;
}
double sub(int a, int b){
    return a - b;
}
double mult(int a, int b){
    return a * b;
}
double div(int a, int b){
    if (b == 0) {return 0.0;}
    return (double)a / (double)b;
}
