#! /bin/sh
#
# at .bashrc
#
#
./configure --prefix=$1 \
            CXX=mpicc \
	    --enable-mpi
