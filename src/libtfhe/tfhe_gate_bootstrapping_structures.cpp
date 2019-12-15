#include "tfhe_gate_bootstrapping_structures.h"
#include "lwekey.h"
#include "lweparams.h"
#include "lwesamples.h"
#include "tlwe.h"
#include "tgsw.h"

TFheGateBootstrappingParameterSet::TFheGateBootstrappingParameterSet(const int32_t ks_t, const int32_t ks_basebit, const LweParams* const in_out_params, const TGswParams* const tgsw_params, const int32_t ks_tbar, const int32_t ks_basebitlvl21, const TGswParams* const tgsw_paramslvl2):
    ks_t(ks_t),
    ks_basebit(ks_basebit),
    in_out_params(in_out_params),
    tgsw_params(tgsw_params),
    ks_tbar(ks_tbar),
    ks_basebitlvl21(ks_basebitlvl21),
    tgsw_paramslvl2(tgsw_paramslvl2)
{}

TFheGateBootstrappingCloudKeySet::TFheGateBootstrappingCloudKeySet(
        const TFheGateBootstrappingParameterSet* const params, 
        const LweBootstrappingKey* const bk,
        const LweBootstrappingKeyFFT* const bkFFT):
    params(params),bk(bk),bkFFT(bkFFT)
{}

TFheGateBootstrappingSecretKeySet::TFheGateBootstrappingSecretKeySet(
        const TFheGateBootstrappingParameterSet* const params, 
        const LweBootstrappingKey* const bk,
        const LweBootstrappingKeyFFT* const bkFFT,
        const LweKey* lwe_key,
        const TGswKey* tgsw_key):
    params(params),
    lwe_key(lwe_key),
    tgsw_key(tgsw_key),
    cloud(params,bk,bkFFT) 
{}
