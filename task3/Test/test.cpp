//
// Created by enotnadoske on 27.11.2020.
//
#include <gtest/gtest.h>
#include "../library.h"
TEST(initial,one){
    ASSERT_EQ(1,1);
}


class TestFoo : public ::testing::Test
{
protected:
    void SetUp()
    {
        a = func_fabric.CreateObject("const", {-2});
        b = func_fabric.CreateObject("polynomial", {0,0,2});
        c = func_fabric.CreateObject("exponential", {1});
        d = func_fabric.CreateObject("power", {2.7,2});
        e = func_fabric.CreateObject("ident", {});
        f = a + b;
        //cout << (*f)(-2) <<endl;
        g = b - c;
        //cout << (*g)(1)<<endl;

        h = c * d;
        //cout << (*h)(2)<<endl;

        i = h / e;
        //cout << (*i)(2)<<endl;
        //cout << a->ToString();

    }
    void TearDown()
    {

    }
    Factory func_fabric;
    unique_ptr<TFunction> a,b,c,d,e;
    TFunction* f;
    TFunction* g;
    TFunction* h;
    TFunction* i;//Why SO?
};

TEST_F(TestFoo, CreationPointValueTest){

   ASSERT_EQ(a->ToString().c_str(), string("-2.000000"));
   ASSERT_EQ((*a)(1000), -2);
   ASSERT_EQ((*a).GetDerive(10.01), 0);
   //cout <<endl<< b->ToString();
   EXPECT_STREQ(b->ToString().c_str(), "0.000000X^0+0.000000X^1+2.000000X^2");
   EXPECT_EQ((*b)(0), 0);
   EXPECT_NEAR((*b)(1.3), 3.38, 0.0001);
   EXPECT_NEAR((*b).GetDerive(1.3), 5.2, 0.0001);//Вот производная вычисленная численно
   EXPECT_STREQ(c->ToString().c_str(), "e^1.000000X");
   EXPECT_NEAR((*c)(1), 2.73, 0.1);
   EXPECT_NEAR((*c).GetDerive(1), 2.73, 0.1);
   EXPECT_STREQ(d->ToString().c_str(), "2.700000^2.000000*X");
   EXPECT_EQ((*d)(0), 1.000000);
   EXPECT_STREQ(f->ToString().c_str(), "(-2.000000) + (0.000000X^0+0.000000X^1+2.000000X^2)");
   EXPECT_EQ((*f)(0), -2);
   EXPECT_EQ(f->GetDerive(1), 4);
   //Остальные операции реализованы по образу и подобию
}

TEST(ExceptionGeneration, InvalidTypes){
    Factory func_fabric;
    unique_ptr<TFunction> a = func_fabric.CreateObject("const", {-2});
    try{
        auto p = a + " ";
    }catch(logic_error a){
        EXPECT_STREQ(a.what(), "invalid type");
    }
    try{
        auto p = " tmp string " + a;
    }catch(logic_error a){
        EXPECT_STREQ(a.what(), "invalid type");
    }
    try{
        auto p = " tmp string " / a;
    }catch(logic_error a){
        EXPECT_STREQ(a.what(), "invalid type");
    }
    try{
        auto p = " tmp string " * a;
    }catch(logic_error a){
        EXPECT_STREQ(a.what(), "invalid type");
    }
    try{
        auto p = " tmp string " - a;
    }catch(logic_error a){
        EXPECT_STREQ(a.what(), "invalid type");
    }
}

TEST( Someuite,Func1 ){
    Factory func_fabric;
    auto a = func_fabric.CreateObject("polynomial",{-5,1});

    auto b = func_fabric.CreateObject("polynomial",{-5,1});
    auto c = a + b;
    ASSERT_NEAR(get_root(0,25,0.1,c), 5, 0.1);
    ASSERT_NEAR(get_root(100,25,0.5,c), 5, 0.1);//Не сошелся
}




