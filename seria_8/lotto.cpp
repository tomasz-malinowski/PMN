#include <iostream>
#include <random>
#include<set>


int main(){

    std::random_device seed;
    //unsigned int seedValue = seed();



    std::mt19937 mt(seed());

    std::uniform_int_distribution lotto{1, 49};


    std::set<int> lotto_nums;
        
    while(lotto_nums.size() < 6){
        lotto_nums.insert(lotto(mt));
    }    

    for(auto it = lotto_nums.begin(); it !=lotto_nums.end(); it++){
        std::cout<<*it<< " ";
    }

    std::cout<<std::endl;

    return 0;
}