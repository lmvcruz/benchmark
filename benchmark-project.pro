TEMPLATE=subdirs
CONFIG += ordered

QMAKE_CXXFLAGS = "-std=c++11"

SUBDIRS = \
    benchmark \
#    projects/genomicrangequery/grq1 \
#    projects/genomicrangequery/grq2 \
#    projects/primes/primes1 \
#    projects/primes/primes2 \
    projects/randmarks/randmarks \
    projects/randmarks/createdata \
    projects/randmarks/quantity

benchmark.depends = benchmark grq1 grq2 primes1 primes1
grq1.depends = ../ctk/ctk ../ctk/utils/filesys
grq2.depends = ../ctk/ctk ../ctk/utils/filesys 
primes1.depends = ../ctk/ctk ../ctk/utils/filesys
primes2.depends = ../ctk/ctk ../ctk/utils/filesys