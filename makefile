VMManager: main.cpp main.cpp HW/Address.cpp HW/BackingStore.cpp HW/MMU.cpp HW/Ram.cpp \
	OS/FirstInFirstOut.cpp OS/LeastRecentlyUsed.cpp OS/MemoryManager.cpp OS/PageReplacement.cpp Util/global.hpp
	g++ -g3 -O0 -std=c++17 -pedantic -Wall -Wold-style-cast -Wextra -Woverloaded-virtual -I./ -g -o VMManager \
	main.cpp HW/Address.cpp HW/BackingStore.cpp HW/MMU.cpp HW/Ram.cpp \
	OS/FirstInFirstOut.cpp OS/LeastRecentlyUsed.cpp OS/MemoryManager.cpp OS/PageReplacement.cpp
clean:
	rm -rf VMManager


