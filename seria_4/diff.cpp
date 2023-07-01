#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>


template<typename F>
double DiffForward(F f, double x0, double h)
{
    return (f(x0+h) - f(x0))/h;
}

template<typename F>
double DiffBackward(F f, double x0, double h)
{
    return (f(x0) - f(x0-h))/h;
}

template<typename F>
double DiffCentral(F f, double x0, double h)
{
    return (f(x0+h) - f(x0-h))/(2*h);
}

template<typename F>
double DiffRichardson(F f, double x0, double h)
{
    return (-f(x0+2*h) + 8*f(x0+h) -8*f(x0-h) + f(x0-2*h)) /(12*h);
}

int main(int argc, char *argv[]){

    std::string diff_method;
    double x0;
    double h;

    std::istringstream(argv[1]) >> diff_method;
    std::istringstream(argv[2]) >> x0;
    std::istringstream(argv[3]) >> h;


    double coeff;

    /*std::cout<<"Forward method: "<<res_forward<< std::endl;
    std::cout<<"Backward method: "<<res_backward<< std::endl;
    std::cout<<"Central method: "<<res_central<< std::endl;
    std::cout<<"Richardson method: "<<res_richardson<< std::endl;
    */


    std::vector<double> coeffs;

    while(std::cin>>coeff){
        coeffs.push_back(coeff);
    }



    auto lambda = [&coeffs](double x){

        double result = 0.0;
        double power = 1.0;

        for(auto it = coeffs.begin(); it != coeffs.end(); it++){
            result += *it*power;
            power *= x;
        }
        return result;
    };

    double diff_result = 0.0;

    if(diff_method == "forward"){
        std::cout <<"Wynik różniczkowania wielomianu metodą "<<diff_method<<": "<<DiffForward(lambda, x0, h);
    }
    else if(diff_method == "backward"){
        std::cout <<"Wynik różniczkowania wielomianu metodą "<<diff_method<<": "<<DiffBackward(lambda, x0, h);
    }
    else if(diff_method == "central"){
        std::cout <<"Wynik różniczkowania wielomianu metodą "<<diff_method<<": "<<DiffCentral(lambda, x0, h);
    }
    else if(diff_method == "richardson"){
        std::cout <<"Wynik różniczkowania wielomianu metodą "<<diff_method<<": "<<DiffRichardson(lambda, x0, h);
    }
    else{
        std::cout<<"zła nazwa metody"<<std::endl;
    }
    
    return 0;
}