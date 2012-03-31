#include <vector>
#include <cstdio>
#include <sstream>
#include "primes.h"

template <typename N>
void find_all_the_primes(logger & l, const N n_) {
  const N n = n_/2;
  std::vector<bool> notprime(n); // if notprime[i], then 2i+1 is not a prime.
  notprime[0] = true;
  N threshold = 2;
  l() << "Finding all primes less than " << 2*n << std::endl;
  for (N i = 1; i < (n); ++i) {
    if (i == threshold) {
      l() << "Found all primes less than " << 2*threshold << std::endl;
      threshold = threshold << 1;
    }
    if (!notprime[i]) {
      N increment = 2*i+1;
      // index i+2*i+1 is the number 2*(i+2i+1)+1 = 2i+4i+3 = 6i+3 = 3*(2i+1)
      for (unsigned int j = i+increment; j < (n); j += increment) {
	notprime[j] = true;
      }
    }
  }
  l() << "Found all primes less than " << 2*n << ", printing to primes.bin" << std::endl;
  write_primes("primes.bin", notprime);
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
