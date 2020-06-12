TEMPLATE=subdirs
CONFIG += ordered

SUBDIRS = \
    benchlib \
#    benchmark \
#    projects/primes/primes1 \
#    projects/primes/primes2 \
#    projects/primes/benchprimes \
#    projects/randmarks/randmarks \
#    projects/randmarks/benchrand \
#    projects/randmarks/quantity \
#    projects/randmarks/distance

benchmark.depends = ../ctk/ctk ../ctk/utils/filesys
primes1.depends = ../ctk/ctk ../ctk/utils/filesys benchmark
primes2.depends = ../ctk/ctk ../ctk/utils/filesys benchmark
benchprimes.depends = ../ctk/ctk ../ctk/utils/filesys benchmark primes1 primes2
