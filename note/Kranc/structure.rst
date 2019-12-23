Data structures
----------------
Mathematica does not have the concept of a C++ class or a C structure, in which collections of named objects are grouped together for ease of manipulation. Instead, we have defined a Kranc structure as a list of rules of the form ``key -> value``.



Name
^^^^^
The name of a calculation is a string which will be used as the function name in Cactus.

    >>> Name -> "Example"

.. note::

    Only the Name key is required; all the others take default values if omitted.