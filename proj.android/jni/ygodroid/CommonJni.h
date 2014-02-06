/*
 * CommonJni.h
 *
 *  Created on: 2014年1月28日
 *      Author: mabin
 */

#ifndef COMMONJNI_H_
#define COMMONJNI_H_

#include <string>


std::string getExternalDataDir();
std::string getExternalStorageDir();
bool isExternalStorageAvailable();



#endif /* COMMONJNI_H_ */
