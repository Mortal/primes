#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <boost/timer.hpp>

struct logger {
  boost::timer t;
  std::ostream & operator()() {
    return std::cout << '[' << std::setw(7) << std::fixed << std::setprecision(2) << t.elapsed() << ']' << ' ';
  }
};

void write_primes(const char * filename, std::vector<bool> & notprime) {
  logger l;
  l() << "Writing to " << filename << std::endl;
  FILE * primes = fopen(filename, "w+");
  size_t n = 2*notprime.size();
  size_t idx = 0;
  for (size_t offset = 1; offset < n;) {
    size_t limit = offset+255;
    int pos = ftell(primes);
    unsigned char count = 0;
    fwrite(&count, 1, 1, primes);
    unsigned char i = 1;
    while (offset < limit) {
      if (!notprime[idx]) {
	fwrite(&i, 1, 1, primes);
	++count;
      }
      offset += 2;
      i += 2;
      ++idx;
    }
    if (count == 0) {
      l() << "There are no primes in the range " << limit-256 << " to " << limit-1 << std::endl;
    }
    fseek(primes, pos, SEEK_SET);
    fwrite(&count, 1, 1, primes);
    fseek(primes, 0, SEEK_END);
  }
  fclose(primes);
  l() << "Finished writing to " << filename << std::endl;
}
