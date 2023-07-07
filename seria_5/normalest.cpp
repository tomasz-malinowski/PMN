#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<cmath>

template <typename F>
double NormalEst(F f, int n)
{
    std::vector <double> w2 = {0.8862269254527580136491, 0.886226925452758013649};
    std::vector <double> x2 = {-0.7071067811865475244008, 0.7071067811865475244008};

    std::vector <double> w3 = {0.295408975150919337883, 1.181635900603677351532, 0.295408975150919337883};
    std::vector <double> x3 = {-1.224744871391589049099, 0, 1.224744871391589049099};

    std::vector <double> w4 = {0.081312835447245177143, 0.8049140900055128365061, 0.8049140900055128365061, 0.08131283544724517714303};
    std::vector <double> x4 = {-1.650680123885784555883, -0.5246476232752903178841, 0.5246476232752903178841, 1.650680123885784555883};

    std::vector <double> w5 = {0.01995324205904591320774, 0.3936193231522411598285,0.9453087204829418812257, 0.393619323152241159828, 0.01995324205904591320774};
    std::vector <double> x5 = {-2.020182870456085632929, -0.9585724646138185071128, 0, 0.9585724646138185071128, 2.020182870456085632929};

    std::vector<std::vector<double>> w_vector = {w2, w3, w4, w5};
    std::vector<std::vector<double>> x_vector = {x2, x3, x4, x5};

    double sum = 0;
    double pi = 3.14159265358979323846;

    for (size_t i = 0; i < x_vector[n-2].size(); i++){
        sum += w_vector[n-2][i] * f(std::sqrt(2) * x_vector[n-2][i]);
    }
    
    return sum/std::sqrt(pi);

}


double Cos(double x){
    return std::cos(x);
}

int main(int argc, char *argv[]){

    int n;
    std::istringstream(argv[1]) >> n;

    
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

    
    double integral = NormalEst(lambda, 5);
    std::cout<<"wynik wynosi: "<< integral<<std::endl;

    return 0;
}




