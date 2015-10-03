How to build
==============
Type 'make' in the ssfi directory


Files built
===========
ssfi -d <dir> [-h | -v | --N <number of threads>]
 The executable that meets the requirements specified. Type -h to learn more
  about the process and what flags can be specified to the user.
test_file_locator
  Tests the FileLocator class and verifies the text files under unit_test/.
  Asserts if the expected files are not present.
test_parser.
  Tests the Parser class that reads in the files under unit_tests/ and
  validates that data was read in correctly. Asserts if the data read in does
  not match what was expected.


Review of the assignment
=========================
My experience with boost prior to this exercise was minimal. I was quite
impressed with it and would definitely look forward to using it along with
C++11.

If I had enough time I would write a test for the worker queue Boost ASIO subclass I created.

My unit tests are very simple. They assert on simple checks and wouldn't provideothe best feedback to a developer, but are a starting point.
