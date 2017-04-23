simple_class : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -std=c++03 $^ -o bin/$@ -fdump-tree-original

complex_class : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -std=c++03 $^ -o bin/$@

partial : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -std=c++03 $^ -o bin/$@

