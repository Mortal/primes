#include <cstdio>
#include <cassert>
#include <cmath>
#include "primes.h"

template <typename N>
void find_more_primes(logger & l, const N n, N iteration) {
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
      N j = ((prime-1+iteration*n)/prime)*prime;
      assert(j >= iteration*n);
      assert(j < n+iteration*n);
      N k = j - iteration*n;
      while (k < n) {
	notprime[k] = true;
	k += prime;
      }
    }
    offset += 256;
  }
past_limit:
  fclose(primes);
  write_primes(l, "primes2.bin", notprime);
}

int main() {
  logger l;
  const unsigned int n = 1 << 14;
  find_more_primes<unsigned int>(l, n, 1);
  return 0;
}
