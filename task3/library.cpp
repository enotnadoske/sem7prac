#include "library.h"

#include <iostream>

double get_root(double start_point, int iteration, double step, TFunction* func){
    double res,cur_point = start_point;
    for(int i = 0; i < iteration; i++){
        cur_point = cur_point - step*((abs((*func)(cur_point + FLT_EPSILON)) - abs((*func)(cur_point - FLT_EPSILON)))/(2* FLT_EPSILON));
    }
    return cur_point;
}

void hello() {
    std::cout << "Hello, World!" << std::endl;
}
