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
