/*
 * YGONetworkEventAdapter.h
 *
 *  Created on: 2014年2月4日
 *      Author: mabin
 */

#ifndef YGONETWORKEVENTADAPTER_H_
#define YGONETWORKEVENTADAPTER_H_

#include "CommonGui.h"
#include "../network/mymutex.h"
#include "../network/mysignal.h"
USING_NS_CC;

namespace ygo {

typedef struct client_evt_param_compat {
	int event_type;
	CTOS_PlayerInfo* ctos_playerinfo;
	union {
		CTOS_CreateGame* ctos_creategame;
		CTOS_JoinGame* ctos_joingame;
	};
} CLIENT_EVT_PARAM_COMPAT;

class YGONetworkEventAdapter: public cocos2d::CCObject {
public:
	YGONetworkEventAdapter();
	static YGONetworkEventAdapater* sharedEventAdapter();
	virtual ~YGONetworkEventAdapter();
	void registerEvent(const char* eventType, CCObject* target,  SEL_CallFuncO selector);
	void unregisterEvent(const char* eventType, CCObject* target);
	void postEvent(const char* eventType, CCObject* = NULL);
	void registerCommand(int cmd, CCObject *target, SEL_CallFunc cmd_handler);
	void unregisterCommand(int cmd, CCObject *target);
	void runCmdOnGLThread(int cmd);
	/* *
	 *  @notice 不要在gl线程中调用此方法！
	 */
	void postEventBlocked(const char* eventType, int max_blocking_time_out, CCObject* = NULL);
	void decreaseBlockingFrame();
	bool testBlockingFrame();
private:
	Mutex* m_mutex;
	Signal* m_signal;
	int m_blockingFrame;
	CCNotificationCenter* m_pEventDispatcher;
	void setBlocking(int blocking_frame);
	CCDictionary* m_cmdDictionary;
};

} /* namespace ygo */
#endif /* YGONETWORKEVENTADAPTER_H_ */
