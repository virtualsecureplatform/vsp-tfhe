#include <tfhe_io.h>
#include <map>
#include <string>
#include <tfhe_generic_streams.h>
#include <tfhe_garbage_collector.h>

using namespace std;



/* ********************************************************
 * LWE 
******************************************************** */

/* ****************************
 * LWE params
**************************** */

/**
 * This function prints the lwe parameters to a generic stream
 */
void write_lweParams(const Ostream& F, const LweParams* lweparams) {
    TextModeProperties* props = new_TextModeProperties_blank();
    props->setTypeTitle("LWEPARAMS");
    props->setProperty_long("n", lweparams->n);
    props->setProperty_double("alpha_min", lweparams->alpha_min);
    props->setProperty_double("alpha_max", lweparams->alpha_max);
    print_TextModeProperties_toOStream(F, props);
    delete_TextModeProperties(props);
}

/**
 * This constructor function reads and creates a LWEParams from a generic stream. The result
 * must be deleted with delete_lweParams();
 */
LweParams* read_new_lweParams(const Istream& F) {
    TextModeProperties* props = new_TextModeProperties_fromIstream(F);
    if (props->getTypeTitle() != string("LWEPARAMS")) abort();
    int n = props->getProperty_long("n");
    double alpha_min = props->getProperty_double("alpha_min");
    double alpha_max = props->getProperty_double("alpha_max");
    delete_TextModeProperties(props);
    return new_LweParams(n,alpha_min,alpha_max);
}


/**
 * This function prints the lwe parameters to a file
 */
EXPORT void export_lweParams_toFile(FILE* F, const LweParams* lweparams) { write_lweParams(to_Ostream(F),lweparams); }

/**
 * This constructor function reads and creates a LWEParams from a File. The result
 * must be deleted with delete_lweParams();
 */
EXPORT void export_lweParams_toStream(ostream& F, const LweParams* lweparams) { write_lweParams(to_Ostream(F),lweparams); }

/**
 * This constructor function reads and creates a LWEParams from a stream. The result
 * must be deleted with delete_lweParams();
 */
EXPORT LweParams* new_lweParams_fromStream(std::istream& in) { return read_new_lweParams(to_Istream(in)); }

/**
 * This constructor function reads and creates a LWEParams from a File. The result
 * must be deleted with delete_lweParams();
 */
EXPORT LweParams* new_lweParams_fromFile(FILE* F)  { return read_new_lweParams(to_Istream(F)); }




/* ****************************
 * LWE samples
**************************** */

void read_lweSample(const Istream& F, LweSample* sample, const LweParams* params) {
    const int n = params->n;
    int32_t type_uid;
    F.fread(&type_uid, sizeof(int32_t));
    if (type_uid != LWE_SAMPLE_TYPE_UID) abort();
    F.fread(sample->a, sizeof(Torus32)*n);
    F.fread(&sample->b, sizeof(Torus32));
    F.fread(&sample->current_variance, sizeof(double));
}


void write_lweSample(const Ostream& F, const LweSample* sample, const LweParams* params) {
    const int n = params->n;
    F.fwrite(&LWE_SAMPLE_TYPE_UID, sizeof(int32_t));
    F.fwrite(sample->a, sizeof(Torus32)*n);
    F.fwrite(&sample->b, sizeof(Torus32));
    F.fwrite(&sample->current_variance, sizeof(double));
}


/**
 * This function prints the lwe sample to a file
 */
EXPORT void export_lweSample_toFile(FILE* F, const LweSample* lwesample, const LweParams* params) { write_lweSample(to_Ostream(F),lwesample, params); }

/**
 * This function prints the lwe sample to a stream
 */
EXPORT void export_lweSample_toStream(ostream& F, const LweSample* lwesample, const LweParams* params) { write_lweSample(to_Ostream(F),lwesample, params); }

/**
 * This function reads a LWESample from a stream in an
 * already allocated lwesample.
 */
