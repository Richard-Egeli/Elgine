mkdir build

if [ ! -e ./build/embedder.a ]; then 
    g++ -std=c++17 tools/embed/main.cpp -o build/embedder.a
    if [ $? -ne 0 ]; then
        echo "Failed to compile shader embedding tool"
        exit 1
    fi
fi

./build/embedder.a ./shaders ./shaders
if [ $? -ne 0 ]; then
    echo "Embedding shaders failed"
    exit 1
fi

# There seems to sometimes be an issue where the shaders won't load if you run this too quickly.
# So there's a 100ms delay here as a workaround for now
sleep 0.5

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

