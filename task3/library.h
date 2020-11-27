#ifndef UNTITLED3_LIBRARY_H
#define UNTITLED3_LIBRARY_H
#include <string>
#include <math.h>
#include <type_traits>
#include <vector>
#include <float.h>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <map>

using namespace std;

class TFunction{

public:
    int type;
    string str;
    double (TFunction::*pFunc)(double);
    virtual string ToString() {return str;};
    virtual double GetDerive(double x){
        return ((*this)(x + FLT_EPSILON) - (*this)(x - FLT_EPSILON))/(2* FLT_EPSILON);
    };
    virtual double operator()(double) {};
    virtual ~TFunction(){};
    virtual TFunction* clone(){
        //cout << "shit";
        return new TFunction(*this);
    };

};

class Ident : public TFunction {
public:
    Ident(vector<double> x){
        if(!x.empty()){
            throw logic_error("too much constructor");
        }else{
            str = "X";
            type = 1;
        }
    }
    virtual Ident* clone(){
        return new Ident(*this);
    }
    double operator()(double x) override {return x;};
    inline string ToString()override{return str;}
    inline double GetDerive(double){return 1;}

};

class Const : public TFunction {
private:
    double m_value;
public:
    int type;
    typedef Const Type;
    Const(vector<double> x){
        if(!x.empty()){

            m_value = x[0];
            str = to_string(m_value);
            type = 2;
        }else{
            throw logic_error("not enough elements in const constructor");
        }
    }
    virtual Const* clone(){
        //cout << "good";
        return new Const(*this);
    }
    double operator()(double)override {
        //cout << m_value;
        return m_value;

    };
    inline string ToString()override{return str;}
    inline double GetDerive(double){return 0;}

};

class Polynomial : public TFunction{
private:
    vector<double> m_vec, d_vec;
public:
    Polynomial(vector<double> mVec) : m_vec(mVec) {
        if(!mVec.empty()){
            int c = 0;
            for (auto i : mVec) {
                d_vec.push_back(c * i);
                str += to_string(i) + string("X^") + to_string(c) + string("+");
                c++;
            }
            str.pop_back();
        }else{
            throw logic_error("not enough elements to construct polynomial");
        }
    };
    virtual Polynomial* clone(){
        return new Polynomial(*this);
    }
    double operator()(double x)
    {
        double xx = 1;
        double res = 0;
        for (auto i : m_vec){
            res += xx * i;
            xx *= x;
        }
        return res;
    }
    inline string ToString() override {return str;}
};

class Exponential : public TFunction{
private:
    double m_value;
public:
    Exponential(){m_value = 1;}
    Exponential(vector<double> vec) {
        if(!vec.empty()){
            m_value = vec[0];
            str = string("e^") + to_string(m_value) + string("X");
        }else{
            throw logic_error("not enough elements to construct exponential");
        }
    }
    virtual Exponential* clone(){
        return new Exponential(*this);
    }
    double operator()(double x) override
    {
        return exp(m_value * x);
    }
    inline string ToString() override {return str;}
};

class Power : public TFunction{
private:
    double m_base, m_pow;
public:
    Power(vector<double>vec){
        if(vec.size()>=2) {
            m_base = vec[0];
            m_pow = vec[1];
            str = to_string(m_base) + string("^") + to_string(m_pow) + string("*X");
        }else{
            throw logic_error("");
        }
    }
    virtual Power* clone(){
        return new Power(*this);
    }
    double operator()(double x) override
    {
        return pow(m_base, m_pow * x);
    }
    inline string ToString() override {return str;}
};

template <class F1, class F2>
class Add : public TFunction {
private:
    TFunction* m_f1;
    TFunction* m_f2;
public:
    typedef Add<F1, F2> Type;
    Add( F1& f1,  F2& f2)  {
        str = string("(") + f1->ToString() + string(") + (") + f2->ToString() + string(")");
        auto tmp1 = f1->clone();
        auto tmp2 = f2->clone();
        //cout << endl << tmp1->operator()(1) << " " << f1->operator()(1) << endl;
        m_f1 = tmp1;
        m_f2 = tmp2;
    }
    virtual Add* clone(){
        return new Add(*this);
    }
    double operator()(double x)  {
        return m_f1->operator()(x) + m_f2->operator()(x);
    }
    string ToString() override {
        return str;
    }

};

template <class F1, class F2>
class Subtract: public TFunction {
private:
    TFunction* m_f1;
    TFunction* m_f2;
public:
    typedef Subtract<F1, F2> Type;
    Subtract( F1& f1,  F2& f2){
        str = string("(") + f1->ToString() + string(") - (") + f2->ToString() + string(")");
        auto tmp1 = f1->clone();
        auto tmp2 = f2->clone();
        //cout << endl << tmp1->operator()(1) << " " << f1->operator()(1) << endl;
        m_f1 = tmp1;
        m_f2 = tmp2;
    }
    virtual Subtract* clone(){
        return new Subtract(*this);
    }
    double operator()(double x) {
        //cout << "!!!" << m_f1->operator()(x) << " " << m_f2->operator()(x) <<  "!!! ";

        return m_f1->operator()(x) - m_f2->operator()(x);
    }
};

template <class F1, class F2>
class Multiply : public TFunction {
private:
    TFunction* m_f1;
    TFunction* m_f2;
public:
    typedef Multiply<F1, F2> Type;
    Multiply( F1& f1,  F2& f2){
        str = string("(") + f1->ToString() + string(") * (") + f2->ToString() + string(")");
        auto tmp1 = f1->clone();
        auto tmp2 = f2->clone();
        //cout << endl << tmp1->operator()(1) << " " << f1->operator()(1) << endl;
        m_f1 = tmp1;
        m_f2 = tmp2;
    }
    virtual Multiply* clone(){
        return new Multiply(*this);
    }
    double operator()(double x)
    {
        return m_f1->operator()(x) - m_f2->operator()(x);
    }
};

