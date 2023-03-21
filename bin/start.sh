mkdir build

cd build

cmake -G Ninja ..
if [ $? -ne 0 ]; then
    echo "CMake failed"
    exit 1
fi

ninja
if [ $? -ne 0 ]; then
    echo "Ninja failed"
    exit 1
fi

./Elgine
if [ $? -ne 0 ]; then
    echo "Elgine failed"
    exit 1
fi
