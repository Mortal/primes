#include <vector>
#include <cstdio>
#include <sstream>
#include "primes.h"

template <typename N>
void find_all_the_primes(logger & l, const N n) {
  std::vector<bool> notprime(n);
  notprime[0] = notprime[1] = true;
  unsigned int threshold = 4;
  l() << "Finding all primes less than " << n << std::endl;
  for (unsigned int i = 2; i < (n); ++i) {
    if (i == threshold) {
      l() << "Found all primes less than " << threshold << std::endl;
      threshold = threshold << 1;
    }
    if (!notprime[i]) {
      for (unsigned int j = i+i; j < (n); j += i) {
	notprime[j] = true;
      }
    }
  }
  l() << "Found all primes less than " << n << ", printing to primes.bin" << std::endl;
  write_primes(l, "primes.bin", notprime);
}

int main(int argc, char ** argv) {
  logger l;
  unsigned long long n = 1 << 30;
  if (argc > 1) std::stringstream(argv[1]) >> n;
  if (n < (1ull << 32)) {
    find_all_the_primes<unsigned int>(l, static_cast<unsigned int>(n));
  } else {
    find_all_the_primes<unsigned long long>(l, n);
  }
  return 0;
}
