#ifndef RINGLWE_H
#define RINGLWE_H

///@file
///@brief This file contains the declaration of tlwe structures

#include "tfhe_core.h"
#include "lweparams.h"

struct TLweParams {
    const int32_t N; ///< a power of 2: degree of the polynomials
    const int32_t k; ///< number of polynomials in the mask
    const double alpha_min; ///< minimal noise s.t. the sample is secure
    const double alpha_max; ///< maximal noise s.t. we can decrypt
    const LweParams extracted_lweparams; ///< lwe params if one extracts

#ifdef __cplusplus

    TLweParams(int32_t N, int32_t k, double alpha_min, double alpha_max, double alpha_lvl21);

    ~TLweParams();

    TLweParams(const TLweParams &) = delete;

    void operator=(const TLweParams &) = delete;

#endif
};

struct TLweKey {
    const TLweParams *params; ///< the parameters of the key
    IntPolynomial *key; ///< the key (i.e k binary polynomials)
#ifdef __cplusplus

    TLweKey(const TLweParams *params);

    ~TLweKey();

    TLweKey(const TLweKey &) = delete;

    void operator=(const TLweKey &) = delete;

#endif
};


struct TLweSample {
    TorusPolynomial *a; ///< array of length k+1: mask + right term
    TorusPolynomial *b; ///< alias of a[k] to get the right term
    double current_variance; ///< avg variance of the sample
    const int32_t k;
#ifdef __cplusplus

    TLweSample(const TLweParams *params);

    ~TLweSample();

    TLweSample(const TLweSample &) = delete;

    void operator=(const TLweSample &) = delete;

#endif
};

struct TLweSamplelvl2 {
    TorusPolynomiallvl2 *a; ///< array of length k+1: mask + right term
    TorusPolynomiallvl2 *b; ///< alias of a[k] to get the right term
    double current_variance; ///< avg variance of the sample
    const int32_t k;
#ifdef __cplusplus

    TLweSamplelvl2(const TLweParams *params);

    ~TLweSamplelvl2();

    TLweSamplelvl2(const TLweSamplelvl2 &) = delete;

    void operator=(const TLweSamplelvl2 &) = delete;

#endif
};

struct TLweSampleFFT {
    LagrangeHalfCPolynomial *a; ///< array of length k+1: mask + right term
    LagrangeHalfCPolynomial *b; ///< alias of a[k] to get the right term
    double current_variance; ///< avg variance of the sample
    const int32_t k; //required during the destructor call...
#ifdef __cplusplus

    TLweSampleFFT(const TLweParams *params, LagrangeHalfCPolynomial *a, double current_variance);

    ~TLweSampleFFT();

    TLweSampleFFT(const TLweSampleFFT &) = delete;

    void operator=(const TLweSampleFFT &) = delete;

#endif
};


//allocate memory space for a TLweParams
EXPORT TLweParams *alloc_TLweParams();
EXPORT TLweParams *alloc_TLweParams_array(int32_t nbelts);

//free memory space for a TLweParams
EXPORT void free_TLweParams(TLweParams *ptr);
EXPORT void free_TLweParams_array(int32_t nbelts, TLweParams *ptr);

//initialize the TLweParams structure
//(equivalent of the C++ constructor)
EXPORT void init_TLweParams(TLweParams *obj, int32_t N, int32_t k, double alpha_min, double alpha_max, double alpha_lvl21);
EXPORT void init_TLweParams_array(int32_t nbelts, TLweParams *obj, int32_t N, int32_t k, double alpha_min, double alpha_max, double alpha_lvl21);

//destroys the TLweParams structure
//(equivalent of the C++ destructor)
EXPORT void destroy_TLweParams(TLweParams *obj);
EXPORT void destroy_TLweParams_array(int32_t nbelts, TLweParams *obj);

//allocates and initialize the TLweParams structure
//(equivalent of the C++ new)
EXPORT TLweParams *new_TLweParams(int32_t N, int32_t k, double alpha_min, double alpha_max, double alpha_lvl21);
EXPORT TLweParams *new_TLweParams_array(int32_t nbelts, int32_t N, int32_t k, double alpha_min, double alpha_max, double alpha_lvl21);

//destroys and frees the TLweParams structure
//(equivalent of the C++ delete)
EXPORT void delete_TLweParams(TLweParams *obj);
EXPORT void delete_TLweParams_array(int32_t nbelts, TLweParams *obj);

//-----------------------------------------------------------------
// autogenerated allocators/constructors/destructors declarations
// use code_autogen.pl TLweKey TLweParams to regenerate
//-----------------------------------------------------------------


