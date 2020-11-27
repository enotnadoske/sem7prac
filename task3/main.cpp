//
// Created by enotnadoske on 26.11.2020.
#include <iostream>
#include "library.h"
#include <gtest/gtest.h>
//#include <gtest/gmock.h>
using namespace std;
//int main(){
//
//
//    Factory fact;
//    auto ff = fact.CreateObject(string("polynomial"), {-2,0,1});
//    auto ii = fact.CreateObject(string("const"), {2});
//    auto pp = (ii) + (ff);
//    cout << (*pp)(1);
//}

int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
