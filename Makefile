bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp


bin/testHashTable: testHashTable.cpp HashTable.h Dict.h TableEntry.h
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

bin/testBSTree: BSTree.h BSNode.h testBSTree.cpp
	g++ testBSTree.cpp -o bin/testBSTree


clean:
	rm -rf *.o *.gch bin

