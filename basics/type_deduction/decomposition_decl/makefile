tie : % : %.cpp
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -std=c++14 $^ -o bin/$@

GCC7 = g++-7.1

deco_decl : % : %.cpp
	@mkdir -p bin/
	$(GCC7) -Wall -Wno-unused-variable -Wno-unused-but-set-variable -pedantic -std=c++1z $^ -o bin/$@

