#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>

int main() {
  const size_t n = 1 << 30;
  const size_t every = 1 << 14;
  std::vector<bool> notprime(n);
  notprime[0] = notprime[1] = true;
  for (unsigned int i = 2; i < (n); ++i) {
    if (!notprime[i]) {
      for (unsigned int j = i+i; j < (n); j += i) {
	notprime[j] = true;
      }
    }
  }
  std::cout << "Calculated all the primes!" << std::endl;
  FILE * primes = fopen("primes.bin", "w+");
  for (size_t offset = 0; offset < n;) {
    size_t limit = offset+256;
    int pos = ftell(primes);
    unsigned char count = 0;
    fwrite(&count, 1, 1, primes);
    unsigned char i = 0;
    while (offset < limit) {
      if (!notprime[offset]) {
	fwrite(&i, 1, 1, primes);
	++count;
      }
      ++offset, ++i;
    }
    if (count == 0) std::cout << offset << std::endl;
    fseek(primes, pos, SEEK_SET);
    fwrite(&count, 1, 1, primes);
    fseek(primes, 0, SEEK_END);
  }
  fclose(primes);
  return 0;
}
