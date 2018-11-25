use_known :
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -std=c++14 -c use_known.cpp -o bin/use_known.o
	g++ -Wall -Wno-unused-variable -pedantic -std=c++14 -c Logger.cpp -o bin/Logger.o
	g++ -Wall -Wno-unused-variable -pedantic -std=c++14 bin/use_known.o bin/Logger.o -o bin/use_known

use_not_known :
	@mkdir -p bin/
	g++ -Wall -Wno-unused-variable -pedantic -std=c++14 -c use_not_known.cpp -o bin/use_not_known.o
	g++ -Wall -Wno-unused-variable -pedantic -std=c++14 -c Logger.cpp -o bin/Logger.o
	g++ -Wall -Wno-unused-variable -pedantic -std=c++14 bin/use_not_known.o bin/Logger.o -o bin/use_not_known

