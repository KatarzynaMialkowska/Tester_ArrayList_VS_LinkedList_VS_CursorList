
.SUFFIXES: .cxx .o .x .hxx
NAME1 = ArrayList
NAME2 = stdlist
NAME3 = generator
NAME4 = generator_overflow
NAME5 = generator_underflow
NAME6 = LinkedList
NAME7 = CursorList

CXX1 = $(NAME1).cxx
CXX2 = $(NAME2).cxx
CXX3 = $(NAME3).cxx
CXX4 = $(NAME4).cxx
CXX5 = $(NAME5).cxx
CXX6 = $(NAME6).cxx
CXX7 = $(NAME7).cxx

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x
EXEC6 = $(NAME6).x
EXEC7 = $(NAME7).x

CO=g++
FLAGS= -std=c++11


.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6) $(EXEC7)


$(EXEC1):
	$(CO) -o $@ $(CXX1) $(FLAGS) 

$(EXEC2): 
	$(CO) -o $@ $(CXX2) $(FLAGS)

$(EXEC3):
	$(CO) -o $@ $(CXX3) $(FLAGS) 

$(EXEC4):
	$(CO) -o $@ $(CXX4) $(FLAGS) 

$(EXEC5):
	$(CO) -o $@ $(CXX5) $(FLAGS) 

$(EXEC6):
	$(CO) -o $@ $(CXX6) $(FLAGS) 

$(EXEC7):
	$(CO) -o $@ $(CXX7) $(FLAGS) 



##TESTER##

#test 1 - compare arrayList z std::list#
test1: $(EXEC1) $(EXEC2) $(EXEC3) 

.PHONY: test_arraylist_1
test_arraylist_1: test1
	@echo "\n(I)\n*list vs std::list*\nLOSOWE DANE\n"
	@./$(EXEC3) > test1.txt
	@echo "\n*testing own array list. wait...*\n"
	@time ./$(EXEC1) < test1.txt > arraylist1.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test1.txt > stdlist1.txt
	@echo "\n*output file:*\n"
	@diff -s arraylist1.txt stdlist1.txt

#test 2 - comparison arrayList with std::list, the given number of operations#
.PHONY: test_arraylist_2
test_arraylist_2: test1
	@echo "\n(II)\n*list vs STD::list*\nDEFINED NUMBER OF OPERATIONS\n"
	@./$(EXEC3) 100 > test2.txt 
	@echo "\n*testing own array list. wait...*\n"
	@time ./$(EXEC1) < test2.txt > arraylist2.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test2.txt > stdlist2.txt
	@echo "\n*output file:*\n"
	@diff -s arraylist2.txt stdlist2.txt

#test 3 - comparison  arrayList with std::list when overflow occurs#
test2: $(EXEC1) $(EXEC4) $(EXEC2)
.PHONY: test_arraylist_3
test_arraylist_3: test2
	@echo "\n(III)\n*list vs STD::list*\nTBUFFER OVERFLOW TEST\n"
	./$(EXEC4) 10001 > test3.txt
	@echo "\n*testing own array list. wait...*\n"
	@time ./$(EXEC1) < test3.txt > arraylist3.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test3.txt > stdlist3.txt
	@echo "\n*output file:*\n"
	@diff -s arraylist3.txt stdlist3.txt
	
#test 4 - comparison arrayList with std::list when underflow occurs#
test3: $(EXEC1) $(EXEC5) $(EXEC2)
.PHONY: test_arraylist_4
test_arraylist_4: test3
	@echo "\n(IV)\n*list vs STD::list*\nTEST OPERATION OF POP() FOR EMPTY BUFFER\n"
	@./$(EXEC5) > test4.txt
	@echo "\n*testing own array list. wait...*\n"
	@time ./$(EXEC1) < test4.txt > arraylist4.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test4.txt > stdlist4.txt
	@echo "\n*output file:*\n"
	@diff -s arraylist4.txt stdlist4.txt

#test 5 - comparison linkedList with std::list#
test5: $(EXEC6) $(EXEC3) $(EXEC2) 

.PHONY: test_linkedlist_1
test_linkedlist_1: test5
	@echo "\n(I)\n*linked list vs std::list*\nRANDOM DATA\n"
	@./$(EXEC3) > test5.txt
	@echo "\n*testing own linked list. wait...*\n"
	@time ./$(EXEC6) < test5.txt > linkedlist5.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test5.txt > stdlist5.txt
	@echo "\n*output file:*\n"
	@diff -s linkedlist5.txt stdlist5.txt

