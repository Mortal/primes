#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <boost/timer.hpp>

struct log {
  boost::timer t;
  std::ostream & operator()() {
    return std::cout << '[' << std::setw(7) << std::fixed << std::setprecision(2) << t.elapsed() << ']' << ' ';
  }
};

int main() {
  const unsigned int n = 1 << 31;
  std::vector<bool> notprime(n);
  notprime[0] = notprime[1] = true;
  unsigned int threshold = 4;
  log l;
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
    if (count == 0) {
      l() << "There are no primes in the range " << limit-256 << " to " << limit-1 << std::endl;
    }
    fseek(primes, pos, SEEK_SET);
    fwrite(&count, 1, 1, primes);
    fseek(primes, 0, SEEK_END);
  }
  fclose(primes);
  l() << "Finished writing" << std::endl;
  return 0;
}
