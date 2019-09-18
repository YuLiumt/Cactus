EinsteinBase
===============
EinsteinBase thorns define and register basic variables within numerical relativity.

ADMBase
--------
This thorn provides the basic variables used to communicate between thorns doing General Relativity in the 3+1 formalism.

Parameter
^^^^^^^^^^
* Minkowski values in cartesian coordinates

    >>> ADMBase::initial_data = "Cartesian Minkowski"

TODO:

TmunuBase
----------
Provide grid functions for the stress-energy tensor 

.. math::
    T_{\mu v}

ADMMacros
----------
Provides macros for common relativity calculations, using the ADMBase variables.

