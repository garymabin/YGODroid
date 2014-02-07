/*
 * YGODataManager.cpp
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#include "YGODataManager.h"

USING_NS_CC;

namespace ygo {
const wchar_t* YGODataManager::unknown_string = L"???";
wchar_t YGODataManager::strBuffer[2048];
static YGODataManager* s_dataManager = NULL;

YGODataManager* YGODataManager::sharedDataManager() {
	if (!s_dataManager) {
		s_dataManager = new YGODataManager();
	}
	return s_dataManager;
}

bool YGODataManager::LoadDB(const char* file) {
	std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(file);
	CCLOG("open db file path = %s", path.c_str());
	sqlite3* pDB;
	if (sqlite3_open(path.c_str(), &pDB) != SQLITE_OK)
		return Error(pDB);
	sqlite3_stmt* pStmt;
	const char* sql = "select * from datas,texts where datas.id=texts.id";
	if (sqlite3_prepare_v2(pDB, sql, -1, &pStmt, 0) != SQLITE_OK)
		return Error(pDB);
	CardDataC cd;
	CardString cs;
	for (int i = 0; i < 16; ++i)
		cs.desc[i] = 0;
	int step = 0, len = 0;
	do {
		step = sqlite3_step(pStmt);
		if (step == SQLITE_BUSY || step == SQLITE_ERROR || step == SQLITE_MISUSE)
			return Error(pDB, pStmt);
		else if (step == SQLITE_ROW) {
			cd.code = sqlite3_column_int(pStmt, 0);
			cd.ot = sqlite3_column_int(pStmt, 1);
			cd.alias = sqlite3_column_int(pStmt, 2);
			cd.setcode = sqlite3_column_int(pStmt, 3);
			cd.type = sqlite3_column_int(pStmt, 4);
			cd.attack = sqlite3_column_int(pStmt, 5);
			cd.defence = sqlite3_column_int(pStmt, 6);
			cd.level = sqlite3_column_int(pStmt, 7);
			cd.race = sqlite3_column_int(pStmt, 8);
			cd.attribute = sqlite3_column_int(pStmt, 9);
			cd.category = sqlite3_column_int(pStmt, 10);
			_datas.insert(std::make_pair(cd.code, cd));
			len = BufferIO::DecodeUTF8(
					(const char*) sqlite3_column_text(pStmt, 12), strBuffer);
			if (len) {
				cs.name = new wchar_t[len + 1];
				memcpy(cs.name, strBuffer, (len + 1) * sizeof(char));
			} else
				cs.name = 0;
			len = BufferIO::DecodeUTF8(
					(const char*) sqlite3_column_text(pStmt, 13), strBuffer);
			if (len) {
				cs.text = new wchar_t[len + 1];
				memcpy(cs.text, strBuffer, (len + 1) * sizeof(wchar_t));
			} else {
				cs.text = new wchar_t[1];
				cs.text[0] = 0;
			}
			for (int i = 14; i < 30; ++i) {
				len = BufferIO::DecodeUTF8(
						(const char*) sqlite3_column_text(pStmt, i), strBuffer);
				if (len) {
					cs.desc[i - 14] = new wchar_t[len + 1];
					memcpy(cs.desc[i - 14], strBuffer,
							(len + 1) * sizeof(wchar_t));
				} else
					cs.desc[i - 14] = 0;
			}
			_strings.insert(std::make_pair(cd.code, cs));
		}
	} while (step != SQLITE_DONE);
	sqlite3_finalize(pStmt);
	sqlite3_close(pDB);
	return true;
}

bool YGODataManager::LoadStrings(const char* file) {
	return true;
}

bool YGODataManager::Error(sqlite3* pDB, sqlite3_stmt* pStmt) {
	BufferIO::DecodeUTF8(sqlite3_errmsg(pDB), strBuffer);
	if(pStmt)
		sqlite3_finalize(pStmt);
	sqlite3_close(pDB);
	return false;
}

bool YGODataManager::GetData(int code, CardData* pData) {
	auto cdit = _datas.find(code);
	if(cdit == _datas.end())
		return false;
	if(pData)
		*pData = *((CardData*)&cdit->second);
	return true;
}

code_pointer YGODataManager::GetCodePointer(int code) {
	return _datas.find(code);
}

bool YGODataManager::GetString(int code, CardString* pStr) {
	auto csit = _strings.find(code);
	if(csit == _strings.end()) {
		pStr->name = const_cast<wchar_t*>(unknown_string);
		pStr->text = const_cast<wchar_t*>(unknown_string);
		return false;
	}
	*pStr = csit->second;
	return true;
}

const wchar_t* YGODataManager::GetName(int code) {
	auto csit = _strings.find(code);
	if(csit == _strings.end())
		return unknown_string;
	if(csit->second.name)
		return csit->second.name;
	return unknown_string;
}

const wchar_t* YGODataManager::GetText(int code) {
	auto csit = _strings.find(code);
	if(csit == _strings.end())
		return unknown_string;
	if(csit->second.text)
		return csit->second.text;
	return unknown_string;
}

const wchar_t* YGODataManager::GetDesc(int strCode) {
	if(strCode < 10000)
		return GetSysString(strCode);
	int code = strCode >> 4;
	int offset = strCode & 0xf;
	auto csit = _strings.find(code);
	if(csit == _strings.end())
		return unknown_string;
	if(csit->second.desc[offset])
		return csit->second.desc[offset];
	return unknown_string;
}

const wchar_t* YGODataManager::GetSysString(int code) {
	if(code < 0 || code >= 2048 || _sysStrings[code] == 0)
		return unknown_string;
	return _sysStrings[code];
}

const wchar_t* YGODataManager::GetVictoryString(int code) {
	auto csit = _victoryStrings.find(code);
	if(csit == _victoryStrings.end())
		return unknown_string;
	return csit->second;
}

const wchar_t* YGODataManager::GetCounterName(int code) {
	auto csit = _counterStrings.find(code);
	if(csit == _counterStrings.end())
		return unknown_string;
	return csit->second;
}

const wchar_t* YGODataManager::GetNumString(int num) {
	return numStrings[num];
}

const wchar_t* YGODataManager::FormatLocation(int location) {
	int filter = 1, i = 1000;
	while(filter != location) {
		filter <<= 1;
		i++;
	}
	if(filter == location)
		return GetSysString(i);
	else
		return unknown_string;
}

const wchar_t* YGODataManager::FormatAttribute(int attribute) {
	wchar_t* p = attBuffer;
	int filter = 1, i = 1010;
	for(; filter != 0x80; filter <<= 1, ++i) {
		if(attribute & filter) {
			BufferIO::CopyWStrRef(GetSysString(i), p, 16);
			*p = L'|';
			*++p = 0;
		}
	}
	if(p != attBuffer)
		*(p - 1) = 0;
	else
		return unknown_string;
	return attBuffer;
}

const wchar_t* YGODataManager::FormatRace(int race) {
	wchar_t* p = racBuffer;
	int filter = 1, i = 1020;
	for(; filter != 0x800000; filter <<= 1, ++i) {
		if(race & filter) {
			BufferIO::CopyWStrRef(GetSysString(i), p, 16);
			*p = L'|';
			*++p = 0;
		}
	}
	if(p != racBuffer)
		*(p - 1) = 0;
	else
		return unknown_string;
	return racBuffer;
}

const wchar_t* YGODataManager::FormatType(int type) {
	wchar_t* p = tpBuffer;
	int filter = 1, i = 1050;
	for(; filter != 0x1000000; filter <<= 1, ++i) {
		if(type & filter) {
			BufferIO::CopyWStrRef(GetSysString(i), p, 16);
			*p = L'|';
			*++p = 0;
		}
	}
	if(p != tpBuffer)
		*(p - 1) = 0;
	else
		return unknown_string;
	return tpBuffer;
}

int YGODataManager::CardReader(int code, void* pData) {
	if(!s_dataManager->GetData(code, (CardData*)pData))
		memset(pData, 0, sizeof(CardData));
	return 0;
}

} /* namespace ygo */


