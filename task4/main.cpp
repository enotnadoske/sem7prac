#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <numeric>
#include <math.h>
#include <utility>
#include <sstream>
#include <fstream>
using namespace std;

#define X 100
#define Y 100
# define BAD_ITER 20
# define ITER_LIFE 100
# define POP 100
# define CHROMO_SIZE 2500
# define P_INTERSECT 0.8

using SolutionCriteria = map<int, double>;

class Life{
public:
    bool stationar;
    vector<bool> square_init;
    vector<bool> square_result;
    vector<bool> c_step;
    map<int, vector<bool>> current_step;
//    Life(){
//        //gener(square_init);
//        current_step = vec_to_map(square_init);
//        square_result = {};
//        stationar = false;
//    }

    Life(vector<bool> a){
        square_init  = a;
        current_step = vec_to_map(square_init);
        c_step = a;
        square_result = {};
        stationar = false;
    }

    map<int, vector<bool>> vec_to_map(vector<bool> a){
        map<int, vector<bool>>tmp;
        int c = -1;
        for(auto i = 0; i < a.size(); i++){
            if(i%50 == 0){
                c++;
                tmp[c] = {};
                tmp[c].resize(50);
            }
            tmp[c][i%50] = a[i];
        }
        return tmp;
    };
    void print_cur_step(){

        for(auto i : current_step){
            for(auto ii : i.second){
                cout << ii;
            }
            cout << endl;
        }
    };

    void do_steps(int n){
        for(auto it = 0; it < n; it++){
            step();
        }
    }

    void step(){
        map<int, vector<bool>> tmp = current_step;
        for(auto i = 0; i<current_step.size();i++){
            for(auto j = 0; j < current_step[i].size(); j++){
                int a = get_alive_num(i,j);
                if(current_step[i][j]){
                    tmp[i][j] = a == 3 || a == 2;
                }else{
                    tmp[i][j] = a == 3;
                }
            }
        }
        stationar = current_step == tmp;
        current_step = tmp;

    }

    int c_get_alive_num(int a, int b){
        int counter = 0;
        if(a == 0){
            if(b == 0){
                counter += c_step[a*50+b+1] + c_step[(a+1)*50 + b+1] + c_step[(a+1)*50 +b];
                return counter;
            }
            if(b == 49){
                counter += c_step[(a+1)*50 + b] + c_step[a*50 + b-1] + c_step[(a+1)*50 + b-1];
                return counter;
            }
            counter += c_step[a*50 + b+1] + c_step[(a+1)*50 + b+1] + c_step[(a+1)*50 + b] + c_step[a*50 + b-1] + c_step[(a+1)*50 + b-1];
            return counter;
        }
        if(a == 49){
            if(b == 0){
                counter += c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a-1)*50 + b];
                return counter;
            }
            if(b == 49){
                counter += c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1];
                return counter;
            }
            counter += c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1];
            return counter;
        }
        if(b == 0){
            counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b+1]+ c_step[(a-1)*50 + b+1] + c_step[(a+1)*50 + b+1];
            return counter;
        }
        if(b == 49){
            counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1]+ c_step[(a-1)*50 + b-1] + c_step[(a+1)*50 + b-1];
            return counter;
        }
        counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1] + c_step[(a+1)*50 + b-1] + c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a+1)*50 + b+1];
        return counter;
    }

    void sstep(){
        vector<bool> tmp = c_step;
        for(auto i = 0; i<50;i++){
            for(auto j = 0; j < 50; j++){
                int a = c_get_alive_num(i,j);
                if(c_step[i*50+j]){
                    tmp[i*50+j] = a == 3 || a == 2;
                }else{
                    tmp[i*50+j] = a == 3;
                }
            }
        }
        stationar = c_step == tmp;
        c_step = tmp;
    }



    int get_alive_num(int a, int b){
        int counter = 0;
        if(a == 0){
            if(b == 0){
                counter += current_step[a][b+1] + current_step[a+1][b+1] + current_step[a+1][b];
                return counter;
            }
            if(b == 49){
                counter += current_step[a+1][b] + current_step[a][b-1] + current_step[a+1][b-1];
                return counter;
            }
            counter += current_step[a][b+1] + current_step[a+1][b+1] + current_step[a+1][b] + current_step[a][b-1] + current_step[a+1][b-1];
            return counter;
        }
        if(a == 49){
            if(b == 0){
                counter += current_step[a][b+1] + current_step[a-1][b+1] + current_step[a-1][b];
                return counter;
            }
            if(b == 49){
                counter += current_step[a-1][b] + current_step[a][b-1] + current_step[a-1][b-1];
                return counter;
            }
            counter += current_step[a][b+1] + current_step[a-1][b+1] + current_step[a-1][b] + current_step[a][b-1] + current_step[a-1][b-1];
            return counter;
        }
        if(b == 0){
            counter += current_step[a+1][b] + current_step[a-1][b] + current_step[a][b+1]+ current_step[a-1][b+1] + current_step[a+1][b+1];
            return counter;
        }
        if(b == 49){
            counter += current_step[a+1][b] + current_step[a-1][b] + current_step[a][b-1]+ current_step[a-1][b-1] + current_step[a+1][b-1];
            return counter;
        }
        counter += current_step[a+1][b] + current_step[a-1][b] + current_step[a][b-1] + current_step[a-1][b-1] + current_step[a+1][b-1] + current_step[a][b+1] + current_step[a-1][b+1] + current_step[a+1][b+1];
        return counter;
    }

    vector<bool> map_to_vec(){
        vector<bool> tmp;
        for(auto i : current_step){
            for(auto ii : i.second)
                tmp.push_back(ii);
        }
        return  tmp;
    };
    int criteria(){
        int count = 0;
        square_result = map_to_vec();
        for(auto i : square_result){
            count += i;
        }
        return count;
    }

