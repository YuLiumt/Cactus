======
Kranc
======

Kranc is a suite of Mathematica-based computer-algebra packages, which comprise a toolboxto convert certain (tensorial) systems of partial differential evolution equations to parallelized C code for solving initial boundary value problems. It does this by generating Cactus thorns, allowing use of all the infrastructure provided by Cactus.

Kranc interfaces with MoL and one of it’s main functions is to produce the RHS evaluation routine for the evolution equations.

The user has to use Kranc mathematica routines to define tensors and their properties and how they relate to the Cactus grid functions.