Numerical
==========

Interp
--------
.. c:function:: int CCTK InterpGridArrays(const cGH *cctkGH, int N_dims, int local_interp_handle, int param_table_handle, int coord_system_handle, int N_interp_points, const int interp_coords_type_code, const void *const interp_coords[], int N_input_arrays, const CCTK_INT input_array_variable_indices[], int N_output_arrays, const CCTK_INT output_array_type_codes[], void *const output_arrays[])

    Interpolate a list of distributed grid variables. A grid variable can be either a grid function or a grid array.

    :param cGH: Pointer to a valid Cactus grid hierarchy.
    :param int N_dims: Number of dimensions in which to interpolate.
    :param int local_interp_handle: Handle to the local interpolation operator as returned by CCTK_InterpHandle.
    :param int param_table_handle: Handle to a key-value table containing zero or more additional parameters for the interpolation operation. The table is allowed to be modified by the local and/or global interpolation routine(s).
    :param int coord_system_handle: Cactus coordinate system handle defining the mapping between (usually floating-point) coordinates and integer grid subscripts, as returned by CCTK_CoordSystemHandle.
    :param int N_interp_points: The number of interpolation points requested by this processor.
    :param int interp_coords_type_code: One of the CCTK_VARIABLE_* type codes, giving the data type of the interpolation-point coordinate arrays pointed to by interp coords[]. All interpolation-point coordinate arrays must be of the same data type.
    :param interp_coords[]: (Pointer to) an array of N dims pointers to 1-D arrays giving the coordinates of the interpolation points requested by this processor. These coordinates are with respect to the coordinate system defined by coord system handle.
    :param int N_input_arrays: The number of input variables to be interpolated. If N input arrays is zero then no interpolation is done; such a call may be useful for setup, interpolator querying, etc. Note that if the parameter table entry operand indices is used to specify a nontrivial (e.g. one-to-many) mapping of input variables to output arrays, only the unique set of input variables should be given here.
    :param input_array_variable_indices[]: (Pointer to) an array of N input arrays CCTK grid variable indices (as returned by CCTK VarIndex) specifying the input grid variables for the interpolation. For any element with an index value of -1 in the grid variable indices array, that interpolation is skipped. This may be useful if the main purpose of the call is e.g. to do some query or setup computation.
    :param N_output_arrays: The number of output arrays to be returned from the interpolation. If N output arrays is zero then no interpolation is done; such a call may be useful for setup, interpolator querying, etc. Note that N output arrays may differ from N input arrays, e.g. if the operand indices parameter-table entry is used to specify a nontrivial (e.g. many- to-one) mapping of input variables to output arrays. If such a mapping is specified, only the unique set of output arrays should be given in the output arrays argument.



    :return: * 0 success
             * <0 indicates an error condition

.. c:function:: InterpGridArrays

Reduce Operators
-----------------

.. py:function:: CCTK_ReduceGridArrays()

    Reduces Cactus grid arrays. This API doesn’t provide a reduction functionality itself, it only takes care of the interprocessor communication necessary when reducing distributed grid arrays.

.. py:function:: CCTK_ReduceLocalArrays()

    Reduces processor-local arrays with various options.

.. py:function:: CCTK_ReductionHandle(const char *reduction_name)

    :param char reduction_name: the name under which the operator has been registered by the providing thorn.

.. py:function:: CCTK_ReductionArrayHandle(const char *reduction_name)

    :param char reduction_name: the name under which the operator has been registered by the providing thorn.

.. c:function:: int CCTK_Reduce(const cGH *GH, int proc, int operation_handle, int num_out_vals, int type_out_vals, void *out_vals, int num_in_fields, ...)

    :param cGH: it is the pointer to the grid hierarchy.
    :param int proc: the processor which collects the information, a negative value (−1) will distribute the data to all processors.
    :param int operation_handle: the number of the reduction operation handle, needs to be found by calling ``CCTK_ReductionHandle`` or ``CCTK_ReductionArrayHandle``.
    :param int num_out_vals: integer defining the number of output values.
    :param int type_out_vals: specifies the type of the gridfunction you are communicating.
    :param out_vals: an array that will contain the output values.
    :param int num_in_fields: specifies the number of input fields.
    :param <...>: indicates a variable argument list, specify the arrays which will be reduced, the number of specified arrays must be the same as the value of the ``num_in_fields`` variable.
    :error: Negative value indicates failure to perform reduction. 0 indicates a successful operation.