//    void next_step(){
//        get_square()
//    };


};

void print_vec(vector<bool> a){
    map<int, vector<bool>>tmp;
    //cout << a.size();
    for(auto i = 0; i < a.size(); i++){
        if(i%50 == 0){
            cout << "\n";
        }
        if(a[i] == false){
            cout<<"-";
        }else{
            cout << "+";
        }
    }

};


vector<bool> gener(){
    vector<bool> a;
    a.resize(CHROMO_SIZE);
    for(auto && i : a){
        i = rand() % 2;
    }
    return a;
}

//class Chromosome{
//public:
//    Life elem;
//    int criteria;
//    double survival;
//    vector<bool> sq_base;
//    vector<bool> sq_result;
//    Chromosome(vector<bool> el){
//        Life tmp(el);
//        elem = tmp;
//        elem.do_steps(100);
//        criteria = elem.criteria();
//        sq_base = elem.square_init;
//        sq_result = elem.square_result;
//    }
//    void SetSurvival(double a){
//        int survival = a;
//    }
//};


class Abstract_Survival{
public:
    bool last_stationar;
    virtual int survival(vector<bool>) = 0;
    virtual vector<int> survival_all(vector<vector<bool>>) = 0;
};

class Survival : public Abstract_Survival{
    vector<bool> c_step;
    int c_get_alive_num(int a, int b){
        int counter = 0;
        if(a == 0){
            if(b == 0){
                counter += c_step[a*50+b+1] + c_step[(a+1)*50 + b+1] + c_step[(a+1)*50 +b];
                return counter;
            }
            if(b == 49){
                counter += c_step[(a+1)*50 + b] + c_step[a*50 + b-1] + c_step[(a+1)*50 + b-1];
                return counter;
            }
            counter += c_step[a*50 + b+1] + c_step[(a+1)*50 + b+1] + c_step[(a+1)*50 + b] + c_step[a*50 + b-1] + c_step[(a+1)*50 + b-1];
            return counter;
        }
        if(a == 49){
            if(b == 0){
                counter += c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a-1)*50 + b];
                return counter;
            }
            if(b == 49){
                counter += c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1];
                return counter;
            }
            counter += c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1];
            return counter;
        }
        if(b == 0){
            counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b+1]+ c_step[(a-1)*50 + b+1] + c_step[(a+1)*50 + b+1];
            return counter;
        }
        if(b == 49){
            counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1]+ c_step[(a-1)*50 + b-1] + c_step[(a+1)*50 + b-1];
            return counter;
        }
        counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1] + c_step[(a+1)*50 + b-1] + c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a+1)*50 + b+1];
        return counter;
    }

    void sstep(){
        vector<bool> tmp = c_step;
        for(auto i = 0; i<50;i++){
            for(auto j = 0; j < 50; j++){
                int a = c_get_alive_num(i,j);
                if(c_step[i*50+j]){
                    tmp[i*50+j] = a == 3 || a == 2;
                }else{
                    tmp[i*50+j] = a == 3;
                }
            }
        }
        last_stationar = c_step == tmp;
        c_step = tmp;
    }
