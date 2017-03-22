decltype_auto : % : %.cpp
	@mkdir -p bin/
	g++ -Wall  -Wno-unused-variable -pedantic -g -std=c++14 $^ -o bin/$@

overload_operator : % : %.cpp
	@mkdir -p bin/
	g++ -Wall  -Wno-unused-variable -pedantic -g -std=c++14 $^ -o bin/$@

wrapper : % : %.cpp
	@mkdir -p bin/
	g++ -Wall  -Wno-unused-variable -pedantic -g -std=c++14 $^ -o bin/$@

forwarding : % : %.cpp
	@mkdir -p bin/
	g++ -Wall  -Wno-unused-variable -pedantic -g -Og -fno-elide-constructors -std=c++14 $^ -o bin/$@

