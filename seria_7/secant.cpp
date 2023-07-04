#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>




template<typename F>
bool RootSecant(double &x, F f, double x0, double x1, double eps, int N)
{
    for(int i = 0; i < N; i++){
        double x2 = x1 - f(x1)*(x1-x0)/(double)(f(x1) - f(x0));
        x0 = x1;
        x1 = x2;
        x = x2;

        if(std::abs(f(x)) < eps){
            return true;
        }
        else{
            continue;
        }
    }
    return false;

}

int main(int argc, char *argv[]){

    double x1, x2, eps;
    int N;

    std::istringstream(argv[1]) >> x1;
    std::istringstream(argv[2]) >> x2;
    std::istringstream(argv[3]) >> eps;
    std::istringstream(argv[4]) >> N;

    double x=0;
    double coeff;

    std::vector<double> coeffs;

    while(std::cin>>coeff){
        coeffs.push_back(coeff);
    }

    auto lambda = [&coeffs](double y){

        double result = 0.0;
        double power = 1.0;

        for(auto it = coeffs.begin(); it != coeffs.end(); it++){
            result += *it*power;
            power *= y;
        }
        return result;
    };

    bool var = RootSecant(x, lambda, x1, x2, eps, N);

    std::cout<<"Znalezione miejsce zerowe: "<<x<<std::endl;
    std::cout<<var<<std::endl;
    
    return 0;
}