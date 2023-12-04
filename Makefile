.PHONY: cmake compile run clean

cmake:
	cmake -B cmake

compile:
	cmake --build cmake

run:
	cd bin && ./APTEKA

clean:
	rm cmake build -rf