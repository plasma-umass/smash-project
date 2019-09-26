libSmash.so: libSmash.cpp 
	g++ -Wall -I./zstd/lib -I./zstd/ -I./Heap-Layers/ libSmash.cpp -fPIC -shared -lc -ldl -pipe -fomit-frame-pointer -D_REENTRANT=1 -finline-limit=65000 -fkeep-inline-functions -finline-functions -ffast-math -L./zstd/lib -lzstd -o $@

libSmash-debug.so: libSmash.cpp 
	g++ -Wall -I./zstd/lib -I./zstd/ -I./Heap-Layers/ libSmash.cpp -fPIC -shared -lc -ldl -pipe -fomit-frame-pointer -D_REENTRANT=1 -finline-limit=65000 -fkeep-inline-functions -finline-functions -ffast-math -L./zstd/lib -lzstd -g -O0 -o $@

all:
	libSmash
