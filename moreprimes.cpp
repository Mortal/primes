#include <cstdio>
#include <cassert>
#include <cmath>
#include <sstream>
#include "primes.h"

template <typename N>
void find_more_primes(logger & l, const N n_, N iteration) {
  const N n = n_/2;
  std::vector<bool> notprime(n);
  FILE * primes = fopen("primes.bin", "r");
  N offset = 0;
  N limit = static_cast<N>(sqrtl(static_cast<long double>(n+iteration*n)));
  while (!feof(primes)) {
    unsigned char count = static_cast<unsigned char>(fgetc(primes));
    if (feof(primes)) break;
    while (count--) {
      unsigned char i = static_cast<unsigned char>(fgetc(primes));
      N prime = offset + i;
      if (prime > limit)
	goto past_limit;
      // first non-prime corresponding to this prime
      N j = ((prime-1+iteration*n_)/prime)*prime;
      assert(j >= iteration*n_);
      assert(j < n_+iteration*n_);
      // first index to write to
      N k = (j - iteration*n)/2;
      N increment = j - iteration*n;
      while (k < n_) {
	notprime[k] = true;
	k += increment;
      }
    }
    offset += 256;
  }
past_limit:
  l() << "Writing primes to primes2.bin" << std::endl;
  fclose(primes);
  write_primes("primes2.bin", notprime);
}

int main(int argc, char ** argv) {
  logger l;
  unsigned long long n = 1 << 30;
  int run = 1;
  if (argc > 1) std::stringstream(argv[1]) >> n;
  if (argc > 2) std::stringstream(argv[2]) >> run;
  if ((n+run*n) < (1ull << 32)) {
    find_more_primes<unsigned int>(l, static_cast<unsigned int>(n), run);
  } else {
    find_more_primes<unsigned long long>(l, n, run);
  }
  return 0;
}