/** allocate space for a single TLweKey */
EXPORT TLweKey *alloc_TLweKey();
/** allocate space for an array of TLweKey 
 * @param nbelts the number of elements */
EXPORT TLweKey *alloc_TLweKey_array(int32_t nbelts);

/** free memory space for a single TLweKey 
 * @param ptr the pointer to release */
EXPORT void free_TLweKey(TLweKey *ptr);
/** free memory space for an array of TLweKey 
 * @param nbelts the number of elements 
 * @param ptr the pointer to release */
EXPORT void free_TLweKey_array(int32_t nbelts, TLweKey *ptr);

/** initializes (constructor) a single TLweKey on an already allocated space 
 * @param ptr the pointer to the first element
 * @param params the LWE parameters to use
 */
EXPORT void init_TLweKey(TLweKey *ptr, const TLweParams *params);

/** initializes (constructor) an array of TLweKeys on an already allocated space 
 * @param nbelts the number of elements to initialize 
 * @param ptr the pointer to the first element
 * @param params the LWE parameters to use
 */
EXPORT void init_TLweKey_array(int32_t nbelts, TLweKey *ptr, const TLweParams *params);

/** finalizes (destructor) a single TLweKey (before freeing the memory space) 
 * @param ptr the pointer to the first element
 */
EXPORT void destroy_TLweKey(TLweKey *ptr);

/** finalizes (destructor) an array of TLweKeys (before freeing the memory space) 
 * @param nbelts the number of elements to initialize 
 * @param ptr the pointer to the first element
 */
EXPORT void destroy_TLweKey_array(int32_t nbelts, TLweKey *ptr);

/** allocates and initializes (constructor) a single TLweKey 
 * @param params the LWE parameters to use
 */
EXPORT TLweKey *new_TLweKey(const TLweParams *params);
/** allocates and initializes (constructor) a single TLweKey 
 * @param nbelts the number of consecutive elements to create 
 * @param params the LWE parameters to use
 */
EXPORT TLweKey *new_TLweKey_array(int32_t nbelts, const TLweParams *params);

/** destroy and frees memory space for a single TLweKey 
 * @param ptr the pointer to release */
EXPORT void delete_TLweKey(TLweKey *obj);
/** destroys and free memory space for an array of TLweKey 
 * @param nbelts the number of elements 
 * @param ptr the pointer to release */
EXPORT void delete_TLweKey_array(int32_t nbelts, TLweKey *obj);


//-----------------------------------------------------------------
// autogenerated allocators/constructors/destructors declarations
// use code_autogen.pl TLweSample TLweParams to regenerate
//-----------------------------------------------------------------


/** allocate space for a single TLweSample */
EXPORT TLweSample *alloc_TLweSample();
EXPORT TLweSamplelvl2 *alloc_TLweSamplelvl2();
/** allocate space for an array of TLweSample 
 * @param nbelts the number of elements */
EXPORT TLweSample *alloc_TLweSample_array(int32_t nbelts);

/** free memory space for a single TLweSample 
 * @param ptr the pointer to release */
EXPORT void free_TLweSample(TLweSample *ptr);
EXPORT void free_TLweSamplelvl2(TLweSamplelvl2 *ptr);
/** free memory space for an array of TLweSample 
 * @param nbelts the number of elements 
 * @param ptr the pointer to release */
EXPORT void free_TLweSample_array(int32_t nbelts, TLweSample *ptr);

/** initializes (constructor) a single TLweSample on an already allocated space 
 * @param ptr the pointer to the first element
 * @param params the LWE parameters to use
 */
EXPORT void init_TLweSample(TLweSample *ptr, const TLweParams *params);
EXPORT void init_TLweSamplelvl2(TLweSamplelvl2 *ptr, const TLweParams *params);

/** initializes (constructor) an array of TLweSamples on an already allocated space 
 * @param nbelts the number of elements to initialize 
 * @param ptr the pointer to the first element
 * @param params the LWE parameters to use
 */
EXPORT void init_TLweSample_array(int32_t nbelts, TLweSample *ptr, const TLweParams *params);
EXPORT void init_TLweSamplelvl2_array(int32_t nbelts, TLweSamplelvl2 *ptr, const TLweParams *params);

/** finalizes (destructor) a single TLweSample (before freeing the memory space) 
 * @param ptr the pointer to the first element
 */
