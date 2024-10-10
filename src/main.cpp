#include <iostream>
#include "fixed_point_lib/fixed_point.h"
#include <print>
#include <benchmark/benchmark.h>
#include <thread>

int main( void ) {
  fixed_point<uint32_t, 16> A{1.9}, B{1.6};
  double C{double(rand())}, D{double(rand())};

  auto F = A + B;
  double E = C + D;
  return 0;
}


/** /

static void FixedPoint(benchmark::State& state) {
  fixed_point<uint32_t, 16> A{rand()};
  fixed_point<uint32_t, 16> B{rand()};
  for (auto _ : state) {
    A + B;
  }
}

static void FloatPoint(benchmark::State& state) {
  double A{double(rand())}, B{double(rand())};
  for (auto _ : state) {
    A + B + B + B + B + B + B + B + B;
  }
}

BENCHMARK(FixedPoint);
BENCHMARK(FloatPoint);

BENCHMARK_MAIN();

/**/