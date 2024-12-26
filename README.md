# jaclar
just another C Linear Algebra runtime

jaclar aims to facilitate trivial linear algebra tasks in the REPL way, this repo is a dump of code aimed to be used at my very own shell, [jsh](https://github.com/Jcee02/jsh).

utils include:

- A series of macros to facilitate inline math functions
- 1-based indexing heap-allocated vectors, matrices and tensors for any numerical type in C
- Functions to cast a matrix/vectors type to any numerical type
- Create submatrices of available allocated matrices
- Cleanup functions for any matrix, vector, tensor or submatrix


My current efforts are poured on integrating builtins for [jsh](https://github.com/Jcee02/jsh), aimed to be a versatile tool to evaluate linear operators for algebraic objects in a REPL fashion.
