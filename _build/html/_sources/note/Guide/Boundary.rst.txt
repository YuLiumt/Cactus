Boundary
=========

Boundary
----------------
Provides a generic interface to boundary conditions, and provides a set of standard boundary conditions for one, two, and three dimensional grid variables.

* scalar boundary conditions
* flat boundary conditions
* radiation boundary conditions
* copy boundary conditions 
* Robin boundary conditions
* static boundary conditions

.. digraph:: foo

   "Boundary" -> "SymBase";

Parameter
^^^^^^^^^^
* Register routine

    >>> Boundary::register_scalar = "yes"
    >>> Boundary::register_flat = "yes"
    >>> Boundary::register_radiation = "yes"
    >>> Boundary::register_copy = "yes"
    >>> Boundary::register_robin = "yes"
    >>> Boundary::register_static = "yes"
    >>> Boundary::register_none = "yes"

Warning
^^^^^^^^^^
* The aliased function 'SymmetryTableHandleForGrid' (required by thorn 'Boundary') has not been provided by any active thorn !

    >>> ActiveThorns = "SymBase"
