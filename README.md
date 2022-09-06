# Matrix2D

Class, which represents a matrix m*n, where m and n are small numbers. The class should implement the following methods:
- support moving and copying
- support iterating over elements
- matrix horizontal concatination with operator '|'
- indexing elements with operator []
- operator '+' to calculate per-element sum of matrices.

Comments on implementation:
- indexing by [] is implemented by 2 methods: 1) with the help of pair a[{i,j}] and 2) in the form of [i][j] with the help of std::span
- used C++20, tested with XCode Version 13.4.1 and Microsoft Visual Studio 2022
