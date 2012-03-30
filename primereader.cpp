#include <cstdio>
#include <iostream>

int main() {
  FILE * primes = fopen("primes.bin", "r");
  size_t offset = 0;
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
