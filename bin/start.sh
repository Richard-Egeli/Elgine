mkdir build

cd build

./embedder.a ../shaders ../shaders
if [ $? -ne 0 ]; then
    echo "Embedding shaders failed"
    exit 1
fi

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
