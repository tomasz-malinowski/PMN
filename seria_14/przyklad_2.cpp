/**
 * Programowanie i metody numeryczne
 *
 * Programowanie współbieżne - przykład 2.
 *
 *
 * Opracowano na podstawie:
 *    https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter07/problem_62/main.cpp
 *    Copyright (c) 2018 Packt
 *    Licencja MIT
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <chrono>
#include <thread>

template <typename It>
auto Max1(It begin, It end)
{
	return *std::max_element(begin, end);
}

template <typename It>
auto Max2(It begin, It end)
{
      std::vector<std::thread> threads;
      int thread_count = std::thread::hardware_concurrency();
	  auto part_size = std::distance(begin, end) / thread_count;
	  
	  std::vector<typename std::iterator_traits<It>::value_type> results(thread_count);
      
	  auto part_begin = begin;
      auto part_end = begin;
      for (int i = 0; i < thread_count; ++i)
      {
         part_begin = part_end;
         if (i == thread_count - 1)
		 {
			 part_end = end;
		 }
         else
		 {
			 std::advance(part_end, part_size);
		 }
		 
		 threads.push_back(std::thread([part_begin, part_end, &r = results[i]]() { r = *std::max_element(part_begin, part_end); }));
      }

      for (auto &t : threads) t.join();
	  
	  return *std::max_element(results.begin(), results.end());
}

int main()
{
   const size_t size = 10000000;
   std::vector<int> v(size);
   
   std::random_device rd; 
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dis(1, 10000000);
   std::generate(v.begin(), v.end(), [&](){ return dis(gen); });
   
   auto start = std::chrono::system_clock::now();
   auto result = Max1(v.begin(), v.end());
   auto end = std::chrono::system_clock::now();
   auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
   std::cout << "Wywołanie sekwencyjne:" << std::endl;
   std::cout << "   wynik: " << result << std::endl;
   std::cout << "   czas:  " << time.count() << " ms" << std::endl;
   
   start = std::chrono::system_clock::now();
   result = Max2(v.begin(), v.end());
   end = std::chrono::system_clock::now();
   time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
   std::cout << "Wywołanie współbieżne:" << std::endl;
   std::cout << "   wynik: " << result << std::endl;
   std::cout << "   czas:  " << time.count() << " ms" << std::endl;

   return 0;
}