EXPORT void import_lweSample_fromStream(std::istream& in, LweSample* lwesample, const LweParams* params) { read_lweSample(to_Istream(in), lwesample, params); }

/**
 * This function reads a LWESample from a stream in an
 * already allocated lwesample.
 */
EXPORT void import_lweSample_fromFile(FILE* F, LweSample* lwesample, const LweParams* params)  { read_lweSample(to_Istream(F), lwesample, params); }






/* ****************************
 * LWE key
**************************** */

/**
 * reads the the coefficients of the key in an already initialized key structure
 * @param F the input stream
 * @param key the destination key
 */
void read_lweKey_content(const Istream& F, LweKey* key) {
    const int n = key->params->n;
    int32_t type_uid;
    F.fread(&type_uid, sizeof(int32_t));
    if (type_uid != LWE_KEY_TYPE_UID) abort();
    F.fread(key->key, sizeof(int)*n);
}


/**
 * writes the the coefficients of the key (not the parameters) to the stream
 * @param F the output stream
 * @param key the input key
 */
void write_lweKey_content(const Ostream& F, const LweKey* key) {
    const int n = key->params->n;
    F.fwrite(&LWE_KEY_TYPE_UID, sizeof(int32_t));
    F.fwrite(key->key, sizeof(int)*n);
}

/**
 * this reads a new lweKey (params + content). The read params are garbage-collected, 
 * the output key needs to be deleted by the user (with delete_LweKey). 
 * @param F the input stream
 * @Return the key
 */
LweKey* read_new_lweKey(const Istream& F) {
    LweParams* params = read_new_lweParams(F);
    global_tfheGarbageCollector.register_param(params);
    LweKey* key = new_LweKey(params);
    read_lweKey_content(F,key);
    return key;
}


/**
 * this writes a lweKey (params + content) to a stream. 
 * @param F the output stream
 * @Return the key
 */
void write_lweKey(const Ostream& F, const LweKey* key) {
    write_lweParams(F,key->params);
    write_lweKey_content(F,key);
}



/**
 * This function prints the lwe parameters to a file
 */
EXPORT void export_lweKey_toFile(FILE* F, const LweKey* lwekey) { write_lweKey(to_Ostream(F),lwekey); }

/**
 * This function prints the lwe parameters to a stream
 */
EXPORT void export_lweKey_toStream(ostream& F, const LweKey* lwekey) { write_lweKey(to_Ostream(F),lwekey); }

/**
 * This constructor function reads and creates a LWEKey from a stream. The result
 * must be deleted with delete_lweKey();
 */
EXPORT LweKey* new_lweKey_fromStream(std::istream& in) { return read_new_lweKey(to_Istream(in)); }

/**
 * This constructor function reads and creates a LWEKey from a File. The result
 * must be deleted with delete_lweKey();
 */
EXPORT LweKey* new_lweKey_fromFile(FILE* F)  { return read_new_lweKey(to_Istream(F)); }







/* ********************************************************
 * TLWE 
******************************************************** */

/* ****************************
 * TLWE params
**************************** */

/**
 * This function prints the tlwe parameters to a generic stream
 */
void write_tLweParams(const Ostream& F, const TLweParams* tlweparams) {
    TextModeProperties* props = new_TextModeProperties_blank();
    props->setTypeTitle("TLWEPARAMS");
    props->setProperty_long("N", tlweparams->N);
    props->setProperty_long("k", tlweparams->k);
    props->setProperty_double("alpha_min", tlweparams->alpha_min);
    props->setProperty_double("alpha_max", tlweparams->alpha_max);
    print_TextModeProperties_toOStream(F, props);
    delete_TextModeProperties(props);
}


/**
 * This constructor function reads and creates a TLweParams from a generic stream. The result
 * must be deleted with delete_TLweParams();
 */
