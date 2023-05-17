#include <cmath>
#include <iostream>
#include <random>
#include <numeric>
#include <vector>
#include <sstream>

double Chi(std::vector<double> cords){
        double sum = 0;
        for(auto it = cords.begin(); it != cords.end(); it++ ){
            sum += *it*(*it);
        }
        if(sum < 1) return 1;
        else return 0;
}

template <typename RNG>
double BallVolume(size_t n, size_t N)
{
    std::random_device seed;
    RNG rng(seed());
    std::uniform_real_distribution<> uni(-1, 1);
    
    double Sum = 0;
    for(size_t i = 0; i < N; i++){
        std::vector<double> cords;
        for(size_t j = 0; j < n; j++){
            cords.push_back(uni(rng));
        }

        Sum += Chi(cords);
    }
    return Sum*std::pow(2, n)/N;
}


int main(int argc, char *argv[])
{
    size_t n;
    size_t N; 
    std::istringstream(argv[1]) >> n;
    std::istringstream(argv[2]) >> N;

	/*
    std::vector<double> pi;
    for(size_t i = 0; i < 100; ++i)
    {
        pi.push_back(IntMonteCarlo<std::mt19937>(Int, -1, 1, N));
    }
    std::cout << std::accumulate(pi.begin(), pi.end(), 0.0) / pi.size() << std::endl;
    */

    std::cout<<"pole: " << BallVolume<std::mt19937>(n, N) << std::endl;
	
    return 0;
}