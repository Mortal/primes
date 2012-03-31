#include <cstdio>
#include <iostream>
#include <sstream>

int main(int argc, char ** argv) {
  size_t offset = 0;
  std::string filename = "primes.bin";
  if (argc > 1) filename = argv[1];
  if (argc > 2) std::stringstream(argv[2]) >> offset;
  FILE * primes = fopen(filename.c_str(), "r");
  while (primes && !feof(primes)) {
    unsigned char count = static_cast<unsigned char>(fgetc(primes));
    if (feof(primes)) break;
    while (count--) {
      size_t prime = offset + static_cast<size_t>(fgetc(primes));
      std::cout << prime << '\n';
    }
    offset += 256;
  }
  fclose(primes);
  return 0;
}
