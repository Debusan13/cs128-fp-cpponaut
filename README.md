# final-project-theteam

## Build and Run the project

```bash
git clone git@github.com:cs128-2021c/final-project-theteam.git
cd final-project-theteam

# install and building dependencies
git submodule update --init --recursive
mkdir external/TermOx/build && cd external/TermOx/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
cd ../../..

# build and run
mkdir build && cd build
cmake ..
make
cd ..
./run.sh
```
## Troubleshooting

# Locale Error
If you are using the cs128env on docker,
you might run into following message while building the program.

"  terminate called after throwing an instance of 'std::runtime_error'
  what():  initialize_terminal(): setlocale() failed.
Aborted "

If so, run the following command to manually set the locale:

```bash

sudo locale-gen en_US.UTF-8

```
# include filesystem error

Some users may encounter an error with detecting the header file <filesystem>,
which is a header file included only on c++ version 17 and later. Cs128env docker
users must have the current version (last updated 10/2021) of the cs128env docker pulled
and built to be able to correctly include this file. Users of other configurations must
ensure c++ version 17 or later is correctly installed on their machine.
