mkdir build

if [ ! -e ./build/embedder.a ]; then
    g++ -std=c++17 tools/embed/main.cpp -o build/embedder.a
    if [ $? -ne 0 ]; then
        echo "Failed to compile shader embedding tool"
        exit 1
    fi
fi

./build/embedder.a ./shaders ./engine/include/elgine
if [ $? -ne 0 ]; then
    echo "Embedding shaders failed"
    exit 1
fi

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
