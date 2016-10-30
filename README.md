#CS 3251: Intermediate Software Design
##Programming Assignment 4


This assignment requires you to implement the Adapter pattern. The assignment integrates the ArrayList and LinkedList classes into a new QueueBase, QueueAdapter, StackBase, and StackAdapter template class hierarchy that can be used to dynamically select the type of List strategy to use in the program at runtime. The use of Adapter ensures that no changes are required to the existing ArrayList and LinkedList classes.  You must implement _QueueAdapter.cpp_, _QueueBase.cpp_, _StackAdapter.cpp_ and _StackBase.cpp_.  They should all be placed in the /src directory.

The shells for the assignment are available in the _/src_ and _/include_ directories.  Use the provided ScopedArray.h, ArrayList.[h, cpp], ArrayListIterators.h, LinkedList.[h, cpp] and LinkedListIterators.h files.  You may use your versions of these files, but ensure that your classes comply with the expected behavior.

The _CMakeLists.txt_ and the testing files are written for you and do not require any modification.  You are NOT to edit any portions of the provided files. 

##Graduate Students:
 
Graduate students are to complete the assignment as described above and additionally implement a memory pool for the _LinkedListNode_ class.  Graduate students are required to research how to implement the memory pool.  Implementing a memory pool requires overriding _operator new()_ and _operator delete()_.  This is an advanced topic, and we will not specifically cover this topic in class; however, some slides have been provided with the assignment, see the _/docs_ directory.  These slides will not be sufficient for completing the assignment.  You will need to do some independent research to complete this portion of the assignment.  Remember to provide complete references for all sources that you use to understand memory pools.

To enable testing your memory code you must uncomment the #define on line 11 of _/tests/tests.h_.  This will impact code in _/tests/stackTest.cpp_, _/include/LinkedList.h_ and in _/src/LinkedList.cpp_.  You must make all of your changes to the implementation in _/src/LinkedList.cpp_.
 

###REMINDERS:

* Students are not permitted to use Visual Studio or alternate build systems for your programming assignments.  You must use the supplied _CMakeLists.txt_ file.

* Ensure that your name, vunetid, email address, and the honor code appear in the header comments of all files that are to be graded.

* Your programs(s) must compile locally with no warnings or errors.  We will use Travis-CI to test compilation across both GCC and CLang compilers.

* Your program(s) should always have an exit code of 0.  A non-zero exit code is reason to worry and must be corrected for full points.

* All students are required to use the CS 3251 coding standard, available on the course web page and provided to you on the first day of class. Points will be deducted for not following the coding standard.
  
* When submitting the assignment, all files that are provided to you, plus your solution files have been submitted. All files necessary to compile and run your program must reside in the GitHub.com repository.
