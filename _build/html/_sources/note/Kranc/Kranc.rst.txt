======
Kranc
======

Introduction
-------------
Kranc is a suite of Mathematica-based computer-algebra packages, which comprise a toolbox to convert certain (tensorial) systems of partial differential evolution equations to parallelized C code for solving initial boundary value problems. **It does this by generating Cactus thorns, allowing use of all the infrastructure provided by Cactus.**

Kranc generates code and Cactus CCL files for:

* Declaring the grid functions which the simulation will use;
* Registering the grid functions for the evolved variables with the MoL thorn;
* Computing the right hand sides of evolution equations so that the time integrator can compute the evolved variables at the next time step;
* Computing finite differences, both using built-in definitions of standard centred finite differencing operators, as well as allowing the user to create customised operators;
* Performing a user-specified calculation at each point of the grid.

.. Kranc interfaces with MoL and one of it’s main functions is to produce the RHS evaluation routine for the evolution equations.

.. The user has to use Kranc mathematica routines to define tensors and their properties and how they relate to the Cactus grid functions.

Get start
^^^^^^^^^^
Run Kranc to build the <thornname> thorn:

.. code-block:: bash

    Kranc/Bin/kranc <thornname>

There should be a new directory, <thornname>, which is the Cactus thorn which has been newly generated from the <thornname>.m Kranc script.

.. note::

    The scripts look for a Kranc installation in the "m" directory, in the Cactus root directory and in $HOME as well as in the location where they find the kranc shell-script if it is in the $PATH. If your Kranc (or kranc) directory is in neither of these places, then you can set the environment variable KRANCPATH to the location of your Kranc installation.

.. include:: ./structure.rst

Creating a Kranc thorn
-----------------------

``CreateThorn[groups, directory, thornName, namedArgs]``

.. note::

    If you want to use TensorTools tensors in calculations, you must call the CreateThornTT function instead of this one.

