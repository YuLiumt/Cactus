Reduce Operators
=================

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