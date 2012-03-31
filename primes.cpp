#include <vector>
#include <cstdio>
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

int main() {
  logger l;
  const unsigned int n = 1 << 14;
  find_all_the_primes<unsigned int>(l, n);
  return 0;
}