TLweParams* read_new_tLweParams(const Istream& F) {
    TextModeProperties* props = new_TextModeProperties_fromIstream(F);
    if (props->getTypeTitle() != string("TLWEPARAMS")) abort();
    int N = props->getProperty_long("N");
    int k = props->getProperty_long("k");
    double alpha_min = props->getProperty_double("alpha_min");
    double alpha_max = props->getProperty_double("alpha_max");
    delete_TextModeProperties(props);
    return new_TLweParams(N,k,alpha_min,alpha_max);
}


/**
 * This function prints the tLwe parameters to a file
 */
EXPORT void export_tLweParams_toFile(FILE* F, const TLweParams* tlweparams) { write_tLweParams(to_Ostream(F),tlweparams); }

/**
 * This constructor function reads and creates a TLWEParams from a File. The result
 * must be deleted with delete_TLweParams();
 */
EXPORT void export_tLweParams_toStream(ostream& F, const TLweParams* tlweparams) { write_tLweParams(to_Ostream(F),tlweparams); }

/**
 * This constructor function reads and creates a TLWEParams from a stream. The result
 * must be deleted with delete_TLweParams();
 */
EXPORT TLweParams* new_tLweParams_fromStream(std::istream& in) { return read_new_tLweParams(to_Istream(in)); }

/**
 * This constructor function reads and creates a TLWEParams from a File. The result
 * must be deleted with delete_TLweParams();
 */
EXPORT TLweParams* new_tLweParams_fromFile(FILE* F)  { return read_new_tLweParams(to_Istream(F)); }





/* ****************************
 * TLWE samples
**************************** */

void read_tLweSample(const Istream& F, TLweSample* sample, const TLweParams* params) {
    const int N = params->N;
    const int k = params->k;
    int32_t type_uid;
    F.fread(&type_uid, sizeof(int32_t));
    if (type_uid != TLWE_SAMPLE_TYPE_UID) abort();
    for (int i = 0; i <= k; ++i) {
        F.fread(sample->a[i].coefsT, sizeof(Torus32)*N);
    }
    F.fread(&sample->current_variance, sizeof(double));
}

void write_tLweSample(const Ostream& F, const TLweSample* sample, const TLweParams* params) {
    const int N = params->N;
    const int k = params->k;
    F.fwrite(&TLWE_SAMPLE_TYPE_UID, sizeof(int32_t));
    for (int i = 0; i <= k; ++i) {
        F.fwrite(sample->a[i].coefsT, sizeof(Torus32)*N);
    }
    F.fwrite(&sample->current_variance, sizeof(double));
}


/**
 * This function prints the tlwe sample to a file
 */
EXPORT void export_tlweSample_toFile(FILE* F, const TLweSample* tlwesample, const TLweParams* params) { write_tLweSample(to_Ostream(F),tlwesample, params); }

/**
 * This function reads a TLWESample from a stream in an
 * already allocated tlwesample.
 */
EXPORT void import_tlweSample_fromFile(FILE* F, TLweSample* tlwesample, const TLweParams* params) { read_tLweSample(to_Istream(F),tlwesample, params); }


/**
 * This function prints the tlwe sample to a stream
 */
EXPORT void export_tlweSample_toStream(std::ostream& F, const TLweSample* tlwesample, const TLweParams* params) { write_tLweSample(to_Ostream(F),tlwesample, params); }

/**
 * This function reads a TLWESample from a stream in an
 * already allocated tlwesample.
 */
EXPORT void import_tlweSample_fromStream(std::istream& F, TLweSample* tlwesample, const TLweParams* params)  { read_tLweSample(to_Istream(F),tlwesample, params); }



