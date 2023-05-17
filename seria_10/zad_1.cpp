#include <cmath>
#include <iostream>
#include <random>
#include <numeric>
#include <vector>
#include <sstream>

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

double Int(double x)
{
    return 2 * std::sqrt(1 - x*x);
}

int main(int argc, char *argv[])
{
    size_t N;
    std::istringstream(argv[1]) >> N;
	
    std::vector<double> pi;
    for(size_t i = 0; i < 100; ++i)
    {
        pi.push_back(IntMonteCarlo<std::mt19937>(Int, -1, 1, N));
    }
    std::cout << std::accumulate(pi.begin(), pi.end(), 0.0) / pi.size() << std::endl;
	
    return 0;
}