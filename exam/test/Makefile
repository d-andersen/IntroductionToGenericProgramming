CXX=g++-11
CPPFLAGS=-I../src
CXXFLAGS=-std=c++20 -O2
LDFLAGS=

EXE=test_init_copy_move \
test_mutable_bidirectional_no_props \
test_mutable_directed_no_props \
test_mutableprop_bidirectional_w_props \
test_mutableprop_directed_w_props \
test_topo_sort

.PHONY: all

all: $(EXE)

test_init_copy_move: test_init_copy_move.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

test_mutable_directed_no_props: test_mutable_directed_no_props.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

test_mutable_bidirectional_no_props: test_mutable_bidirectional_no_props.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

test_mutableprop_directed_w_props: test_mutableprop_directed_w_props.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

test_mutableprop_bidirectional_w_props: test_mutableprop_bidirectional_w_props.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

test_topo_sort: test_topo_sort.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

test:
	./test_init_copy_move
	@echo
	./test_mutable_directed_no_props
	@echo
	./test_mutable_bidirectional_no_props
	@echo
	./test_mutableprop_directed_w_props
	@echo
	./test_mutableprop_bidirectional_w_props
	@echo
	./test_topo_sort

.PHONY: clean
clean:
	rm -f $(EXE) *.o ../src/*.o