#test 6 - comparison linkedList with std::list, the given number of operations#
.PHONY: test_linkedlist_2
test_linkedlist_2: test5
	@echo "\n(II)\n*linked list vs STD::list*\nDEFINED NUMBER OF OPERATIONS\n"
	@./$(EXEC3) 100 > test6.txt 
	@echo "\n*testing own linked list. wait...*\n"
	@time ./$(EXEC6) < test6.txt > linkedlist6.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test6.txt > stdlist6.txt
	@echo "\n*output file:*\n"
	@diff -s linkedlist6.txt stdlist6.txt

#test 7 - comparison linkedList with std::list when overflow occurs#
test6: $(EXEC6) $(EXEC4) $(EXEC2)
.PHONY: test_arraylist_3
test_linkedlist_3: test6
	@echo "\n(III)\n*linkedList vs STD::list*\nBUFFER OVERFLOW TEST\n"
	./$(EXEC4) 10001 > test7.txt
	@echo "\n*testing own linked list. wait...*\n"
	@time ./$(EXEC6) < test7.txt > linkedlist7.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test7.txt > stdlist7.txt
	@echo "\n*output file:*\n"
	@diff -s linkedlist7.txt stdlist7.txt
	
#test 8 - comparison linkedList with std::list when underflow occurs#
test7: $(EXEC6) $(EXEC5) $(EXEC2)
.PHONY: test_arraylist_4
test_linkedlist_4: test7
	@echo "\n(IV)\n*linkedList vs STD::list*\nTEST OPERATION OF POP() FOR EMPTY BUFFER\n"
	@./$(EXEC5) > test8.txt
	@echo "\n*testing own linked list. wait...*\n"
	@time ./$(EXEC6) < test8.txt > linkedlist8.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test8.txt > stdlist8.txt
	@echo "\n*output file:*\n"
	@diff -s linkedlist8.txt stdlist8.txt

#test 9 - comparison cursorList with std::list#
test8: $(EXEC7) $(EXEC2) $(EXEC3) 

.PHONY: test_cursorlist_1
test_cursorlist_1: test8
	@echo "\n(I)\n*cursorlist vs std::list*\nRANDOM DATA\n"
	@./$(EXEC3) > test9.txt
	@echo "\n*testing own cursor list. wait...*\n"
	@time ./$(EXEC7) < test9.txt > cursorlist9.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test9.txt > stdlist9.txt
	@echo "\n*output file:*\n"
	@diff -s cursorlist9.txt stdlist9.txt


#test 10 - comparison cursorList with std::list, the given number of operations#
.PHONY: test_cursorlist_2
test_cursorlist_2: test8
	@echo "\n(I)\n*cursorlist vs std::list*\nDEFINED NUMBER OF OPERATIONS\n"
	@./$(EXEC3) 100 > test10.txt
	@echo "\n*testing own cursor list. wait...*\n"
	@time ./$(EXEC7) < test10.txt > cursorlist10.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test10.txt > stdlist10.txt
	@echo "\n*output file:*\n"
	@diff -s cursorlist10.txt stdlist10.txt

test9: $(EXEC7) $(EXEC4) $(EXEC2)
#test 11 - comparison cursorList with std::list when overflow occurs#
.PHONY: test_cursorlist_3
test_cursorlist_3: test9
	@echo "\n(I)\n*cursorlist vs std::list*\nOVERFLOW\n"
	@./$(EXEC4) > test11.txt
	@echo "\n*testing own cursor list. wait...*\n"
	@time ./$(EXEC7) < test11.txt > cursorlist11.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test11.txt > stdlist11.txt
	@echo "\n*output file:*\n"
	@diff -s cursorlist11.txt stdlist11.txt

test10: $(EXEC7) $(EXEC5) $(EXEC2)
#test 12 - comparison cursorList with std::list when overflow occurs#
.PHONY: test_cursorlist_4
test_cursorlist_4: test10
	@echo "\n(I)\n*cursorlist vs std::list*\nUNDERFLOW\n"
	@./$(EXEC5) > test12.txt
	@echo "\n*testing own cursor list. wait...*\n"
	@time ./$(EXEC7) < test12.txt > cursorlist12.txt
	@echo "\n*testing std::list. wait...*\n"
	@time ./$(EXEC2) < test12.txt > stdlist12.txt
	@echo "\n*output file:*\n"
	@diff -s cursorlist12.txt stdlist12.txt


.PHONY: test
test: test_arraylist_1 test_arraylist_2 test_arraylist_3 test_arraylist_4 test_linkedlist_1 test_linkedlist_2 test_linkedlist_3 test_linkedlist_4 test_cursorlist_1 test_cursorlist_2 test_cursorlist_3 test_cursorlist_4

.PHONY: clean
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x *.txt core core* a.out; rm -rf ${LIB_DIR}