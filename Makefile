CPPC=g++
CPPFLAGS= -std=c++11 -g -Wall

test: rbtree_test.cpp
	$(CPPC) $(CPPFLAGS) -o rbtree_test rbtree_test.cpp
