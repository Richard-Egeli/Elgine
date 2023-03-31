# Create build directory
mkdir build

# Update submodules
git submodule update --init --recursive
if [ $? -ne 0 ]; then
    echo "Failed to update submodules"
    exit 1
fi

# Build Assimp
cd engine/lib/assimp
cmake CMakeLists.txt
cmake --build .

if [ $? -ne 0 ]; then
    echo "Installing Assimp Failed"
    exit 1
fi

cd ../../..

sh ./bin/build.sh

if [ $? -ne 0 ]; then
    echo" Failed to build the software"
    exit 1
fi


