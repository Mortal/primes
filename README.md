Prime generator.

Installation
------------

Install cmake, make, gcc/clang and libboost.

<pre>
git clone git://github.com/Mortal/primes.git
mkdir primes/build
cd primes/build
cmake -DCMAKE_BUILD_TYPE:STRING=Release ..
make
</pre>

Usage
-----

`./primes $n` - find all primes between 0 and $n-1, output to primes.bin.

`./primereader $filename $offset` - output primes stored in $filename (default
primes.bin) offset by $offset (default 0).

`./moreprimes $n $i` - using the primes between 0 and $n-1 stored in
primes.bin, find the primes between $i·$n and $i·$n+$n-1 and output to
primes2.bin.
