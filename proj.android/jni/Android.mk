LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   ../../Classes/database/parser/DataParser.cpp \
				   ../../Classes/database/parser/PlanetInfoParser.cpp \
				   ../../Classes/database/parser/StageInfoParser.cpp \
				   ../../Classes/database/PlanetInfo.cpp \
				   ../../Classes/database/StageInfo.cpp \
				   ../../Classes/manager/BallManager.cpp \
				   ../../Classes/manager/StageManager.cpp \
				   ../../Classes/model/Ball.cpp \
				   ../../Classes/model/FireBall.cpp \
				   ../../Classes/model/GrowButton.cpp \
				   ../../Classes/model/GuideDots.cpp \
				   ../../Classes/model/PlanetBtn.cpp \
				   ../../Classes/model/Slot.cpp \
				   ../../Classes/model/StageBtn.cpp \
				   ../../Classes/scene/GameScene.cpp \
				   ../../Classes/scene/MainMenuScene.cpp \
				   ../../Classes/scene/ResultScene.cpp \
				   ../../Classes/scene/StageChooserScene.cpp \
				   ../../Classes/scene/UniverseScene.cpp \
				   ../../Classes/sqlite/Column.cpp \
				   ../../Classes/sqlite/Database.cpp \
				   ../../Classes/sqlite/sqlite3.c \
				   ../../Classes/sqlite/SqliteUtil.cpp \
				   ../../Classes/sqlite/Statement.cpp \
				   ../../Classes/sqlite/Transaction.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
