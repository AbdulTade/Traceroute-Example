CXX=clang++
CXXFLAGS= -g -O3 -std=c++20
LD=ld
LDFLAGS= --copy-dt-needed-entries
LIBS= -lstdc++ -lpcap -lnet
GDB=gdb

error:
	[ -d build/ ] || mkdir build/
	$(CXX) $(CXXFLAGS) -c -o ./build/error.o  ./utils/Error.cpp

pcap:
	[ -d build/ ] || mkdir build/
	$(CXX) $(CXXFLAGS) -c -o ./build/pcap.o  ./utils/Pcap.cpp #$(LIBS)

traceroute:
	[ -d build/ ] || mkdir build/
	[ -d build ] && $(CXX) $(CXXFLAGS) -c -o ./build/traceroute.o  ./main/Traceroute.cpp

IP:
	[ -d build/ ] || mkdir build/
	[ -d build ] && $(CXX) $(CXXFLAGS) -c -o ./build/ip.o  ./utils/IP.cpp

trace:
	[ -d build/ ] || mkdir build/
	[ -d build ] && $(CXX) -o ./build/trace.elf ./build/traceroute.o ./build/error.o ./build/pcap.o ./build/ip.o $(LIBS)

compile:
	@make error traceroute pcap IP trace

clean:
	[ -d build/ ] && rm -r ./build/


run:
	@printf "\n============================================ OUTPUT ===========================================================\n"
	-@[ -d build/ ] && cd build/ && [ -f trace.elf ] && sudo ./trace.elf
	@printf "\n============================================ DONE   ===========================================================\n"
