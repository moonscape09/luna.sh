if [ -d "build" ]; then
    rm -r build
fi
mkdir build
cp -r src build/src
cd build/src
g++ -std=c++20 luna.cpp shell.cpp command.cpp -o luna.sh
./luna.sh
cd ../..
