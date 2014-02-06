/*
 * CommonJni.cpp
 *
 *  Created on: 2014年1月28日
 *      Author: mabin
 */

#include "CommonJni.h"
#include "jni/JniHelper.h"

USING_NS_CC;

std::string getExternalDataDir() {
	std::string ret;
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "android/os/Environment",
			"getDataDirectory", "()Ljava/io/File;")) {
		jobject retFromJava = t.env->CallStaticObjectMethod(t.classID,
				t.methodID);
		t.env->DeleteLocalRef(t.classID);
		if (JniHelper::getMethodInfo(t, "java/io/File", "getAbsolutePath",
				"()Ljava/lang/String;")) {
			jstring retString = (jstring) t.env->CallObjectMethod(retFromJava, t.methodID);
			ret = JniHelper::jstring2string(retString);
			t.env->DeleteLocalRef(t.classID);
		}

	}
	return ret;
}

std::string getExternalStorageDir() {
	std::string ret;
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "android/os/Environment",
			"getExternalStorageDirectory", "()Ljava/io/File;")) {
		jobject retFromJava = t.env->CallStaticObjectMethod(t.classID,
				t.methodID);
		t.env->DeleteLocalRef(t.classID);
		if (JniHelper::getMethodInfo(t, "java/io/File", "getAbsolutePath",
				"()Ljava/lang/String;")) {
			jstring retString = (jstring) t.env->CallObjectMethod(retFromJava, t.methodID);
			ret = JniHelper::jstring2string(retString);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	return ret;
}

bool isExternalStorageAvailable() {
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "android/os/Environment",
			"getExternalStorageState", "()Ljava/lang/String;")) {
		jfieldID fieldId1 = t.env->GetFieldID(t.classID, "MEDIA_MOUNTED",
				"Ljava/lang/String;");
		jfieldID fieldId2 = t.env->GetFieldID(t.classID,
				"MEDIA_MOUNTED_READ_ONLY", "Ljava/lang/String;");
		jstring jstr1 = (jstring) t.env->GetStaticObjectField(t.classID,
				fieldId1);
		jstring jstr2 = (jstring) t.env->GetStaticObjectField(t.classID,
				fieldId2);

		jstring jstr3 = (jstring) t.env->CallStaticIntMethod(t.classID,
				t.methodID);
		std::string str1 = JniHelper::jstring2string(jstr1);
		std::string str2 = JniHelper::jstring2string(jstr2);
		std::string str3 = JniHelper::jstring2string(jstr3);
		t.env->DeleteLocalRef(t.classID);
		if (str3 == str1 || str3 == str2) {
			return true;
		}
	}
	return false;
}
