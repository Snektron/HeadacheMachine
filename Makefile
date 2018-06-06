all: compile

compile:
	@echo Compiling headache...
	@$(CXX) -oheadache -O3 -std=c++17 -Isrc/ src/transpiler.cpp

clean:
	@echo Cleaning...
	@rm -f headache
