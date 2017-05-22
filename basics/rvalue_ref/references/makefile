copies_and_refs : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -g -Og -fno-elide-constructors -std=c++11 $^ -o bin/$@

rvalue_references : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -g -Og -std=c++11 $^ -o bin/$@

lvalue_ref : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -g -Og -std=c++11 $^ -o bin/$@

const_lvalue_ref : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -g -Og -std=c++11 $^ -o bin/$@

lvalue_ref_to_rvalue : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -g -Og -std=c++11 $^ -o bin/$@

