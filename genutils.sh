# warning: this cleans!!

# use bear to generate compile commands

rm -rf ./build/*
cd build
cmake ..
bear -- make -j4
cd ..