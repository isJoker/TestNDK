# TestNDK
jni + ndk 编程

NDK集成开发流程（AS）


1. 安装配置NDK

	1). 解压NDK的zip包到非中文目录
	
	2). 配置path : 解压后NDK的根目录----->ndk-build
	

2. 给AS配置关联NDK

	1). local.properties中添加配置

    		        ndk.dir=D\:\\android-ndk32-r10-windows-x86_64\\android-ndk-r10
     
	2). gradle.properties中添加配置
	
		        android.useDeprecatedNdk=true//可以用过时的方法
		

3. 编写native方法:

			public class JNIS {
    			    public native String helloJNI();
			}

4. 定义对应的JNI

	1). 在main下创建jni文件夹
	
	2). 生成native方法对应的JNI函数声明头文件: 
			命令窗口中, 进入java文件夹
	
			执行命令: javah com.example.wanjiacheng.testndk.JNIS
			
			生成头文件: com_example_wanjiacheng_testndk_JNIS.h
			
			函数声明: JNIEXPORT jstring JNICALL Java_com_example_wanjiacheng_testndk_JNIS_helloJNI(JNIEnv *, jobject);
			
	3). 将生成的头文件转移到jni文件夹下
	
	4). 在jni下定义对应的函数文件: test.c
	
		#include "com_example_wanjiacheng_testndk_JNIS.h"
		JNIEXPORT jstring JNICALL Java_com_example_wanjiacheng_testndk_JNIS_helloJNI
  		(JNIEnv * env, jobject jobj) {
  			return (*env)->NewStringUTF(env, "Hello from C");
		}
		

5. 指定编译的不同CPU

		defaultConfig {
    		    ndk{
        		moduleName "HelloJni" //so文件: lib+moduleName+.so
        		abiFilters "armeabi", "armeabi-v7a", "x86" //cpu的类型
    		    }
		}
		
6. 编译生成不同平台下的动态链接文件

	1). 执行rebuild, 生成so文件
	
	2). so文件目录: build\intermediates\ndk\debug\lib\.....
	
7. 调用native方法:

	1). 在native方法所在的类中加载so文件
	
			static {
        		    System.loadLibrary("HelloJni");
    			}
			
	2). 在Activity中调用native方法:
	
		        String result = new JNIS().helloJNI();
        	        Log.e("TAG", "result="+result);
