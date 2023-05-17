#include <cmath>
#include <iostream>
#include <random>
#include <numeric>
#include <vector>
#include <sstream>

double Chi(double x, double y){
        if (std::pow((x*x +y*y),2) <= 2*(x*x - y*y)){
            return 1;
        }
        else return 0;
    }

template <typename RNG, typename F>
double IntMonteCarlo(F f, double a, double b, size_t N)
{
    // Inicjalizacja generatora liczb losowych.
    std::random_device seed;
    RNG rng(seed());
    std::uniform_real_distribution<> uni(a, b);
    
	// Obliczenie całki.
	double s = 0;
    for(size_t i = 0; i != N; ++i)
    {
        s += f(uni(rng));
    }
    return s * (b - a) / N;
}


/*double Chi(double x, double y)
{
    if () return 1;
    else return 0;
}
*/

template <typename RNG>
double LemniscateArea(size_t N)
{

    
    
    std::random_device seed;
    RNG rng(seed());
    std::uniform_real_distribution<> uni(-1.5, 1.5);
    std::uniform_real_distribution<> uni2(-0.6, 0.6);
    double S = 0;
    for(size_t i = 0; i < N; i++){
        S += Chi(uni(rng), uni2(rng));
    }
    return S*3*1.2/N;
}

double Int(double x)
{
    return 2 * std::sqrt(1 - x*x);
}

int main(int argc, char *argv[])
{
    size_t N;
    std::istringstream(argv[1]) >> N;
	/*
    std::vector<double> pi;
    for(size_t i = 0; i < 100; ++i)
    {
        pi.push_back(IntMonteCarlo<std::mt19937>(Int, -1, 1, N));
    }
    std::cout << std::accumulate(pi.begin(), pi.end(), 0.0) / pi.size() << std::endl;
    */

    std::cout<<"pole: " << LemniscateArea<std::mt19937>(N) << std::endl;
	
    return 0;
}