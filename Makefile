CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

SRC = src/main.cpp src/ContactList.cpp src/PhoneBST.cpp src/ContactBook.cpp src/Validation.cpp

contacts: $(SRC) $(wildcard src/*.h)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

run: contacts
	./contacts data/contacts.txt

test: contacts
	bash tests/run_tests.sh

clean:
	rm -f contacts contacts.exe

.PHONY: run test clean
