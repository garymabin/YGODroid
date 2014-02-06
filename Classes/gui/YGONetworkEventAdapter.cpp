/*
 * YGONetworkEventAdapter.cpp
 *
 *  Created on: 2014年2月4日
 *      Author: mabin
 */

#include "YGONetworkEventAdapter.h"

namespace ygo {

static YGONetworkEventAdapter* s_adapter;

YGONetworkEventAdapter::YGONetworkEventAdapter() {
	// TODO Auto-generated constructor stub
	m_blockingFrame = 0;
	m_mutex = new Mutex();
	m_signal = new Signal();
	m_pEventDispatcher = CCNotificationCenter::sharedNotificationCenter();
	m_cmdDictionary = CCDictionary::create();
	m_cmdDictionary->retain();
}

YGONetworkEventAdapater* YGONetworkEventAdapter::sharedEventAdapter() {
	if (!s_adapter) {
		s_adapter = new YGONetworkEventAdapter();
	}
	return s_adapter;
}

YGONetworkEventAdapter::~YGONetworkEventAdapter() {
	// TODO Auto-generated destructor stub
	CC_SAFE_DELETE(m_mutex);
	CC_SAFE_DELETE(m_signal);
	CC_SAFE_RELEASE(m_cmdDictionary);
}

void YGONetworkEventAdapter::registerEvent(const char* eventType,
		CCObject* target,  SEL_CallFuncO selector) {
	m_mutex->Lock();
	m_pEventDispatcher->addObserver(target, selector, eventType, NULL);
	m_mutex->Unlock();
}

void YGONetworkEventAdapter::unregisterEvent(const char* eventType,
		CCObject* target) {
	m_mutex->Lock();
	m_pEventDispatcher->removeObserver(target, eventType)
	m_mutex->Unlock();
}

void YGONetworkEventAdapter::postEvent(const char* eventType, CCObject* object) {
	m_mutex->Lock();
	m_pEventDispatcher->postNotification(eventType, object);
	m_mutex->Unlock();
}

inline void YGONetworkEventAdapter::decreaseBlockingFrame() {
	if (m_blockingFrame && !--m_blockingFrame) {
		m_signal->Set();
	}
}

inline bool YGONetworkEventAdapter::testBlockingFrame() {
	return m_blockingFrame > 0;
}

void YGONetworkEventAdapter::registerCommand(int cmd, CCObject* target,
		SEL_CallFunc cmd_handler) {
	m_cmdDictionary->setObject((CCObject*)cmd_handler, (int)target);
}

void YGONetworkEventAdapter::unregisterCommand(int cmd, CCObject* target) {
	m_cmdDictionary->removeObjectForKey(target);
}

void YGONetworkEventAdapter::runCmdOnGLThread(int cmd) {
	CCArray* arrays = m_cmdDictionary->allKeys();
	CCObject* object = NULL;
	CCARRAY_FOREACH(arrays, object) {
		if (object) {
			SEL_CallFunc handler = callfunc_selector(m_cmdDictionary->objectForKey((int)object));
			(object->*handler)();
		}
	}
}

inline void YGONetworkEventAdapter::setBlocking(int blocking_frame) {
	m_signal->Reset();
	m_blockingFrame = blocking_frame;
	m_signal->Wait();
}

void YGONetworkEventAdapter::postEventBlocked(const char* eventType, int max_blocking_frame, CCObject*) {
	m_mutex->Lock();
	m_pEventDispatcher->postNotification(eventType, object);
	setBlocking(max_blocking_frame);
	m_mutex->Unlock();
}

} /* namespace ygo */
