#include <jni.h>
#include <string>

#include "dconvolution.h"

#include "dconvolution_terminate.h"
#include "dconvolution_emxAPI.h"
#include "dconvolution_terminate.h"
#include <android/log.h>

static emxArray_real_T *argInit_1xUnbounded_real_T();
static double argInit_real_T();
static void main_dconvolution();

/* Function Definitions */
static emxArray_real_T *argInit_1xUnbounded_real_T(int len)
{
    emxArray_real_T *result;
    static int iv0[2] = { 1, len};

    int idx1;

    /* Set the size of the array.
       Change this size to the value that the application requires. */
    result = emxCreateND_real_T(2, *(int (*)[len])&iv0[0]);

    /* Loop over the array to initialize each element. */
    /*result->size[1U]*/
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
        /* Set the value of the array element.
           Change this value to the value that the application requires. */
        result->data[result->size[0] * idx1] = argInit_real_T();
    }

    return result;
}

static double argInit_real_T()
{
    return 0.0;
}



extern "C"
JNIEXPORT void JNICALL
Java_edu_osu_dconvapp_ResultsActivity_dconvolution(JNIEnv *env, jobject instance, jdoubleArray x_,
                                                jdoubleArray h_, jdouble s, jdoubleArray b_,
                                                jdoubleArray e_, jdoubleArray m_, jdoubleArray y_,
                                                jdoubleArray i_) {
    jdouble *x1 = env->GetDoubleArrayElements(x_, NULL);
    jdouble *h1 = env->GetDoubleArrayElements(h_, NULL);
    /*  jdouble *b = env->GetDoubleArrayElements(b_, NULL);
      jdouble *e = env->GetDoubleArrayElements(e_, NULL);
      jdouble *m = env->GetDoubleArrayElements(m_, NULL);
      jdouble *y = env->GetDoubleArrayElements(y_, NULL);

      */

    int len_x =  env->GetArrayLength(x_);
    int len_h =  env->GetArrayLength(h_);

    int len_e = 2*len_h + len_x ;
    int len_b = 2*len_h + len_x;
    int len_m = 2*len_h + len_x;
    int len_y = 2*len_h + len_x -1;

    __android_log_print(ANDROID_LOG_ERROR," len x", "%d\n", len_x);
    __android_log_print(ANDROID_LOG_ERROR," len h", "%d\n", len_h);
    __android_log_print(ANDROID_LOG_ERROR," len b", "%d\n", len_b);


    emxArray_real_T *b;
    emxArray_real_T *e;
    emxArray_real_T *m;
    emxArray_real_T *y;
    emxArray_real_T *x;
    emxArray_real_T *h;

    emxInitArray_real_T(&b, 2);
    emxInitArray_real_T(&e, 2);
    emxInitArray_real_T(&m, 2);
    emxInitArray_real_T(&y, 2);

    /* Initialize function 'dconvolution' input arguments. */
    /* Initialize function input argument 'x'. */
    x = argInit_1xUnbounded_real_T(len_x);

    /* Initialize function input argument 'h'. */
    h = argInit_1xUnbounded_real_T(len_h);

    x->data = x1;
    x->size[1] = len_x;


    double x_temp[len_x];
    int j;
    for(j=0;j<len_x;j++){
        x_temp[j]=x->data[j];
        __android_log_print(ANDROID_LOG_ERROR," X Value", "%f\n", x->data[j]);

    }


    h->data = h1;
    h->size[1] = len_h;

    double h_temp[len_h];

    for(j=0;j<len_h;j++){
        h_temp[j]=h->data[j];
        __android_log_print(ANDROID_LOG_ERROR," H Value", "%f\n",h->data[j]);

    }

    __android_log_print(ANDROID_LOG_ERROR," H Size", "%d\n",h->size[0]);
    __android_log_print(ANDROID_LOG_ERROR," H Size", "%d\n",h->size[1]);

    __android_log_print(ANDROID_LOG_ERROR," X Size", "%d\n",x->size[0]);
    __android_log_print(ANDROID_LOG_ERROR," X Size", "%d\n",x->size[1]);


    jdouble i;

    /* Call the entry-point 'dconvolution'. */
   dconvolution(x, h, s , b, e, m, &i, y);

    __android_log_print(ANDROID_LOG_ERROR," S Value", "%f\n", s);
    __android_log_print(ANDROID_LOG_ERROR," I Value", "%f\n", i);

    double e_temp[len_e];
    //int j;
    for(j=0;j<len_e;j++){
        e_temp[j]=e->data[j];

    }

    //e_temp[0] = x->size[1];

    double b_temp[len_b];

    for(j=0;j<len_b;j++){
        b_temp[j]=b->data[j];
        __android_log_print(ANDROID_LOG_ERROR," B Value", "%f\n", b_temp[j]);
    }


    double m_temp[len_m];

    for(j=0;j<len_m;j++){
        m_temp[j]=m->data[j];
        //__android_log_print(ANDROID_LOG_ERROR,
        //                "HelloWorld Final 1", "%f\n", xt_temp[i]);
    }


    double y_temp[len_y];

    for(j=0;j<len_y;j++){
        y_temp[j]=y->data[j];
        //__android_log_print(ANDROID_LOG_ERROR,
        //                "HelloWorld Final 1", "%f\n", xt_temp[i]);
    }


    double o1[] = {i};

    (env)->SetDoubleArrayRegion(x_, 0, len_x, x_temp);
    (env)->SetDoubleArrayRegion(h_, 0, len_h, h_temp);


    (env)->SetDoubleArrayRegion(e_, 0, len_e, e_temp);

    (env)->SetDoubleArrayRegion(m_, 0, len_m, m_temp);
    (env)->SetDoubleArrayRegion(b_, 0, len_b, b_temp);
    (env)->SetDoubleArrayRegion(y_, 0, len_y, y_temp);
    (env)->SetDoubleArrayRegion(i_, 0, 1, o1);

    emxDestroyArray_real_T(y);
    emxDestroyArray_real_T(m);
    emxDestroyArray_real_T(e);
    emxDestroyArray_real_T(b);
    emxDestroyArray_real_T(h);
    emxDestroyArray_real_T(x);



    dconvolution_terminate();


}


