I/O
====
API
----
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