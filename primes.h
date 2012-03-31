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

void write_primes(logger & l, const char * filename, std::vector<bool> & notprime) {
  FILE * primes = fopen(filename, "w+");
  size_t n = notprime.size();
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
  l() << "Finished writing to " << filename << std::endl;
}
