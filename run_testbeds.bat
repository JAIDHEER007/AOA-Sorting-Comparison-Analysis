g++ -std=c++17 -I include/ -c src/helper.cpp -o obj/helper.o
g++ -std=c++17 -I include/ -c src/algorithms.cpp -o obj/algorithms.o
g++ -std=c++17 -I include/ -c testbeds/testbed_1.cpp -o obj/testbed_1.o
g++ -std=c++17 -I include/ -c testbeds/testbed_2.cpp -o obj/testbed_2.o
g++ -std=c++17 -I include/ -c testbeds/testbed_3.cpp -o obj/testbed_3.o
g++ -std=c++17 -I include/ -c testbeds/testbed_4.cpp -o obj/testbed_4.o
g++ -std=c++17 -I include/ -c testbeds/testbed_5.cpp -o obj/testbed_5.o
g++ -std=c++17 -I include/ -c testbeds/testbed_6.cpp -o obj/testbed_6.o
g++ -std=c++17 -I include/ -c testbeds/testbed_7.cpp -o obj/testbed_7.o
g++ -std=c++17 -I include/ -c testbeds/testbed_8.cpp -o obj/testbed_8.o
g++ -std=c++17 -I include/ -c testbeds/testbed_9.cpp -o obj/testbed_9.o
g++ -std=c++17 -I include/ -c testbeds/testbed_10.cpp -o obj/testbed_10.o

g++ obj/testbed_1.o obj/helper.o obj/algorithms.o -o bin/testbed_1.exe
g++ obj/testbed_2.o obj/helper.o obj/algorithms.o -o bin/testbed_2.exe
g++ obj/testbed_3.o obj/helper.o obj/algorithms.o -o bin/testbed_3.exe
g++ obj/testbed_4.o obj/helper.o obj/algorithms.o -o bin/testbed_4.exe
g++ obj/testbed_5.o obj/helper.o obj/algorithms.o -o bin/testbed_5.exe
g++ obj/testbed_6.o obj/helper.o obj/algorithms.o -o bin/testbed_6.exe
g++ obj/testbed_7.o obj/helper.o obj/algorithms.o -o bin/testbed_7.exe
g++ obj/testbed_8.o obj/helper.o obj/algorithms.o -o bin/testbed_8.exe
g++ obj/testbed_9.o obj/helper.o obj/algorithms.o -o bin/testbed_9.exe
g++ obj/testbed_10.o obj/helper.o obj/algorithms.o -o bin/testbed_10.exe


bin\testbed_1.exe
bin\testbed_2.exe
bin\testbed_3.exe
bin\testbed_4.exe
bin\testbed_5.exe
bin\testbed_6.exe
bin\testbed_7.exe
bin\testbed_8.exe
bin\testbed_9.exe
bin\testbed_10.exe

python plot.py