/* ****************************
 * TLWE FFT samples
**************************** */
/*
void read_tLweSampleFFT(const Istream& F, TLweSampleFFT* sample, const TLweParams* params) {
    const int k = params->k;
    int32_t type_uid;
    F.fread(&type_uid, sizeof(int32_t));
    if (type_uid != TLWE_SAMPLE_FFT_TYPE_UID) abort();
    for (int i = 0; i <= k; ++i) {
        F.fread(&sample->a[i], sizeof(LagrangeHalfCPolynomial));
    }
    F.fread(&sample->current_variance, sizeof(double));
}


void write_tLweSampleFFT(const Ostream& F, const TLweSampleFFT* sample, const TLweParams* params) {
    const int k = params->k;
    F.fwrite(&TLWE_SAMPLE_FFT_TYPE_UID, sizeof(int32_t));
    for (int i = 0; i <= k; ++i) {
        F.fwrite(&sample->a[i], sizeof(LagrangeHalfCPolynomial));
    }
    F.fwrite(&sample->current_variance, sizeof(double));
}
*/




/* ****************************
 * TLWE key
**************************** */

/**
 * reads the coefficients of a tlweKey, which has been previously be instantiated (the parameters are already given)
 */ 
void read_tLweKey_content(const Istream& F, TLweKey* key) {
    const int N = key->params->N;
    const int k = key->params->k;
    int32_t type_uid;
    F.fread(&type_uid, sizeof(int32_t));
    if (type_uid != TLWE_KEY_TYPE_UID) abort();
    for (int i = 0; i < k; ++i) {
        F.fread(key->key[i].coefs, sizeof(int)*N);
    }    
}

/**
 * writes the coefficients of a tlweKey
 */ 
void write_tLweKey_content(const Ostream& F, const TLweKey* key) {
    const int N = key->params->N;
    const int k = key->params->k;
    F.fwrite(&TLWE_KEY_TYPE_UID, sizeof(int32_t));
    for (int i = 0; i < k; ++i) {
        F.fwrite(key->key[i].coefs, sizeof(int)*N);
    }
}

/**
 * reads and creates the parameters and coefficients of a tlweKey.
 * The result needs to be deleted by the user (with delete_TLweKey)
 */ 
TLweKey* read_new_tLweKey(const Istream& F) {
    TLweParams* params = read_new_tLweParams(F);
    global_tfheGarbageCollector.register_param(params);
    TLweKey* key = new_TLweKey(params);
    read_tLweKey_content(F,key);
    return key;
}

/**
 * writes the coefficients of a tlweKey
 */ 
void write_tLweKey(const Ostream& F, const TLweKey* key) {
    write_tLweParams(F,key->params);
    write_tLweKey_content(F,key);
}




/**
 * This function prints the tlwe parameters to a file
 */
EXPORT void export_tlweKey_toFile(FILE* F, const TLweKey* tlwekey) { write_tLweKey(to_Ostream(F),tlwekey); }

/**
 * This constructor function reads and creates a TLWEKey from a File. The result
 * must be deleted with delete_tlweKey();
 */
EXPORT TLweKey* new_tlweKey_fromFile(FILE* F) { return read_new_tLweKey(to_Istream(F)); }


/**
 * This function prints the tlwe parameters to a stream
 */
EXPORT void export_tlweKey_toStream(std::ostream& F, const TLweKey* tlwekey) { write_tLweKey(to_Ostream(F),tlwekey); }

/**
 * This constructor function reads and creates a TLWEKey from a stream. The result
 * must be deleted with delete_tlweKey();
 */
EXPORT TLweKey* new_tlweKey_fromStream(std::istream& F) { return read_new_tLweKey(to_Istream(F)); }





/* ********************************************************
 * TGSW
******************************************************** */

/* ****************************
 * TGSW params
**************************** */

/**
 * This function prints the tGsw parameters to a generic stream
 * It only prints the TGSW section, not the Tlwe parameters
 */
void write_tGswParams_section(const Ostream& F, const TGswParams* tgswparams) {
    TextModeProperties* props = new_TextModeProperties_blank();
    props->setTypeTitle("TGSWPARAMS");
    props->setProperty_long("l", tgswparams->l);
    props->setProperty_long("Bgbit", tgswparams->Bgbit);
    print_TextModeProperties_toOStream(F, props);
    delete_TextModeProperties(props);
}

/**
 * This function prints the tGsw parameters to a generic stream
 */
