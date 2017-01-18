# TextParser - Text Parsing Library

- Copyright (c) 2012-2015 Institute of Industrial Science, The University of Tokyo. All rights reserved.
- Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN. All rights reserved.
- Copyright (c) 2016-2017 Research Institute for Information Technology, Kyushu University. All rights reserved.


## OUTLINE
Text Parser library allows us to describe and to parse JSON like simple parameter structure.


## PREREQUISITE
- Cmake
- MPI library


## HOW TO BUILD

### Build

~~~
$ export TP_HOME=/hogehoge
$ mkdir BUILD
$ cd BUILD
$ cmake [options] ..
$ make
$ make test  // if test option is specified.
$ sudo make install
~~~

### Options

`-D INSTALL_DIR=install_directory`

>  Specify the directory that this library will be installed. Built library is
   installed at `install_directory/lib` and the header files are placed at
   `install_directory/include`.

`-D comp_kind=(INTEL|FJ|GNU)`

>  If Fujitsu compiler is used, specify FJ. This option is _mandatory_.

`-D enable_fapi=(no|yes)`

>  This option is for building Fortran API. Default is no.

`-D enable_test=(yes|no)`

>  This option turns on compiling sample codes and execute the tests. Default is yes.

`-D TP_BUILD_CROSS=(OFF|ON)`

>  Specify TP_BUILD_CROSS=ON in the case of cross-compilation, otherwise OFF or you can omit.

`-D TP_BUILD_MPI=(OFF|ON)`

>  If you use an MPI library, specify `TP_BUILD_MPI=ON`, otherwise OFF or you can omit.

`-D TP_BUILD_OMP=(OFF|ON)`

>  If you activate OpenMP directives, specify `TP_BUILD_OMP=ON`, otherwise OFF or you can omit.

`-D CXX=CXX_COMPILER`

>  Specify C++ compiler or a wrapper compiler for MPI. If a wrapper compiler is
   specified, set string as `-DCXX=mpicxx` without directory prefix.

`-D CC=C_COMPILER`
>  Specify C compiler or a wrapper compiler for MPI.

`-D F90=FORTRAN90_COMPILER`
>   Specify Fortran90 compiler or a wrapper compiler for MPI.


The default compiler options are described at the top level CMakeLists.txt file.
See the detail at BUILD OPTION section. If you need to change compiler flags,
you can specify by `CMAKE_C_FLAGS`, `CMAKE_CXX_FLAGS`, and `CMAKE_Fortran_FLAGS`, respectively. These FLAGS override the default option `-O3`.

~~~
-D CMAKE_C_FLAGS=options
-D CMAKE_CXX_FLAGS=options
-D CMAKE_Fortran_FLAGS=options
~~~

* `-Wno-dev` option suppresses warnings for developpers.


## Configure Examples

### INTEL compiler

#### Serial
* C/C++ only with test

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=INTEL -DCC=icc -DCXX=icpc -Wno-dev ..
	~~~

  * Suppress example test

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=INTEL -DCC=icc -DCXX=icpc -Denable_test=no -Wno-dev ..
	~~~

* With fortran API

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=INTEL -DCC=icc -DCXX=icpc -DF90=ifort -Denable_fapi=yes -Wno-dev ..
	~~~


#### MPI
* C/C++ by a wrapper compiler

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=INTEL -DCC=mpicc -DCXX=mpicxx -DTP_BUILD_MPI=ON -Wno-dev ..
	~~~
	Before compiling, OpenMPI shuold be compiled by Intel compiler.

* With fortran API

  ~~~
  $ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=INTEL -DCC=mpicc -DCXX=mpicxx -DTP_BUILD_MPI=ON -DF90=mpif90 -Denable_fapi=yes -Wno-dev ..
  ~~~


### GNU compiler

#### Serial
* C/C++ only

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=GNU -DCC=gcc -DCXX=g++ -Wno-dev ..
	~~~

* With fortran API

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=GNU -DCC=gcc -DCXX=g++ -DF90=gfortran -Denable_fapi=yes -Wno-dev ..
	~~~

#### MPI
* C/C++ by a wrapper compiler

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=GNU -DCC=mpicc -DCXX=mpicxx -DTP_BUILD_MPI=ON -Wno-dev ..
	~~~

* With fortran API

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=GNU -DCC=mpicc -DCXX=mpicxx -DTP_BUILD_MPI=ON -DF90=mpif90 -Denable_fapi=yes -Wno-dev ..
  	~~~


### FUJITSU compiler / FX, K computer on login nodes (Cross compilation)

#### Serial
* C/C++ only

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=FJ -DCC=fccpx -DCXX=FCCpx -DTP_BUILD_CROSS=ON -Wno-dev ..
	~~~

* With fortran API

  ~~~
  $ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=FJ -DCC=fccpx -DCXX=FCCpx -DF90=frtpx -Denable_fapi=yes -DTP_BUILD_CROSS=ON -Wno-dev ..
  ~~~


#### MPI

* C/C++ only

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=FJ -DCC=mpifccpx -DCXX=mpiFCCpx -DTP_BUILD_MPI=ON -DTP_BUILD_CROSS=ON -Wno-dev ..
	~~~

* with fortran API

	~~~
	$ cmake -DINSTALL_DIR=${TP_HOME}/TextParser -Dcomp_kind=FJ -DCC=mpifccpx -DCXX=mpiFCCpx -DF90=mpifrtpx -Denable_fapi=yes -DTP_BUILD_MPI=ON -DTP_BUILD_CROSS=ON -Wno-dev ..
	~~~


##### Note
- Before building, execute following command for clean. `$ make distclean`

- Available target
	- `mpi`	Build a library for MPI. _Disable_ is default.
	- `f90_api` Specify to build API for fortran90. _Disable_ is default.

- Build library is only static library and installed lib/ directory.



## TEST
* If you specify the test option by `-Denable_test=yes` (default), you can
execute the intrinsic tests by;

	`$ make test`

* The detailed results are written in `BUILD/Testing/Temporary/LastTest.log` file.
Meanwhile, the summary is displayed for stdout.



## CONTRIBUTORS

* Kenji    Ono        _keno@{cc.kyushu-u.ac, riken, iis.u-tokyo.ac}.jp_
* Tomohiro Kawanabe
* Takafumi Suzuki
* Satoshi  Fuchikami
* Naoyuki  Sogo
* Eri      Takebe
* Syoyo    Fujita
* Ken      Uzawa