public:



    int survival(vector<bool> el) override{
        c_step = el;
        for(auto i = 0; i < ITER_LIFE; i++){
            sstep();
        }
        int criteria = 0;
        for(const auto& i : c_step){
            if(i) criteria++;
        }
        return(criteria);
    }

    vector<int> survival_all(vector<vector<bool>> a) override{
        vector<int> res;
        for(auto i : a){
            res.push_back(survival(i));
        }
        return res;
    }
};

class Abstract_Mut{
public:
    virtual void mutation(vector<bool>& a, double d) = 0;
    virtual vector<vector<bool>> pop_mutation(vector<vector<bool>> & a, double d) = 0;
};

class Mut: public Abstract_Mut{
public:
    void mutation(vector<bool>& a, double d) override{
        for (int i = 0; i < CHROMO_SIZE; i++) {
            double p = (double) rand() / RAND_MAX;
            if (d > p) {
                a[i] = !a[i];
            }
        }
    }
    vector<vector<bool>> pop_mutation(vector<vector<bool>>& a, double d) override {
        for(auto & i : a){
            mutation(i,d);
        }
        return a;
    };
};

class Abstract_Select{
public:
    virtual vector<vector<bool>> selection(vector<vector<bool>>, vector<int>, vector<bool>) = 0;
};

class Select : public Abstract_Select{
public:
    vector<vector<bool>> selection(vector<vector<bool>> chromo, vector<int> pop_criteria, vector<bool> criteria_reduction) override{
        vector<vector<bool>> intermediate_pop;
        long sum = 0;
        for(const auto& a : pop_criteria){
            sum += a;
        }
        int c = 0;
        for(auto i = 0; i < chromo.size(); i++){
            double criteria  =  ((pop_criteria[i])*1.)/((double)(sum)/POP);
            if(criteria_reduction[i]){
                criteria -= (int)criteria;
            }
            vector<bool> tmp = chromo[i];
            while(criteria > 1){
                intermediate_pop.push_back(tmp);
                criteria -= 1.0;
            }
            if(((double(rand())/RAND_MAX) < criteria)){
                intermediate_pop.push_back(tmp);
            }
        }
        return intermediate_pop;
    }
};

class Abstract_Intersect{
public:
    virtual void intersection(vector<bool> a, vector<bool> b, vector<bool>& c1, vector<bool>& c2) = 0;
    virtual vector<vector<bool>> pop_intersection(vector<vector<bool>>& population, int t) = 0;
};

class Intersect : public Abstract_Intersect{
public:
    Intersect(){};
    void intersection(vector<bool> p1, vector<bool> p2, vector<bool>& c1, vector<bool>& c2) override{
        int i = rand() % CHROMO_SIZE, j;
        c1 = p1;
        c2 = p2;
        do {
            j = rand() % CHROMO_SIZE;
        } while (j == i);
        if (i > j) {
            std::swap(i, j);
        }
        for (int k = i; k < j; k++) {
            std::iter_swap(c1.begin() + k, c2.begin() + k);
        }
    }

    vector<vector<bool>> pop_intersection(vector<vector<bool>>& p, int t) override{
        vector<vector<bool>> next_pop;
        while(next_pop.size() < POP){
            int index_1 = rand()%(p.size()), index_2;
            do {
                index_2 = rand() % (p.size());
            } while (index_1 == index_2);
            if((double(rand())/RAND_MAX) > P_INTERSECT){
                continue;
            }
            vector<bool> child1;
            vector<bool> child2;

            intersection(p[index_1],p[index_2], child1, child2);
            next_pop.push_back(child1);
            next_pop.push_back(child2);
        }
        return next_pop;
    }
};



class Genetic{
public:
    vector<vector<bool>> population;
    vector<bool> best;
    int criteria_best;
    vector<int> fs;
    vector<bool> bs;
    double Pmut;
    Abstract_Mut * mut;
    Abstract_Select * select;
    Abstract_Intersect * intersect;
    Abstract_Survival * survivor;

    Genetic(Abstract_Mut* m, Abstract_Select* s, Abstract_Intersect* in, Abstract_Survival* sur, double d){
        Pmut = d;
        mut = m;
        select = s;
        intersect = in;
        survivor = sur;
        criteria_best = 0;
        for(auto i = 0; i < POP; i++){

            vector<bool> tmp = gener();
            population.push_back(tmp);
            int value = survivor->survival(tmp);
            fs.push_back(value);
            bs.push_back(survivor->last_stationar);
            if (value > criteria_best) {
                best = population[i];
                criteria_best = value;
            }
        }
    }