extern "C"
JNIEXPORT void JNICALL
Java_edu_osu_dconvapp_MainActivity_dconvMain(JNIEnv *env, jobject instance, jdoubleArray x_,
                                             jdoubleArray h_, jdouble s, jdoubleArray b_,
                                             jdoubleArray e_, jdoubleArray m_, jdoubleArray y_,
                                             jdouble i) {
    jdouble *x = env->GetDoubleArrayElements(x_, NULL);
    jdouble *h = env->GetDoubleArrayElements(h_, NULL);
    jdouble *b = env->GetDoubleArrayElements(b_, NULL);
    jdouble *e = env->GetDoubleArrayElements(e_, NULL);
    jdouble *m = env->GetDoubleArrayElements(m_, NULL);
    jdouble *y = env->GetDoubleArrayElements(y_, NULL);

    double out1[] = {1.0 , 9.0, 3.0};

    (env)->SetDoubleArrayRegion(e_, 0, 3, out1);

    (env)->SetDoubleArrayRegion(m_, 0, 3, out1);

    i = 12;


    env->ReleaseDoubleArrayElements(x_, x, 0);
    env->ReleaseDoubleArrayElements(h_, h, 0);
    env->ReleaseDoubleArrayElements(b_, b, 0);
    //env->ReleaseDoubleArrayElements(e_, e, 0);
    //env->ReleaseDoubleArrayElements(m_, m, 0);
    env->ReleaseDoubleArrayElements(y_, y, 0);

    //return e_;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_edu_osu_dconvapp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jobject JNICALL
Java_edu_osu_dconvapp_MainActivity_matrixmulti(JNIEnv *env, jobject instance, jdoubleArray a_,
                                               jdoubleArray b_) {
    jdouble *a = env->GetDoubleArrayElements(a_, NULL);
    jdouble *b = env->GetDoubleArrayElements(b_, NULL);

    double c;

    int i0;
    //c = 0.0;
    for (i0 = 0; i0 < 2; i0++) {
        c += a[i0] * b[i0];
    }

    // Get the class we wish to return an instance of
    jclass clazz = (env)->FindClass("edu/osu/dconvapp/DConvResults");

    // Get the method id of an empty constructor in clazz
    //jmethodID constructor = (env)->GetMethodID(clazz, "<init>", "([D[D[DD[D)V");
    jmethodID constructor = (env)->GetMethodID(clazz, "<init>", "(D)V");

    // Create an instance of clazz
    jobject obj = (env)->NewObject( clazz, constructor, c);

    env->ReleaseDoubleArrayElements(a_, a, 0);
    env->ReleaseDoubleArrayElements(b_, b, 0);

    return obj;
}