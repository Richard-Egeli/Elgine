# mkdir build

# cd build

sh ./bin/build.sh
if [ $? -ne 0 ]; then
    echo "Failed to build"
    exit 1
fi

./build/Elgine
if [ $? -ne 0 ]; then
    echo "Elgine failed"
    exit 1
fi
