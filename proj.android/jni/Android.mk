LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := ygodroid/main.cpp \
				   ygodroid/CommonJni.cpp \
                   ../../Classes/gui/AppDelegate.cpp \
                   ../../Classes/gui/YGOMainScene.cpp \
                   ../../Classes/gui/YGOBackgroundLayer.cpp \
                   ../../Classes/gui/YGOMainMenuLayer.cpp \
                   ../../Classes/gui/XMLParser.cpp \
                   ../../Classes/gui/CCMenuItemImageFont.cpp \
                   ../../Classes/gui/YGOLANModeLayer.cpp \
                   ../../Classes/gui/YGOReplayModeLayer.cpp \
                   ../../Classes/gui/YGOSingleModeLayer.cpp \
                   ../../Classes/gui/YGOCardCell.cpp \
                   ../../Classes/gui/YGOCardDeck.cpp \
                   ../../Classes/gui/YGOCardDeckGrid.cpp \
                   ../../Classes/gui/YGODeckEditLayer.cpp \
                   ../../Classes/gui/DropDownList.cpp \
                   ../../Classes/gui/SelectedItemsSprite.cpp \
                   ../../Classes/gui/YGODeckBuilder.cpp \
                   ../../Classes/gui/YGOGameConfig.cpp \
                   ../../Classes/gui/YGOClientCard.cpp \
                   ../../Classes/gui/YGODeckManager.cpp \
                   ../../Classes/gui/YGODataManager.cpp \
                   ../../Classes/gui/YGOCardFrame.cpp \
                   ../../Classes/gui/YGOImageManager.cpp \
                   ../../Classes/gui/YGOCreateServerLayer.cpp \
                   ../../Classes/gui/YGOUILayer.cpp \
                   ../../Classes/gui/YGODuelPrepareLayer.cpp \
                   ../../Classes/gui/YGODuelScene.cpp \
                   ../../Classes/gui/YGODuelFieldLayer.cpp \
                   ../../Classes/gui/YGODuelField.cpp \
                   ../../Classes/gui/YGODuelFieldFrame.cpp \
                   ../../Classes/gui/YGOHandCardList.cpp \
                   ../../Classes/gui/YGOCardOpsPanel.cpp \
                   ../../Classes/gui/ExitDialog.cpp \
                   ../../Classes/gui/DialogLayer.cpp
                   
LOCAL_SRC_FILES += ../../Classes/network/netserver.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/sqlite3
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/libevent/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/libevent/android

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/ygodroid

LOCAL_STATIC_LIBRARIES += libssl_static
LOCAL_STATIC_LIBRARIES += libcrypto_static
LOCAL_STATIC_LIBRARIES += libevent2
LOCAL_STATIC_LIBRARIES += liblua5.2
LOCAL_STATIC_LIBRARIES += libocgcore_static

LOCAL_WHOLE_STATIC_LIBRARIES += sqlite3
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static



include $(BUILD_SHARED_LIBRARY)
$(call import-module,projects/YGODroid/Classes/openssl)
$(call import-module,projects/YGODroid/Classes/libevent)
$(call import-module,projects/YGODroid/Classes/sqlite3)
$(call import-module,projects/YGODroid/Classes/lua)
$(call import-module,projects/YGODroid/Classes/ocgcore)
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
