CXX=g++
LIBS=`pkg-config --libs gtkmm-3.0`
CFLAGS=`pkg-config --cflags gtkmm-3.0`

all: clean
	@echo Compiling...
	@mkdir build build/gui
	@${CXX} -g -o build/vse -rdynamic ${CFLAGS} ${LIBS} *.cpp
	@echo Done.
	@cp gui/* build/gui/
	@echo "All done. Run \"vse\" from build folder"
clean:
	@echo Deleting build folder and it contents...
	@rm -rf build/
	@echo Done
