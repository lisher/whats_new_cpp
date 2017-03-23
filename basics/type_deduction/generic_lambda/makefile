generic_lambda : % : %.cpp
	@mkdir -p bin/
	g++ -Wall  -Wno-unused-variable -pedantic -g -std=c++14 $^ -o bin/$@

generic_lambda_cpp11 : %_cpp11 : %.cpp
	@mkdir -p bin/
	g++ -Wall  -Wno-unused-variable -pedantic -g -std=c++11 $^ -o bin/$@

