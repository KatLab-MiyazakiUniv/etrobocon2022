mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

# Shellスクリプトで、moduleディレクトリ中のソースコード名をオブジェクトファイル名に変換している
APPL_CXXOBJS += $(shell echo \
                    `ls ${HOME}/etrobo/workspace/etrobocon2021/module/*.cpp | \
                     sed -r 's/(\/.*)*\/(.*\.)cpp/\2o/g'`)
APPL_CXXOBJS += $(shell echo \
                    `ls ${HOME}/etrobo/workspace/etrobocon2021/module/*/*.cpp | \
                     sed -r 's/(\/.*)*\/(.*\.)cpp/\2o/g'`)

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

# ソースコードのあるディレクトリを指定する？
APPL_DIRS += \
    $(mkfile_path)app \
    $(mkfile_path)module \
    $(mkfile_path)module/API \
    $(mkfile_path)module/BingoMotion \
    $(mkfile_path)module/CourseInfo \
    $(mkfile_path)module/Motion \
    $(mkfile_path)module/RoutePlanner

# ヘッダファイルのあるディレクトリを指定する？
INCLUDES += \
    -I$(mkfile_path)app \
    -I$(mkfile_path)module \
    -I$(ETROBO_HRP3_WORKSPACE)/etroboc_common \
    -I$(mkfile_path)module/API \
    -I$(mkfile_path)module/BingoMotion \
    -I$(mkfile_path)module/CourseInfo \
    -I$(mkfile_path)module/Motion \
    -I$(mkfile_path)module/RoutePlanner

COPTS += -std=gnu++11