    pair<vector<bool>,int> run() {
        int badIt = 0;
        while (badIt < 20){
            vector<vector<bool>> pop_select = select->selection(population,fs,bs);
           // cout << endl << pop_select.size() << " ";
            auto pop_interect = intersect->pop_intersection(pop_select,1);
            auto pop_mutation = mut->pop_mutation(pop_interect, Pmut);
            bool fl = false;
            fs.clear();
            for (auto &elem : pop_mutation) {
                int value = survivor->survival(elem);
                fs.push_back(value);
                bs.push_back(survivor->last_stationar);
                if ((value > criteria_best) && (!survivor->last_stationar) ) {
                    best = elem;
                    criteria_best = value;
                    //cout << badIt;
                    badIt = 0;

                    fl = true;
                }
            }

            if (!fl) {
                badIt++;
            }
            population = pop_mutation;
        }
        return make_pair(best,criteria_best);
    }

};

void WriteInFile(vector<bool> &s_best, bool l, int exp_n, int run_n) {


    string filename = !l ? "series_" + to_string(exp_n) + "_run_" + to_string(run_n) + "_sol.txt" :
                           "series_" + to_string(exp_n) + "_run_" + to_string(run_n) + "_sol_after100.txt";
    ofstream file(filename.c_str());

    for (size_t i = 0; i < 50; i++) {
        for (size_t j = 0; j < 50; j++) {
            auto symb = s_best[i*50 + j] == true ? "+" : "-";
            file << symb;
        }
        file << std::endl;
    }
    file.close();
}


int c_get_alive_num(int a, int b, vector<bool> c_step){
    int counter = 0;
    if(a == 0){
        if(b == 0){
            counter += c_step[a*50+b+1] + c_step[(a+1)*50 + b+1] + c_step[(a+1)*50 +b];
            return counter;
        }
        if(b == 49){
            counter += c_step[(a+1)*50 + b] + c_step[a*50 + b-1] + c_step[(a+1)*50 + b-1];
            return counter;
        }
        counter += c_step[a*50 + b+1] + c_step[(a+1)*50 + b+1] + c_step[(a+1)*50 + b] + c_step[a*50 + b-1] + c_step[(a+1)*50 + b-1];
        return counter;
    }
    if(a == 49){
        if(b == 0){
            counter += c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a-1)*50 + b];
            return counter;
        }
        if(b == 49){
            counter += c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1];
            return counter;
        }
        counter += c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1];
        return counter;
    }
    if(b == 0){
        counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b+1]+ c_step[(a-1)*50 + b+1] + c_step[(a+1)*50 + b+1];
        return counter;
    }
    if(b == 49){
        counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1]+ c_step[(a-1)*50 + b-1] + c_step[(a+1)*50 + b-1];
        return counter;
    }
    counter += c_step[(a+1)*50 + b] + c_step[(a-1)*50 + b] + c_step[a*50 + b-1] + c_step[(a-1)*50 + b-1] + c_step[(a+1)*50 + b-1] + c_step[a*50 + b+1] + c_step[(a-1)*50 + b+1] + c_step[(a+1)*50 + b+1];
    return counter;
}

vector<bool> sstep(vector<bool>c_step){
    vector<bool> tmp = c_step;
    for(auto i = 0; i<50;i++){
        for(auto j = 0; j < 50; j++){
            int a = c_get_alive_num(i,j,c_step);
            if(c_step[i*50+j]){
                tmp[i*50+j] = a == 3 || a == 2;
            }else{
                tmp[i*50+j] = a == 3;
            }
        }
    }
    return tmp;
}



int main(int argc, char *argv[]) {

    srand(time(NULL));

    Select s;
    Survival sur;
    Intersect i;
//    auto t = i.pop_intersection(cb,1);
//    i.intersection(gener(),gener(), c, b);
    Mut m;
    std::stringstream conv_1(argv[1]), conv_2(argv[2]);
    int series, run;
    conv_1 >> series;
    conv_2 >> run;
    cout<<"experiment "<<series << " run "<<run << endl;
    Genetic a(&m,&s,&i,&sur, 0.0004*pow(1.5,series));
    auto k = a.run();
    WriteInFile(k.first, false, series, run);
    vector<bool> tmp = k.first;
    for(auto it = 0; it<100; it++){
        tmp = sstep(tmp);
    }
    WriteInFile(tmp, true, series, run);
    std::string filename = "series_" + std::to_string(series) + "_run_" + std::to_string(run) + "_time.txt";
    std::ofstream file(filename.c_str());
    file << k.second;
    file.close();





    //cout << true + true;
}
