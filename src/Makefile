CC=g++
FLAGS=-std=gnu++17 -Wall -Wextra -Werror
LIBS_LINUX= -lcheck -lm -lpthread -lrt -lsubunit -D_GNU_SOURCE
LIBS_MACOS=  -lcheck


OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=--coverage -lgtest -lpthread
  CHECK_LEAKS=valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=log.txt
  RUN_MAZE=../build/Maze
else
  LIBS=--coverage -lgtest
  CHECK_LEAKS= leaks -atExit --
  RUN_MAZE=cd ../build/Maze.app/Contents/MacOS;  ./Maze
endif


all: install run

run: install
	$(RUN_MAZE)

install: uninstall
	@mkdir -p ../build
	@qmake6 -o ../build/Makefile ./Maze/Maze.pro
	@make -C ../build > /dev/null 2>&1
	@echo "Done!"

ifneq ($(OS), Linux)
	@mkdir -p ~/Applications ; cp -r ./../build/Maze.app ~/Applications/Maze.app
endif

dvi:
	 open doc.html

dist:
	cd ..; tar -czvf Maze.tar.gz src

tests: clean
	$(CC) $(FLAGS) backend/*.cc test.cc $(LIBS) && ./a.out

gcov_report: tests
	lcov --no-external --capture --directory . --output-file coverage.info --ignore-errors mismatch
	genhtml -o  report coverage.info
	open ./report/index.html

style:
	clang-format -style=google -i backend/*.cc backend/*.h Maze/*.cpp Maze/*.h
	clang-format -style=google -n backend/*.cc backend/*.h Maze/*.cpp Maze/*.h

leaks: tests
	$(CHECK_LEAKS) ./a.out

uninstall: clean
	cd ..; rm -rf build

clean:
	@rm -rf ../build ../.vscode a.out *.gcno *.gcda *.info coverage_report report build-Maze-Desktop-Debug build-Maze-Desktop_x86_darwin_generic_mach_o_64bit-Debug log.txt
	