.. c:function:: int CCTK_ReduceArray(const cGH *GH, int proc, int operation_handle, int num_out_vals, int type_out_vals, void *out_vals, int num_dims, int num_in_arrays, int type_in_arrays, ...)

    The routines are designed for the purpose of reducing arrays

    :param cGH: it is the pointer to the grid hierarchy.
    :param int proc: the processor which collects the information, a negative value (−1) will distribute the data to all processors.
    :param int operation_handle: the number of the reduction operation handle, needs to be found by calling ``CCTK_ReductionHandle`` or ``CCTK_ReductionArrayHandle``.
    :param int num_out_vals: integer defining the number of output values.
    :param int type_out_vals: specifies the type of the gridfunction you are communicating.
    :param out_vals: an array that will contain the output values.
    :param int num_dims:
    :param int num_in_arrays:
    :param int type_in_arrays: specifies the type of the gridfunction you are communicating.
    :param <...>: indicates a variable argument list, specify the arrays which will be reduced, the number of specified arrays must be the same as the value of the ``num_in_fields`` variable.
    :error: Negative value indicates failure to perform reduction. 0 indicates a successful operation.

.. c:function:: int CCTK_ReduceLocScalar(const cGH *GH, int proc, int operation_handle, void *in_scalar, void *out_scalar, int data_type)

    The routines are designed for the purpose of reducing scalars

    :param cGH: it is the pointer to the grid hierarchy.
    :param int proc: the processor which collects the information, a negative value (−1) will distribute the data to all processors.
    :param int operation_handle: the number of the reduction operation handle, needs to be found by calling ``CCTK_ReductionHandle`` or ``CCTK_ReductionArrayHandle``.
    :param void in_scalar: the processor local variable with local value to be reduced
    :param void out_scalar: the reduction result, a processor local variable with the global value (same on all processors), if processor has been set to −1. Otherwise, processor will hold the reduction result.
    :param int data_type: specifies the type of the gridfunction you are communicating.
    :error: Negative value indicates failure to perform reduction. 0 indicates a successful operation.

.. c:function:: int CCTK_ReduceLocArrayToArray1D(const cGH *GH, int proc, int operation_handle, void *in_array1d, void *out_array1d, int xsize, int data_type)

    Reduction of local 1d arrays to a local arrays.

    :param cGH: it is the pointer to the grid hierarchy.
    :param int proc: the processor which collects the information, a negative value (−1) will distribute the data to all processors.
    :param int operation_handle: the number of the reduction operation handle, needs to be found by calling ``CCTK_ReductionHandle`` or ``CCTK_ReductionArrayHandle``.
    :param void in_array1d: one dimensional local arrays to be reduced across a processors, element by element.
    :param void out_array1d: array holding the reduction result.
    :param int xsize: the size of the one dimensional array.
    :param int data_type: specifies the type of the gridfunction you are communicating.
    :error: Negative value indicates failure to perform reduction. 0 indicates a successful operation.

.. c:function:: int CCTK_ReduceLocArrayToArray2D(const cGH *GH, int proc, int operation_handle, void *in_array2d, void *out_array2d, int xsize, int ysize, int data_type)

    Reduction of local 1d arrays to a local arrays.

    :param cGH: it is the pointer to the grid hierarchy.
    :param int proc: the processor which collects the information, a negative value (−1) will distribute the data to all processors.
    :param int operation_handle: the number of the reduction operation handle, needs to be found by calling ``CCTK_ReductionHandle`` or ``CCTK_ReductionArrayHandle``.
    :param void in_array2d: two dimensional local arrays to be reduced across a processors, element by element.
    :param void out_array2d: two dimensional array holding the reduction result.
    :param int xsize: the size of the one dimensional array in x direction.
    :param int ysize: the size of the one dimensional array in y direction.
    :param int data_type: specifies the type of the gridfunction you are communicating.
    :error: Negative value indicates failure to perform reduction. 0 indicates a successful operation.

.. c:function:: int CCTK_ReduceLocArrayToArray3D(const cGH *GH, int proc, int operation_handle, void *in_array3d, void *out_array3d, int xsize, int ysize, int zsize, int data_type)

    Reduction of local 1d arrays to a local arrays.

    :param cGH: it is the pointer to the grid hierarchy.
    :param int proc: the processor which collects the information, a negative value (−1) will distribute the data to all processors.
    :param int operation_handle: the number of the reduction operation handle, needs to be found by calling ``CCTK_ReductionHandle`` or ``CCTK_ReductionArrayHandle``.
    :param void in_array3d: three dimensional local arrays to be reduced across a processors, element by element.
    :param void out_array3d: three dimensional array holding the reduction result.
    :param int xsize: the size of the one dimensional array in x direction.
    :param int ysize: the size of the one dimensional array in y direction.
    :param int zsize: the size of the one dimensional array in z direction.
    :param int data_type: specifies the type of the gridfunction you are communicating.
    :error: Negative value indicates failure to perform reduction. 0 indicates a successful operation.