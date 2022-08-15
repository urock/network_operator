# Network operator

Репозиторий cpp кода сетевого оператора

1. Что это такое
2. Как скомпилировать
3. Что запустить


## how to build
```
git submodule update --init --recursive 
mkdir build
cd build
cmake ..
make
```

## Run tests
```
cd build/test
./nop_tests 
# or
./nop_tests --gtest_filter="NOP.*"
```





