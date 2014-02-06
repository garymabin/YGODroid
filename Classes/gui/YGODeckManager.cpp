/*
 * YGODeckManager.cpp
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#include "YGODeckManager.h"

USING_NS_CC;

namespace ygo {

static YGODeckManager* s_pDeckManager = NULL;

YGODeckManager::YGODeckManager() {
	m_pDataManager = YGODataManager::sharedDataManager();
}

YGODeckManager* YGODeckManager::sharedDeckManager() {
	if (!s_pDeckManager) {
		s_pDeckManager = new YGODeckManager();
	}
	return s_pDeckManager;
}

void YGODeckManager::LoadLFList() {
	const char* path = CCFileUtils::sharedFileUtils()->fullPathForFilename(
			"lflist.conf").c_str();
	LFList* cur = NULL;
	FILE* fp = fopen(path, "r");
	char linebuf[256];
	wchar_t strBuffer[256];
	if (fp) {
		fseek(fp, 0, SEEK_END);
		int fsize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		fgets(linebuf, 256, fp);
		while (ftell(fp) < fsize) {
			fgets(linebuf, 256, fp);
			if (linebuf[0] == '#')
				continue;
			int p = 0, sa = 0, code, count;
			if (linebuf[0] == '!') {
				sa = BufferIO::DecodeUTF8((const char*) (&linebuf[1]),
						strBuffer);
				while (strBuffer[sa - 1] == L'\r' || strBuffer[sa - 1] == L'\n')
					sa--;
				LFList* pNewlist = new LFList();
				_lfList.push_back(pNewlist);
				cur = _lfList[_lfList.size() - 1];
				memcpy(cur->listName, (const void*) strBuffer, 40);
				cur->listName[sa] = 0;
				cur->content = new std::unordered_map<int, int>;
				cur->hash = 0x7dfcee6a;
				continue;
			}
			while (linebuf[p] != ' ' && linebuf[p] != '\t' && linebuf[p] != 0)
				p++;
			if (linebuf[p] == 0)
				continue;
			linebuf[p++] = 0;
			sa = p;
			code = atoi(linebuf);
			if (code == 0)
				continue;
			while (linebuf[p] == ' ' || linebuf[p] == '\t')
				p++;
			while (linebuf[p] != ' ' && linebuf[p] != '\t' && linebuf[p] != 0)
				p++;
			linebuf[p] = 0;
			count = atoi(&linebuf[sa]);
			if (cur == NULL)
				continue;
			(*cur->content)[code] = count;
			cur->hash = cur->hash ^ ((code << 18) | (code >> 14))
					^ ((code << (27 + count)) | (code >> (5 - count)));
		}
		fclose(fp);
	}
	LFList* pNolimit = new LFList();
	myswprintf(pNolimit->listName, L"N/A");
	pNolimit->hash = 0;
	pNolimit->content = new std::unordered_map<int, int>;
	_lfList.push_back(pNolimit);
}

wchar_t* YGODeckManager::GetLFListName(int lfhash) {
	for (size_t i = 0; i < _lfList.size(); ++i) {
		if (_lfList[i]->hash == (unsigned int) lfhash) {
			return _lfList[i]->listName;
		}
	}
	return const_cast<wchar_t *>(YGODataManager::unknown_string);
}

int YGODeckManager::CheckLFList(Deck& deck, int lfhash, bool allow_ocg,
		bool allow_tcg) {
	std::unordered_map<int, int> ccount;
	std::unordered_map<int, int>* list = 0;
	for (size_t i = 0; i < _lfList.size(); ++i) {
		if (_lfList[i]->hash == (unsigned int) lfhash) {
			list = _lfList[i]->content;
			break;
		}
	}
	if (!list)
		return 0;
	int dc = 0;
	if (deck.main.size() < 40 || deck.main.size() > 60 || deck.extra.size() > 15
			|| deck.side.size() > 15)
		return 1;
	for (size_t i = 0; i < deck.main.size(); ++i) {
		code_pointer cit = deck.main[i];
		if ((!allow_ocg && (cit->second.ot == 0x1))
				|| (!allow_tcg && (cit->second.ot == 0x2)))
			return cit->first;
		if (cit->second.type
				& (TYPE_FUSION | TYPE_SYNCHRO | TYPE_XYZ | TYPE_TOKEN))
			return 1;
		int code = cit->second.alias ? cit->second.alias : cit->first;
		ccount[code]++;
		dc = ccount[code];
		auto it = list->find(code);
		if (dc > 3 || (it != list->end() && dc > it->second))
			return cit->first;
	}
	for (size_t i = 0; i < deck.extra.size(); ++i) {
		code_pointer cit = deck.extra[i];
		if ((!allow_ocg && (cit->second.ot == 0x1))
				|| (!allow_tcg && (cit->second.ot == 0x2)))
			return cit->first;
		int code = cit->second.alias ? cit->second.alias : cit->first;
		ccount[code]++;
		dc = ccount[code];
		auto it = list->find(code);
		if (dc > 3 || (it != list->end() && dc > it->second))
			return cit->first;
	}
	for (size_t i = 0; i < deck.side.size(); ++i) {
		code_pointer cit = deck.side[i];
		if ((!allow_ocg && (cit->second.ot == 0x1))
				|| (!allow_tcg && (cit->second.ot == 0x2)))
			return cit->first;
		int code = cit->second.alias ? cit->second.alias : cit->first;
		ccount[code]++;
		dc = ccount[code];
		auto it = list->find(code);
		if (dc > 3 || (it != list->end() && dc > it->second))
			return cit->first;
	}
	return 0;
}

void YGODeckManager::LoadDeck(Deck& deck, int* dbuf, int mainc, int sidec) {
	deck.clear();
	int code;
	CardData cd;
	for (int i = 0; i < mainc; ++i) {
		code = dbuf[i];
		if (!m_pDataManager->GetData(code, &cd))
			continue;
		if (cd.type & TYPE_TOKEN)
			continue;
		else if ((cd.type & 0x802040) && deck.extra.size() < 15) {
			deck.extra.push_back(m_pDataManager->GetCodePointer(code));
		} else if (deck.main.size() < 60) {
			deck.main.push_back(m_pDataManager->GetCodePointer(code));
		}
	}
	for (int i = 0; i < sidec; ++i) {
		code = dbuf[mainc + i];
		if (!m_pDataManager->GetData(code, &cd))
			continue;
		if (cd.type & TYPE_TOKEN)
			continue;
		if (deck.side.size() < 15)
			deck.side.push_back(m_pDataManager->GetCodePointer(code));
	}
}

void YGODeckManager::RefreshDeckList(std::vector<CCString*>* deckList) {
//#ifdef _WIN32
//	WIN32_FIND_DATAW fdataw;
//	HANDLE fh = FindFirstFileW(L"./deck/*.ydk", &fdataw);
//	if(fh == INVALID_HANDLE_VALUE)
//		return;
//	do {
//		if(!(fdataw.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//			wchar_t* pf = fdataw.cFileName;
//			while(*pf) pf++;
//			while(*pf != L'.') pf--;
//			*pf = 0;
//			cbDeck->addItem(fdataw.cFileName);
//		}
//	} while(FindNextFileW(fh, &fdataw));
//	FindClose(fh);
//#else
	DIR * dir;
	struct dirent * dirp;
	const char* path = CCFileUtils::sharedFileUtils()->fullPathForFilename("deck").c_str();
	if((dir = opendir(path)) == NULL)
		return;
	while((dirp = readdir(dir)) != NULL) {
		size_t len = strlen(dirp->d_name);
		if(len < 5 || strcasecmp(dirp->d_name + len - 4, ".ydk") != 0)
			continue;
		dirp->d_name[len - 4] = 0;
//		wchar_t wname[256];
//		BufferIO::DecodeUTF8(dirp->d_name, wname);
		deckList->push_back(CCString::createWithData((unsigned char *)dirp->d_name, strlen(dirp->d_name) + 1));
	}
//#endif
//	for(size_t i = 0; i < cbDeck->getItemCount(); ++i) {
//		if(!wcscmp(cbDeck->getItem(i), gameConf.lastdeck)) {
//			cbDeck->setSelected(i);
//			break;
//		}
//	}
}

bool YGODeckManager::LoadSide(Deck& deck, int* dbuf, int mainc, int sidec) {
	std::unordered_map<int, int> pcount;
	std::unordered_map<int, int> ncount;
	for (size_t i = 0; i < deck.main.size(); ++i)
		pcount[deck.main[i]->first]++;
	for (size_t i = 0; i < deck.extra.size(); ++i)
		pcount[deck.extra[i]->first]++;
	for (size_t i = 0; i < deck.side.size(); ++i)
		pcount[deck.side[i]->first]++;
	Deck ndeck;
	LoadDeck(ndeck, dbuf, mainc, sidec);
	if (ndeck.main.size() != deck.main.size()
			|| ndeck.extra.size() != deck.extra.size())
		return false;
	for (size_t i = 0; i < ndeck.main.size(); ++i)
		ncount[ndeck.main[i]->first]++;
	for (size_t i = 0; i < ndeck.extra.size(); ++i)
		ncount[ndeck.extra[i]->first]++;
	for (size_t i = 0; i < ndeck.side.size(); ++i)
		ncount[ndeck.side[i]->first]++;
	for (auto cdit = ncount.begin(); cdit != ncount.end(); ++cdit)
		if (cdit->second != pcount[cdit->first])
			return false;
	deck = ndeck;
	return true;
}

bool YGODeckManager::LoadDeck(const char* file) {
	int sp = 0, ct = 0, mainc = 0, sidec = 0, code;
	char deck[64];
	sprintf(deck, "deck/%s.ydk", file);
	int cardlist[128];
	const char* path =
			CCFileUtils::sharedFileUtils()->fullPathForFilename(
					deck).c_str();
	CCLOG("loaddeck, full_path = %s", path);
	bool is_side = false;
//#ifdef WIN32
//	FILE* fp = _wfopen(deck, L"r");
//#else
//	char deckfn[256];
//	BufferIO::EncodeUTF8(path, deckfn);
	FILE* fp = fopen(path, "r");
//#endif
	if (!fp)
		return false;
	char linebuf[256];
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fgets(linebuf, 256, fp);
	while (ftell(fp) < fsize && ct < 128) {
		fgets(linebuf, 256, fp);
		if (linebuf[0] == '!') {
			is_side = true;
			continue;
		}
		if (linebuf[0] < '0' || linebuf[0] > '9')
			continue;
		sp = 0;
		while (linebuf[sp] >= '0' && linebuf[sp] <= '9')
			sp++;
		linebuf[sp] = 0;
		code = atoi(linebuf);
		cardlist[ct++] = code;
		if (is_side)
			sidec++;
		else
			mainc++;
	}
	fclose(fp);
	LoadDeck(current_deck, cardlist, mainc, sidec);
	return true;
}

bool YGODeckManager::SaveDeck(Deck& deck, const char* name) {
	char file[64];
	std::string dirpath =
			CCFileUtils::sharedFileUtils()->fullPathForFilename(
					"deck");
	sprintf(file, "/%s.ydk", name);
//#ifdef WIN32
//	FILE* fp = _wfopen(file, L"w");
//#else
//	char filefn[256];
//	BufferIO::EncodeUTF8(file, filefn);
	FILE* fp = fopen(dirpath.append(file).c_str(), "w");
//#endif
	if (!fp)
		return false;
	fprintf(fp, "#created by ...\n#main\n");
	for (size_t i = 0; i < deck.main.size(); ++i)
		fprintf(fp, "%d\n", deck.main[i]->first);
	fprintf(fp, "#extra\n");
	for (size_t i = 0; i < deck.extra.size(); ++i)
		fprintf(fp, "%d\n", deck.extra[i]->first);
	fprintf(fp, "!side\n");
	for (size_t i = 0; i < deck.side.size(); ++i)
		fprintf(fp, "%d\n", deck.side[i]->first);
	fclose(fp);
	return true;
}

} /* namespace ygo */
