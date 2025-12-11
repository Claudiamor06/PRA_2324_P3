bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp


bin/testHashTable: testHashTable.cpp HashTable.h Dict.h TableEntry.h
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

bin/testBSTree: BSTree.h BSNode.h testBSTree.cpp
	g++ testBSTree.cpp -o bin/testBSTree

bin/testBSTreeDict: testBSTreeDict.cpp Dict.h BSTreeDict.h BSNode.h TableEntry.h
	mkdir -p bin
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp

clean:
	rm -rf *.o *.gch bin

