#include <iostream>
#include "fixed_point_lib/fixed_point.h"
#include <print>
#include <benchmark/benchmark.h>
#include <thread>

/**/
int main( void ) {
  auto maxD = 1/pow(2, 16);
  std::printf("\x1b[38;2;0;255;0m!! %.8f !!\x1b[38;2;255;255;255m\n", maxD);
  for (double x = 0; x < 1000; x += 0.01f) {
    fixed_point<int32_t, 4> A{x}, B{x};
    auto d = double(A * B) - double(x * x);
    if (fabs(d) > 1)
    //  std::printf("\x1b[38;2;255;0;0m%f - %.8f\x1b[38;2;255;255;255m\n", x, d);
    //else
      std::printf("%f - %.8f\n", x, d);
  }
  return 0;
}


/** /

static volatile float Bunny = 0;

static void FixedPoint(benchmark::State& state) {
  fixed_point<uint32_t, 16> A{rand()};
  fixed_point<uint32_t, 16> B{rand()};
  fixed_point<uint32_t, 16> C{rand()};
  for (auto _ : state) {
     C = A * B;
  }
  Bunny = float(C);
}

static void FloatPoint(benchmark::State& state) {
  double A{double(rand())}, B{double(rand())}, C{double(rand())};
  for (auto _ : state) {
    C = A * B;
  }
  Bunny = float(C);
}

BENCHMARK(FixedPoint);
BENCHMARK(FloatPoint);

BENCHMARK_MAIN();

/**/