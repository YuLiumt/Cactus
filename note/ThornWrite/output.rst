I/O
====
API
----
.. c:function:: int CCTK_VarIndex(const char *varname)

    Get the index for a variable.

    :Discussion: The variable name should be the given in its fully qualified form, that is ``<implementation>::<variable>`` for PUBLIC or PROTECTED variables and ``<thorn>::<variable>`` for PRIVATE variables.

    :param char varname: The name of the variable.
    :error: * **-1** - no variable of this name exists
            * **-2** - no failed to catch error code from ``Util_SplitString``
            * **-3** - given full name is in wrong format
            * **-4** - memory allocation failed

    >>> index = CCTK_VarIndex("evolve::phi"); 
    >>> index = CCTK_VarIndex("evolve::vect[0]");

.. c:function:: int CCTK_GroupIndexFromVarI(int varindex)

    Given a variable index, returns the index of the associated group
 
    :param int varindex: The index of the variable
    :result: **groupindex** (*int*) - The index of the group

    >>> index = CCTK_VarIndex("evolve::phi");
    >>> groupindex = CCTK_GroupIndexFromVarI(index);

.. c:function:: char CCTK_FullName(int index)

    Given a variable index, returns the full name of the variable
 
    :Discussion: The full variable name is in the form ``<implementation>::<variable>`` for PUBLIC or PROTECTED variables and ``<thorn>::<variable>`` for PRIVATE variables.

    :param int index: The variable index
    :result: **implementation** (*char*) - The full variable name

    >>> name = CCTK_FullName(index);

.. c:function:: int CCTK_VarTypeI(int index)

    Provides variable type index from the variable index

    :Discussion: The variable type index indicates the type of the variable. Either character, int, complex or real. The group type can be checked with the Cactus provided macros for CCTK_VARIABLE_INT, CCTK_VARIABLE_REAL, CCTK_VARIABLE_COMPLEX or CCTK_VARIABLE_CHAR.

    :param int index: The variable index
    :result: **type** (*int*) - The variable type index

    >>> vtype = CCTK_VarTypeI(index);
    >>> if (vtype == CCTK_VARIABLE_REAL) {
    >>>     /* Here goes your code */
    >>> }

.. c:function:: int CCTK_GroupTypeI(int group)

    Provides a group type index given a group index

    :Discussion: A group type index indicates the type of variables in the group. The group type can be checked with the Cactus provided macros for CCTK_SCALAR, CCTK_GF, CCTK_ARRAY.

    :param int group: Group index.
    :error: **-1** - the given group index is invalid.

    >>> gtype = CCTK_GroupTypeI(gindex);
    >>> if (gtype == CCTK_GF) {
    >>>     /* Here goes your code */
    >>> }

.. c:function:: void CCTK_VarDataPtrI(const cGH * cctkGH, int timelevel, int index)

    Returns the data pointer for a grid variable from the variable index.

    :param cctkGH: pointer to CCTK grid hierarchy
    :param int timelevel: The timelevel of the grid variable
    :param int index: The index of the variable

    >>> CCTK_REAL *data = NULL;
    >>> vindex = CCTK_VarIndex("evolve::phi"); 
    >>> data = (CCTK_REAL*) CCTK_VarDataPtrI(cctkGH, 0, vindex);

.. c:function:: int CCTK_OutputVarAs(const cGH *cctkGH, const char *variable, const char *alias)

    Output a single variable as an alias by all I/O methods.

    :Discussion: If the appropriate file exists the data is appended, otherwise a new file is created. Uses ``alias`` as the name of the variable for the purpose of constructing a filename.

    :param cctkGH: pointer to CCTK grid hierarchy
    :param char variable: full name of variable to output
    :param char alias: alias name to base the output filename on
    :result: **istat** (*int*) - the number of IO methods which did output of variable
    :error: **negative** - if no IO methods were registered

    >>> CCTK_OutputVarAs(cctkGH, "HydroBase::rho", "rho");

.. c:function:: int CCTK_OutputVarAsByMethod(const cGH *cctkGH, const char *variable, const char *method, const char *alias)

    Output a variable variable using the method method if it is registered. Uses alias as the name of the variable for the purpose of constructing a filename. If the appropriate file exists the data is appended, otherwise a new file is created.

    :param cctkGH: pointer to CCTK grid hierarchy
    :param char variable: full name of variable to output
    :param char method: method to use for output
    :param char alias: alias name to base the output filename on
    :result: **istat** (*int*) - zero for success
    :error: **negative** - indicating some error

.. c:function:: int CCTK_OutputVarByMethod(const cGH *cctkGH, const char *variable, const char *method)

    Output a variable variable using the IO method method if it is registered. If the appropriate file exists the data is appended, otherwise a new file is created.

    :param cctkGH: pointer to CCTK grid hierarchy
    :param char variable: full name of variable to output
    :param char method: method to use for output
    :result: **istat** (*int*) - zero for success
    :error: **negative** - indicating some error