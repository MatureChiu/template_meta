CC=gcc
CXX=g++

LOCAL_INCLUDE_PATH = include
LOCAL_SRC_PATH = src
LOCAL_SRC_FILES = $(wildcard $(LOCAL_SRC_PATH)/*.cpp)
LOCAL_INCLUDE_FILES = $(patsubst %.cpp,$(LOCAL_INCLDUE_PATH)/%.h,$(notdir $(LOCAL_SRC_FILES)))
LOCAL_OBJ_FILES = $(patsubst %.cpp,%.o,$(notdir $(LOCAL_SRC_FILES)))
LOCAL_MODULE ?= main 
LOCAL_INSTALL = out 

CFLAGS += -Wall -g
CFLAGS += -I$(LOCAL_INCLUDE_PATH)
CFLAGS += -std=c++11 -pthread

LDFLAGS += -Wall -g -std=c++11 -pthread

.PHONY: all install clean disclean

$(LOCAL_OBJ_FILES):	$(LOCAL_SRC_FILES)
	@$(CXX) -Wall -c $^ $(CFLAGS)

$(LOCAL_MODULE): $(LOCAL_OBJ_FILES)
	@$(CXX) -o $@ $^ $(LDFLAGS)

all: $(LOCAL_MODULE) install

install:
	@mkdir -p $(LOCAL_INSTALL)
	@mv $(LOCAL_MODULE) $(LOCAL_OBJ_FILES) $(LOCAL_INSTALL)

clean:
	@rm -rf $(LOCAL_MODULE) $(LOCAL_OBJ_FILES)
	@rm -rf $(LOCAL_INSTALL)

disclean:
	@$(MAKE) clean