EXPORT void destroy_TLweSample(TLweSample *ptr);
EXPORT void destroy_TLweSamplelvl2(TLweSamplelvl2 *ptr);

/** finalizes (destructor) an array of TLweSamples (before freeing the memory space) 
 * @param nbelts the number of elements to initialize 
 * @param ptr the pointer to the first element
 */
EXPORT void destroy_TLweSample_array(int32_t nbelts, TLweSample *ptr);

/** allocates and initializes (constructor) a single TLweSample 
 * @param params the LWE parameters to use
 */
EXPORT TLweSample *new_TLweSample(const TLweParams *params);
EXPORT TLweSamplelvl2 *new_TLweSamplelvl2(const TLweParams *params);
/** allocates and initializes (constructor) a single TLweSample 
 * @param nbelts the number of consecutive elements to create 
 * @param params the LWE parameters to use
 */
EXPORT TLweSample *new_TLweSample_array(int32_t nbelts, const TLweParams *params);
EXPORT TLweSamplelvl2 *new_TLweSamplelvl2_array(int32_t nbelts, const TLweParams *params);

/** destroy and frees memory space for a single TLweSample 
 * @param ptr the pointer to release */
EXPORT void delete_TLweSample(TLweSample *obj);
EXPORT void delete_TLweSamplelvl2(TLweSamplelvl2 *obj);
/** destroys and free memory space for an array of TLweSample 
 * @param nbelts the number of elements 
 * @param ptr the pointer to release */
EXPORT void delete_TLweSample_array(int32_t nbelts, TLweSample *obj);


//-----------------------------------------------------------------
// autogenerated allocators/constructors/destructors declarations
// use code_autogen.pl TLweSampleFFT TLweParams to regenerate
//-----------------------------------------------------------------


/** allocate space for a single TLweSampleFFT */
EXPORT TLweSampleFFT *alloc_TLweSampleFFT();
/** allocate space for an array of TLweSampleFFT 
 * @param nbelts the number of elements */
EXPORT TLweSampleFFT *alloc_TLweSampleFFT_array(int32_t nbelts);

/** free memory space for a single TLweSampleFFT 
 * @param ptr the pointer to release */
EXPORT void free_TLweSampleFFT(TLweSampleFFT *ptr);
/** free memory space for an array of TLweSampleFFT 
 * @param nbelts the number of elements 
 * @param ptr the pointer to release */
EXPORT void free_TLweSampleFFT_array(int32_t nbelts, TLweSampleFFT *ptr);

/** initializes (constructor) a single TLweSampleFFT on an already allocated space 
 * @param ptr the pointer to the first element
 * @param params the LWE parameters to use
 */
EXPORT void init_TLweSampleFFT(TLweSampleFFT *ptr, const TLweParams *params);

/** initializes (constructor) an array of TLweSampleFFTs on an already allocated space 
 * @param nbelts the number of elements to initialize 
 * @param ptr the pointer to the first element
 * @param params the LWE parameters to use
 */
EXPORT void init_TLweSampleFFT_array(int32_t nbelts, TLweSampleFFT *ptr, const TLweParams *params);

/** finalizes (destructor) a single TLweSampleFFT (before freeing the memory space) 
 * @param ptr the pointer to the first element
 */
EXPORT void destroy_TLweSampleFFT(TLweSampleFFT *ptr);

/** finalizes (destructor) an array of TLweSampleFFTs (before freeing the memory space) 
 * @param nbelts the number of elements to initialize 
 * @param ptr the pointer to the first element
 */
EXPORT void destroy_TLweSampleFFT_array(int32_t nbelts, TLweSampleFFT *ptr);

/** allocates and initializes (constructor) a single TLweSampleFFT 
 * @param params the LWE parameters to use
 */
EXPORT TLweSampleFFT *new_TLweSampleFFT(const TLweParams *params);
/** allocates and initializes (constructor) a single TLweSampleFFT 
 * @param nbelts the number of consecutive elements to create 
 * @param params the LWE parameters to use
 */
EXPORT TLweSampleFFT *new_TLweSampleFFT_array(int32_t nbelts, const TLweParams *params);

/** destroy and frees memory space for a single TLweSampleFFT 
 * @param ptr the pointer to release */
EXPORT void delete_TLweSampleFFT(TLweSampleFFT *obj);
/** destroys and free memory space for an array of TLweSampleFFT 
 * @param nbelts the number of elements 
 * @param ptr the pointer to release */
EXPORT void delete_TLweSampleFFT_array(int32_t nbelts, TLweSampleFFT *obj);

#endif // RINGLWE_H
