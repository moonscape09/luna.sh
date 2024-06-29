if [ -d "build" ]; then
    rm -r build
fi
mkdir build
cp -r src build/src
cp -r tests build/tests
cd build/src
g++ -std=c++20 luna.cpp shell.cpp command.cpp ../tests/test.cpp -o luna.sh
if [[ $1 = "--testing" ]]; then
    export "LUNA_TESTING_ON"=
    echo "Hello world\n" >> ../cat_testing.txt
    mkdir mv_test_dir
else
    unset "LUNA_TESTING_ON" # unset in case testing mode was ran before
fi
if [[ $1 = "--debug" ]]; then
    lldb ./luna.sh
else
    ./luna.sh
fi
cd ../..