void write_tGswParams(const Ostream& F, const TGswParams* tgswparams) {
    write_tLweParams(F, tgswparams->tlwe_params);
    write_tGswParams_section(F, tgswparams);
}

/**
 * This constructor function reads and creates a TGswParams from a generic stream, and an TlweParams object. 
 * The result must be deleted with delete_TGswParams();
 */
TGswParams* read_new_tGswParams_section(const Istream& F, const TLweParams* tlwe_params) {
    TextModeProperties* props = new_TextModeProperties_fromIstream(F);
    if (props->getTypeTitle() != string("TGSWPARAMS")) abort();
    int l = props->getProperty_long("l");
    int Bgbit = props->getProperty_long("Bgbit");
    // ATTENTION ici!!!
    delete_TextModeProperties(props);
    return new_TGswParams(l,Bgbit,tlwe_params);
}

/**
 * This wrapper constructor function reads and creates a TGswParams from a generic stream. 
 * The result must be deleted with delete_TGswParams(), but the inner
 * TlweParams will be garbage-collected automatically;
 */
TGswParams* read_new_tGswParams(const Istream& F) {
    TLweParams* tlwe_params = read_new_tLweParams(F);
    global_tfheGarbageCollector.register_param(tlwe_params);
    return read_new_tGswParams_section(F, tlwe_params);
}


/**
 * This function prints the tLwe parameters to a file
 */
EXPORT void export_tGswParams_toFile(FILE* F, const TGswParams* tgswparams) { write_tGswParams(to_Ostream(F),tgswparams); }

/**
 * This constructor function reads and creates a TGSWParams from a File. The result
 * must be deleted with delete_TGswParams();
 */
EXPORT void export_tGswParams_toStream(ostream& F, const TGswParams* tgswparams) { write_tGswParams(to_Ostream(F),tgswparams); }

/**
 * This constructor function reads and creates a TGSWParams from a stream. The result
 * must be deleted with delete_TGswParams();
 */
EXPORT TGswParams* new_tGswParams_fromStream(std::istream& in) { return read_new_tGswParams(to_Istream(in)); }

/**
 * This constructor function reads and creates a TGSWParams from a File. The result
 * must be deleted with delete_TGswParams();
 */
EXPORT TGswParams* new_tGswParams_fromFile(FILE* F)  { return read_new_tGswParams(to_Istream(F)); }








/* ****************************
 * TGSW samples
**************************** */

void read_tGswSample(const Istream& F, TGswSample* sample, const TGswParams* params) {
    const int kpl = params->kpl;
    int32_t type_uid;
    F.fread(&type_uid, sizeof(int32_t));
    if (type_uid != TGSW_SAMPLE_TYPE_UID) abort();

    for (int i = 0; i < kpl; ++i) {
        read_tLweSample(F, &sample->all_sample[i], params->tlwe_params);
    }
}

void write_tGswSample(const Ostream& F, const TGswSample* sample, const TGswParams* params) {
    const int kpl = params->kpl;
    F.fwrite(&TGSW_SAMPLE_TYPE_UID, sizeof(int32_t));

    for (int i = 0; i < kpl; ++i) {
        write_tLweSample(F, &sample->all_sample[i], params->tlwe_params);
    }
}

/**
 * This function prints the tgsw sample to a file
 */
EXPORT void export_tgswSample_toFile(FILE* F, const TGswSample* tgswsample, const TGswParams* params) { write_tGswSample(to_Ostream(F),tgswsample,params); }

/**
 * This function reads a TGSWSample from a stream in an
 * already allocated tgswsample.
 */
EXPORT void import_tgswSample_fromFile(FILE* F, TGswSample* tgswsample, const TGswParams* params)  { read_tGswSample(to_Istream(F),tgswsample,params); }


/**
 * This function prints the tgsw sample to a stream
 */
EXPORT void export_tgswSample_toStream(std::ostream& F, const TGswSample* tgswsample, const TGswParams* params) { write_tGswSample(to_Ostream(F),tgswsample,params); }

