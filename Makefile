ROOT=`root-config --cflags --glibs`
CXX=g++
CXXFLAGS=-Wall -O2 -Wextra -Wno-unused-local-typedefs -Wno-deprecated-declarations -std=c++11

MKDIR_BIN=mkdir -p $(PWD)/bin

all: mkdirBin bin/TwoParticleCorrelation.exe

mkdirBin:
	$(MKDIR_BIN)
bin/TwoParticleCorrelation.exe: src/TwoParticleCorrelation.cc
	$(CXX) src/TwoParticleCorrelation.cc -o bin/TwoParticleCorrelation.exe  -I../include -pedantic -W $(CXXFLAGS) -Wshadow -fPIC -ldl $(ROOT) -I $(PWD)

clean:
	rm -f *~
	rm -f \#*.*#
	rm -f $(PWD)/include/#*.*#
	rm -f $(PWD)/include/*~
	rm -f $(PWD)/src/#*.*#
	rm -f $(PWD)/src/*~
	rm -f $(PWD)/bash/#*.*#
	rm -f $(PWD)/bash/*~
	rm -f $(PWD)/paths/#*.*#
	rm -f $(PWD)/paths/*~
	rm -f $(PWD)/bin/*.exe
	rmdir bin
.PHONY: all
