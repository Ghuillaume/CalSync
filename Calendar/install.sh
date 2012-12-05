echo "Warning : installation needs cmake, qmake and make installed"
sleep 3
make clean
rm -rf lib/qjson/build
mkdir lib/qjson/build
cd lib/qjson/build/
cmake ..
make
cd ../../../
cp --remove-destination lib/qjson/build/lib/libqjson.so* ./
qmake
make
make clean
