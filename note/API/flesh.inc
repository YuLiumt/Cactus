Cactus.Flesh
=============

CCTK Function 
--------------
.. c:function:: int CCTK_ActiveTimeLevels(const cGH *cctkGH, const char *groupname| int groupindex| const char *varname| int varindex)

    Returns the number of active time levels for a group.

    :Discussion: This function returns the number of timelevels for which storage has been activated.

    :param cGH: Pointer to a valid Cactus grid hierarchy.
    :param char groupname: Name of the group.
    :param int groupindex: Index of the group.
    :param char varname: Name of a variable in the group.
    :param int varindex: Index of a variable in the group.

    :error: Negative value: Illegal arguments given.

.. c:function:: int CCTK_ERROR(const char *message)

    Macro to print a single string as error message and stop the code.

    :Discussion: To include variables in the error message from C, you can use the routine :c:func:`CCTK_VError` which accepts a variable argument list.

    :param char message: The error message to print

.. py:function:: CCTK_FirstVarIndex(const char* group_name)

    Given a group name, returns the first variable index in the group.
    
    :Discussion: If the group contains :math:`N > 0` variables, and :math:`V` is the value of first varindex returned by this function, then the group’s variables have variable indices :math:`V, V+1, V+2, \dots , V+N-1`.

    :param char group_name: The character-string name of the group.
    :return: The first variable index in the group.
    :error: * -1 Group name is invalid.
            * -2 Group has no members.

.. c:function:: int CCTK_GFINDEX3D(cctkGH,i,j,k)

    Find the 1-dimensional index which is needed from the multidimensional indices

    :param cGH: Pointer to a valid Cactus grid hierarchy.
    :param int ijk: multidimensional indices
    :return: (i + cctkGH->cctk_ash[0] * (j + cctkGH->cctk_ash[1] * k))

.. c:function:: void CCTK_Info(*thorn, *message)

    Print an information message to stdout. 
    
    :Discussion: For a multiprocessor run, only runtime information from processor zero will be printed to screen by default.

    :param char thorn: Name of originating thorn
    :param char message: the warning message to output


.. py:function:: CCTK_Reduce(const cGH *GH, int proc, int operation_handle, int num_out_vals, int type_out_vals, void *out_vals, int num_in_fields, ... )

    Generic routine for doing a reduction operation on a set of Cactus variables.

    :param GH: pointer to the grid hierarchy
    :param int proc: processor that receives the result of the reduction operation (a negative value means that all processors get the result)
    :param int operation_handle: the handle specifying the reduction operator
    :param int num_out_vals: number of elements in the reduction output
    :param int type_out_vals: datatype of the output values
    :param out_vals: pointer to buffer holding the output values
    :param int num_in_fields: number of input fields passed in the variable argument list
    :param <...>: list of variables indices of input fields


.. py:function:: CCTK_ReductionHandle(const char * reduction)

    Handle for given reduction method

    :Discussion: Reduction methods should be registered at CCTK_STARTUP.
    :param char name: name of the reduction method required
    :return: handle returned for this method


.. c:function:: int CCTK_VarIndex(const char *varname)

    Get the index for a variable.

    :Discussion: The variable name should be the given in its fully qualified form, that is <implementation>::<variable> for a public or protected variable, and <thornname>::<variable> for a private variable. For vector variables, the zero-based component index should be included in square brackets after the variable name.
    :param char varname: The name of the variable.
    :error: * -1 no variable of this name exists
            * -2 failed to catch error code from Util_SplitString
            * -3 given full name is in wrong format
            * -4 memory allocation failed
    
    >>> index = CCTK_VarIndex("evolve::phi"); 
    >>> index = CCTK_VarIndex("evolve::vect[0]")

.. py:function:: CCTK_VarDataPtrI(const cGH * cctkGH, int timelevel, int index)

    Returns the data pointer for a grid variable from the variable index.

    :param cctkGH: pointer to CCTK grid hierarchy
    :param int timelevel: The timelevel of the grid variable
    :param int index: The index of the variable


.. c:function:: void CCTK_VInfo(*thorn, *format, ...)

    Info output routine with variable argument list

    :Discussion: only be called from C, because Fortran doesn’t know about variable argument lists.

    :param char thorn: Name of originating thorn
    :param char format: format string for message


.. c:function:: int CCTK_VWarn(level, line, *file, *thorn, *format, ...)

    If the given warning level is less or equal to the current one, it will print the given warning message to stderr.

    :param int level: Warn Level

.. c:function:: int CCTK_WARN(int level, const char *message)

    Macro to print a single string as a warning message and possibly stop the code

    :param int level: The warning level to use
    :param char message: The warning message to print.

Util Function
--------------

.. py:function:: Util_GetHandledData(cHandledData *storage, int handle)

    Gets a pointer to the data corresponding to the given handle.

    :param int level: Warn Level