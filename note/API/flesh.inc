Cactus.Flesh
=============

CCTK Function 
--------------

.. py:function:: CCTK_FirstVarIndex(const char* group_name)

    Given a group name, returns the first variable index in the group.
    
    :Discussion: If the group contains :math:`N > 0` variables, and :math:`V` is the value of first varindex returned by this function, then the group’s variables have variable indices :math:`V, V+1, V+2, \dots , V+N-1`.

    :param char group_name: The character-string name of the group.
    :return: The first variable index in the group.
    :error: * -1 Group name is invalid.
            * -2 Group has no members.


.. py:function:: CCTK_Info(*thorn, *message)

    Print an information message to stdout

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


.. py:function:: CCTK_VarDataPtrI(const cGH * cctkGH, int timelevel, int index)

    Returns the data pointer for a grid variable from the variable index.

    :param cctkGH: pointer to CCTK grid hierarchy
    :param int timelevel: The timelevel of the grid variable
    :param int index: The index of the variable


.. py:function:: CCTK_VInfo(*thorn, *format, ...)

    Info output routine with variable argument list

    :param char thorn: Name of originating thorn
    :param char format: format string for message


.. py:function:: CCTK_VWarn(level, line, *file, *thorn, *format, ...)

    If the given warning level is less or equal to the current one, it will print the given warning message to stderr.

    :param int level: Warn Level
    :rtype: int

Util Function
--------------

.. py:function:: Util_GetHandledData(cHandledData *storage, int handle)

    Gets a pointer to the data corresponding to the given handle.

    :param int level: Warn Level