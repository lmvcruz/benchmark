TEMPLATE=subdirs
CONFIG += ordered

#QMAKE_CXXFLAGS = "-std=c++11"

SUBDIRS = \
    benchlib \
    benchmark \
#    projects/genomicrangequery/grq1 \
#    projects/genomicrangequery/grq2 \
#    projects/primes/primes1 \
#    projects/primes/primes2 \
    projects/randmarks/randmarks \
#    projects/randmarks/createdata \
#    projects/randmarks/quantity \
    snippets

benchmark.depends = ../ctk/ctk ../ctk/utils/filesys
grq1.depends = ../ctk/ctk ../ctk/utils/filesys benchmark
grq2.depends = ../ctk/ctk ../ctk/utils/filesys benchmark
primes1.depends = ../ctk/ctk ../ctk/utils/filesys benchmark
primes2.depends = ../ctk/ctk ../ctk/utils/filesys benchmark
