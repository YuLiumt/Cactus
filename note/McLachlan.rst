McLachlan
===========

McLachlan is a state-of-the-art BSSN code for solving the Einstein equations.

ML_ADMConstraints
------------------
ML_ADMConstraints calculates the ADM constraints violation, but directly using potentially higher-order derivatives, and is, in general, preferred over ADMConstraints.

Output
^^^^^^^
* Hamiltonian constraint

    >>> IOHDF5::out2D_vars = "ML_ADMConstraints::ML_Ham"

* Momentum constraints

    >>> IOHDF5::out2D_vars = "ML_ADMConstraints::ML_mom"