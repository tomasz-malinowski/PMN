/**
 * Programowanie i metody numeryczne
 *
 * Programowanie współbieżne - przykład 1.
 *
 *
 * Opracowano na podstawie:
 *    https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter07/problem_61/main.cpp
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
#include <future>


template <typename It>
auto Max1(It begin, It end)
{
    return std::accumulate(begin, end, 0);
}

//template <typename It>
//auto Max2(It begin, It end)

//template <typename It>
//auto Max3(It begin, It end)



template <typename It>
auto Max3(It begin, It end)
{
      std::vector<std::future<typename std::iterator_traits<It>::value_type>> tasks;
      int task_count = std::thread::hardware_concurrency();
	  auto part_size = std::distance(begin, end) / task_count;
	  
	  std::vector<typename std::iterator_traits<It>::value_type> results(task_count);
      
	  auto part_begin = begin;
      auto part_end = begin;
      for (int i = 0; i < task_count; ++i)
      {
         part_begin = part_end;
         if (i == task_count - 1)
		 {
			 part_end = end;
		 }
         else
		 {
			 std::advance(part_end, part_size);
		 }
		 
		 tasks.push_back(std::async(std::launch::async, [part_begin, part_end]() { return std::accumulate(part_begin, part_end, 0); }));
      }

      for (auto &t : tasks)
	  {
		  results.push_back(t.get());
	  }
	  
	  return std::accumulate(results.begin(), results.end(), 0);
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
   std::cout << "Wywołanie synchroniczne:" << std::endl;
   std::cout << "   wynik: " << result << std::endl;
   std::cout << "   czas:  " << time.count() << " ms" << std::endl;
   
   start = std::chrono::system_clock::now();
   result = Max3(v.begin(), v.end());
   end = std::chrono::system_clock::now();
   time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
   std::cout << "Wywołanie asynchroniczne:" << std::endl;
   std::cout << "   wynik: " << result << std::endl;
   std::cout << "   czas:  " << time.count() << " ms" << std::endl;

   return 0;
}