template <class F1, class F2>
class Divide : public TFunction {
private:
    TFunction* m_f1;
    TFunction* m_f2;
public:
    typedef Divide<F1, F2> Type;
    Divide( F1& f1,  F2& f2){
        str = string("(") + f1->ToString() + string(") / (") + f2->ToString() + string(")");
        auto tmp1 = f1->clone();
        auto tmp2 = f2->clone();
        //cout << endl << tmp1->operator()(1) << " " << f1->operator()(1) << endl;
        m_f1 = tmp1;
        m_f2 = tmp2;
    }
    virtual Divide* clone(){
        return new Divide(*this);
    }
    double operator()(double x)
    {
        return m_f1->operator()(x) / m_f2->operator()(x);
    }
    string ToString(){
        return str;
    }
};



double get_root(double start_point, int iteration, double step, TFunction* func);


class Factory{
public:
    Factory(){
        RegisterAll();
    };

    class ICreator{
    public:
        virtual unique_ptr<TFunction> create(vector<double>) = 0;
        virtual ~ICreator(){};
    };

    template<typename T>
    class TCreator : public ICreator{
    public:
        unique_ptr<TFunction> create(vector<double> vec)override {
            return make_unique<T>(vec);
        }
    };
    using Registered = map<string, std::shared_ptr<ICreator>>;

    Registered rmap;

    template<typename T>
    void Register(string s){
        rmap[s] = make_shared<TCreator<T>>();
    }

    void RegisterAll(){
        Register<Const>("const");
        Register<Polynomial>("polynomial");
        Register<Exponential>("exponential");
        Register<Power>("power");
        Register<Ident>("ident");
    }

//    template<typename  T,typename... Args>
//    enable_if_t<is_constructible<T,Args...>::value, unique_ptr<T>> create(Args... arg){
//        return make_unique<T>(arg...);
//    }
//
//    template<typename  T,typename... Args>
//    enable_if_t<!is_constructible<T,Args...>::value, unique_ptr<T>> create(Args... arg){
//        return nullptr;
//    }
    std::unique_ptr<TFunction> CreateObject(string s,vector<double> vec){
        auto creator = rmap.find(s);
        if (creator == rmap.end()) {
            return nullptr;
        }
        return creator->second->create(vec);
    }


};





template <class F1, class F2>
typename std::enable_if<(std::is_same<unique_ptr<TFunction>, F1>::value || is_same<TFunction*,F1>::value) && (std::is_same<unique_ptr<TFunction>, F2>::value || is_same<TFunction*,F2>::value) , TFunction*>::type operator+( F1& f1,  F2& f2) {
        return Add<F1, F2>(f1, f2).clone();

};

template <class F1, class F2>
typename std::enable_if<(std::is_same<unique_ptr<TFunction>, F1>::value || is_same<TFunction*,F1>::value) != (std::is_same<unique_ptr<TFunction>, F2>::value || is_same<TFunction*,F2>::value) , int>::type operator+( F1& f1,  F2& f2) {
    throw logic_error("invalid type");
};

template <class F1, class F2>
typename std::enable_if<(std::is_same<unique_ptr<TFunction>, F1>::value || is_same<TFunction*,F1>::value) && (std::is_same<unique_ptr<TFunction>, F2>::value || is_same<TFunction*,F2>::value) , TFunction*>::type  operator-( F1& f1,  F2& f2) {
    return Subtract<F1,F2>(f1,f2).clone();
};

template <class F1, class F2>
typename std::enable_if<(std::is_same<unique_ptr<TFunction>, F1>::value || is_same<TFunction*,F1>::value) != (std::is_same<unique_ptr<TFunction>, F2>::value || is_same<TFunction*,F2>::value) , int>::type operator-( F1& f1,  F2& f2) {
    throw logic_error("invalid type");
};

template <class F1, class F2>
typename std::enable_if<(std::is_same<unique_ptr<TFunction>, F1>::value || is_same<TFunction*,F1>::value) && (std::is_same<unique_ptr<TFunction>, F2>::value || is_same<TFunction*,F2>::value) , TFunction*>::type  operator*( F1& f1,  F2& f2) {
    return Multiply<F1,F2>(f1,f2).clone();
};

template <class F1, class F2>
typename std::enable_if<(std::is_same<unique_ptr<TFunction>, F1>::value || is_same<TFunction*,F1>::value) != (std::is_same<unique_ptr<TFunction>, F2>::value || is_same<TFunction*,F2>::value) , int>::type operator*( F1& f1,  F2& f2) {
    throw logic_error("invalid type");
};

template <class F1, class F2>
typename std::enable_if<(std::is_same<unique_ptr<TFunction>, F1>::value || is_same<TFunction*,F1>::value) && (std::is_same<unique_ptr<TFunction>, F2>::value || is_same<TFunction*,F2>::value) , TFunction*>::type  operator/( F1& f1,  F2& f2) {
    return Divide<F1,F2>(f1,f2).clone();
};

template <class F1, class F2>
typename std::enable_if<(std::is_same<unique_ptr<TFunction>, F1>::value || is_same<TFunction*,F1>::value) != (std::is_same<unique_ptr<TFunction>, F2>::value || is_same<TFunction*,F2>::value) , int>::type operator/( F1& f1,  F2& f2) {
    throw logic_error("invalid type");
};











#endif //UNTITLED3_LIBRARY_H
