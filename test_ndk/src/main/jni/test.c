//
// Created by $JokerWan on 2017/10/30.
//

#include "com_example_wanjiacheng_myapplication_JNIS.h"
#include <string.h>

/**
 * 返回一个字符串
 */
JNIEXPORT jstring JNICALL
Java_com_example_wanjiacheng_myapplication_JNIS_helloJNI(JNIEnv *env,jobject jobj) {
    return (*env)->NewStringUTF(env, "Hello from C");
};

/**
 * 工具函数
 * 把一个jstring转换成一个c语言的char* 类型.
 */
char* _JString2CStr(JNIEnv* env, jstring jstr) {

    char* rtn;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env,"GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if(alen > 0) {
        rtn = (char*)malloc(alen+1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen]=0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba,0);
    return rtn;
}

/**
 * 将两个字符串拼接后返回
 */
JNIEXPORT jstring JNICALL
Java_com_example_wanjiacheng_myapplication_JNIS_sayHello(JNIEnv *env,jobject jobj,jstring jstr){
    char* cs1 = _JString2CStr(env,jstr);
    char* cs2 = "Hello by C";
    char* cs3 = strcat(cs1,cs2);
    return (*env) -> NewStringUTF(env,cs3);
};

/**
 * 将数组中的每个元素增加10
 */
JNIEXPORT jintArray JNICALL
Java_com_example_wanjiacheng_myapplication_JNIS_increaseArrayEles(JNIEnv *env,jobject jobj,jintArray arr){

    jsize length = (*env) -> GetArrayLength(env,arr);
    jint* array = (*env) -> GetIntArrayElements(env,arr,JNI_FALSE);

    //方法一：不能实现？
//    int i;
//    for(i = 0;i < length;i++){
//        *(array+i) += 10;
//    }


    //方法二
    jint nativeArr[length];
    (*env) -> GetIntArrayRegion(env,arr,0,length,nativeArr);
    int i;
    for(i = 0;i < length;i++){
        nativeArr[i] += 10;
    }
    (*env) -> SetIntArrayRegion(env,arr,0,length,nativeArr);

    return arr;
}

/**
 * C 回调java，利用反射
 */
JNIEXPORT void JNICALL
Java_com_example_wanjiacheng_myapplication_JNIS_callbackShowToast(JNIEnv *env,jobject jobj){
    //1.加载类得到class对象
    jclass jc = (*env) -> FindClass(env,"com/example/wanjiacheng/myapplication/JNIS");

    //2.得到对应方法的Method对象    "()V"  参数类型签名：() 返回值类型签名：V  表示无参无返回值方法的签名
    jmethodID method = (*env)->GetMethodID(env,jc,"showToast","()V");

    //3.调用方法
    (*env)->CallVoidMethod(env,jobj,method);
}