/**
 * This function reads a TGSWSample from a stream in an
 * already allocated tgswsample.
 */
EXPORT void import_tgswSample_fromStream(std::istream& F, TGswSample* tgswsample, const TGswParams* params) { read_tGswSample(to_Istream(F),tgswsample,params); }



/* ****************************
 * TGSW FFT samples
**************************** */
/*
void read_tGswSampleFFT(const Istream& F, TGswSampleFFT* sample, const TGswParams* params) {
    const int kpl = params->kpl;
    int32_t type_uid;
    F.fread(&type_uid, sizeof(int32_t));
    if (type_uid != TGSW_SAMPLE_FFT_TYPE_UID) abort();

    for (int i = 0; i < kpl; ++i) {
        read_tLweSampleFFT(F, &sample->all_samples[i], params->tlwe_params);
    }
}


void write_tGswSampleFFT(const Ostream& F, const TGswSampleFFT* sample, const TGswParams* params) {
    const int kpl = params->kpl;
    F.fwrite(&TGSW_SAMPLE_FFT_TYPE_UID, sizeof(int32_t));

    for (int i = 0; i < kpl; ++i) {
        write_tLweSampleFFT(F, &sample->all_samples[i], params->tlwe_params);
    }
}
*/




/* ****************************
 * TGSW key
**************************** */

/**
 * reads a tgsw key coefficients in a previously defined structure
 */ 
void read_tGswKey_content(const Istream& F, TGswKey* key) {
    const int N = key->params->tlwe_params->N;
    const int k = key->params->tlwe_params->k;
    int32_t type_uid;
    F.fread(&type_uid, sizeof(int32_t));
    if (type_uid != TGSW_KEY_TYPE_UID) abort();

    for (int i = 0; i < k; ++i) {
        F.fread(key->key[i].coefs, sizeof(int)*N);
    }
}


/**
 * writes the tgsw key coefficients
 */ 
void write_tGswKey_content(const Ostream& F, const TGswKey* key) {
    const int N = key->params->tlwe_params->N;
    const int k = key->params->tlwe_params->k;
    F.fwrite(&TGSW_KEY_TYPE_UID, sizeof(int32_t));
    
    for (int i = 0; i < k; ++i) {
        F.fwrite(key->key[i].coefs, sizeof(int)*N);
    }
}

/**
 * reads a tgsw key coefficients in a previously defined structure
 */ 
TGswKey* read_new_tGswKey(const Istream& F) {
    TGswParams* params = read_new_tGswParams(F);
    global_tfheGarbageCollector.register_param(params);
    TGswKey* key = new_TGswKey(params);
    read_tGswKey_content(F, key);
    return key;
}

/**
 * writes the tgsw key coefficients
 */ 
void write_tGswKey(const Ostream& F, const TGswKey* key) {
    write_tGswParams(F,key->params);
    write_tGswKey_content(F,key);
}

/**
 * This function prints the tgsw parameters to a file
 */
EXPORT void export_tgswKey_toFile(FILE* F, const TGswKey* tgswkey) { write_tGswKey(to_Ostream(F), tgswkey); }

/**
 * This constructor function reads and creates a TGSWKey from a File. The result
 * must be deleted with delete_tgswKey();
 */
EXPORT TGswKey* new_tgswKey_fromFile(FILE* F) { return read_new_tGswKey(to_Istream(F)); }


/**
 * This function prints the tgsw parameters to a stream
 */
EXPORT void export_tgswKey_toStream(std::ostream& F, const TGswKey* tgswkey)  { write_tGswKey(to_Ostream(F), tgswkey); }

/**
 * This constructor function reads and creates a TGSWKey from a stream. The result
 * must be deleted with delete_tgswKey();
 */
EXPORT TGswKey* new_tgswKey_fromStream(std::istream& F) { return read_new_tGswKey(to_Istream(F)); }
