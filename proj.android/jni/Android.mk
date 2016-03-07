LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := wantedcpp/main.cpp \
                   ../../Classes/AppData.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameCenter/GameCenter.cpp \
                   ../../Classes/GameCenter/GameCenterHelper.cpp \
                   ../../Classes/GameCenter/GameCenterMessage.cpp \
                   ../../Classes/GameCenter/Game.cpp \
                   ../../Classes/GameCenter/GameClientServerListener.cpp \
                   ../../Classes/GameCenter/GameClientListener.cpp \
                   ../../Classes/GameCenter/GameServerListener.cpp \
                   ../../Classes/Scenes/Duel.cpp \
                   ../../Classes/Scenes/Cloud.cpp \
                   ../../Classes/Scenes/Character.cpp \
                   ../../Classes/Scenes/Target.cpp \
                   ../../Classes/Scenes/Countdown.cpp \
                   ../../Classes/Jni/Java_com_jino_wanted_WantedHelper.cpp \
                   ../../Classes/Utils/WantedLayer.cpp \
                   ../../Classes/Menus/BaseMenu.cpp \
                   ../../Classes/Menus/MenuItem.cpp \
                   ../../Classes/Menus/DuelMenu.cpp \
                   ../../Classes/Menus/MainMenu.cpp	\
                   ../../Classes/Menus/CharacterSelection.cpp	
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
