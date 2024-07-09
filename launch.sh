if [ -d "build" ]; then
    rm -r build
fi
mkdir build
cp -r src build/src
cp -r tests build/tests
cp -r include build/include
cd build/src
g++ -std=c++20 *.cpp ../tests/test.cpp commands/*cpp -o luna.sh -lreadline $LDFLAGS $CPPFLAGS

export LDFLAGS="-L$CONDA_PREFIX/lib"
export CPPFLAGS="-I$CONDA_PREFIX/include"
export DYLD_LIBRARY_PATH="$CONDA_PREFIX/lib:$DYLD_LIBRARY_PATH"

# debug, testing and leaks mode for own use
if [[ $1 = "--testing" ]]; then
    export "LUNA_TESTING_ON"=
    echo "Hello world\n" >> ../cat_testing.txt
    mkdir mv_test_dir
else
    unset "LUNA_TESTING_ON" # unset in case testing mode was ran before
fi
if [[ $1 = "--debug" ]]; then # opens debugging interface
    lldb ./luna.sh
elif [[ $1 = "--leaks" ]]; then # checking for memory leaks
    leaks -atExit -- ./luna.sh
else
    ./luna.sh
fi
cd ../..
