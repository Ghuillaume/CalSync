echo "Warning : installation needs cmake and make installed"
sleep 3
make clean
rm -rf lib/qjson/build
mkdir lib/qjson/build
cd lib/qjson/build/
cmake ..
make
cd ../../../
make
make clean
