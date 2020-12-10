#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

const int MAX = 1000000;
std::vector<int> arr;
  
int multiplication(const std::vector<int>& arr) {
  int val = 1;
  for (auto& e : arr) {
    if (rand() % 2) {
      val ^= e;
    }
  }
  return val;
}

static void BM_multiplication(benchmark::State& state) {
  for (auto _ : state) {
    multiplication(arr);
  }
}

BENCHMARK(BM_mulxtiplication);

int main(int argc, char** argv) {       
  for (int i = 0; i < MAX; ++i) {
    arr.push_back(rand());
  }
                              
  benchmark::Initialize(&argc, argv);                               
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; 
  benchmark::RunSpecifiedBenchmarks();                              
}