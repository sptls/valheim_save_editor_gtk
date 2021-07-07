CXX=g++ -Wall -std=c++20
LIBS=`pkg-config --libs gtkmm-3.0`
CFLAGS=`pkg-config --cflags gtkmm-3.0`

all: clean
	@echo -n Creating resource file... 
	@cd gui; glib-compile-resources --target=resources.cpp --generate-source resources.gresource.xml; cd ..
	@cp gui/resources.cpp src/resources.cpp
	@echo Done.
	@echo -n Compiling... 
	@mkdir build
	@${CXX} -g -o build/vse -rdynamic ${CFLAGS} ${LIBS} main.cpp src/*.cpp
	@echo Done.
	@echo "All done. Run \"vse\" from build folder"
clean:
	@echo -n Deleting build folder and it contents... 
	@rm -rf build/
	@echo Done.
