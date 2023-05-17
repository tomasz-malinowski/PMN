#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

class LCG
{
    using result_type=size_t;

    result_type x_0, b, m, a;
    
    public:
    result_type Min();
    result_type Max();
    LCG (size_t x_0, int b, int m, int a);
    result_type operator()(); // bo zwraca int
};


LCG::LCG (result_type x_0, int b, int m, int a): x_0(x_0), b(b), m(m), a(a) {};// o te x_0(x_0) etc to robią nam od razu odwołanie do prywatnych pól x_0 etc
    
    // mozna tak zrobić że po obliczeniu x_1, gdy chcemy obliczyć x_2 to dajemy wartość x_2 do x_0 i potem 

LCG::result_type LCG::operator()()
{
    result_type temp = (a*x_0 + b)%m;
    x_0 = temp;
    return temp;
}

LCG::result_type LCG::Min()
{
    if(this->m == 0){
        return 1;
    }
    else{
        return 0;
    }
}

LCG::result_type LCG::Max()
{
    return this->m-1;
}

// i potem możemy podzielić wynik przez Max i wtedy liczbę z przedziału [0,1]

int main(int argc, char *argv[]){

    size_t N;
    std::istringstream(argv[1]) >> N;

    //(double x_0, double b, int m, int a)
    LCG r(5, 0, std::pow(2,31) -1, 48271);
    for(int i = 0; i < N; i++){
        //std::cout<< r()/(double)r.Max() << std::endl;
    }

    std::vector<double> x_vector;
    std::vector<double> y_vector;

    std::vector<double> K_x;
    std::vector<double> K_y;

    for(int i = 0; i < N; i++){
        x_vector.push_back(r()/(double)r.Max());
        y_vector.push_back(r()/(double)r.Max());
    }

    for(auto it_x = x_vector.begin(), it_y = y_vector.begin(); it_x != x_vector.end(); it_x++, it_y++ ){
        if(std::pow(*it_x,2) + std::pow(*it_y,2) < 1){
            K_x.push_back(*it_x);
            K_y.push_back(*it_y);
        }
}

    double pi = 4*K_x.size()/(double)N;
    std::cout<< pi << std::endl;

    return 0;
}