Objective -- The goal of this assignment is to implement a multithreaded solution for critical section problem using the three techniques discussed in the class: Test_And_Set, Test_And_Set with Bounded Waiting and Compare_And_Swap. You have to implement these three algorithms and compare the time taken for each thread to access the critical section. Implement all the algos in C++.
Running :

Unzip and place the files in a directory
The input is read from inp-params.txt file.

Eg. of inp-params.txt file:
10 1000 20 30

1) To execute --------- Assgn2-TASCS16BTECH11032.cpp

COMPILE --  g++ -std=c++11 Assgn2-TASCS16BTECH11032.cpp -pthread
EXECUTE -- ./a.out

2) To execute --------- g++ -std=c++11 Assgn2-TAS_FairCS16BTECH11032.cpp -pthread

COMPILE --  g++ -std=c++11 Assgn2-TAS_FairCS16BTECH11032.cpp -pthread
EXECUTE -- ./a.out

2) To execute --------- g++ -std=c++11 Assgn2-CASCS16BTECH11032.cpp -pthread

COMPILE --  g++ -std=c++11 Assgn2-CASCS16BTECH11032.cpp -pthread
EXECUTE -- ./a.out
