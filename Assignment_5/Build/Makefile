#==============================C++ Compilter Settings==============================#
CXX := g++
CFLAGS += -Wall -MMD -MP
CXXFLAGS += -std=c++11 $(shell wx-config --cxxflags)
LDFLAGS += -static-libgcc -static-libstdc++ -pthread $(shell wx-config --libs)

#Not likely to change, but added for compatability with certain IDEs
BUILD_DIR := .
ROOT_DIR := ..


#==============================Variables and Directories==============================#
include $(BUILD_DIR)/Makefile.variable

#Adding paths to application names
APP_PATH := $(BUILD_DIR)/$(APP_NAME)
TESTS_PATH := $(BUILD_DIR)/$(TESTS_NAME)

#Build Directory Settings
APP_OBJ_DIR := $(BUILD_DIR)/$(APP_OBJ_DIR_NAME)
TEST_OBJ_DIR := $(BUILD_DIR)/$(TESTS_OBJ_DIR_NAME)


#==============================Build Rules==============================#
.PHONY:all release debug unit-tests clean
#Default to normal build
all: release

#Target specific variable for includes, No debug flags
release: INCLUDES += $(strip $(foreach DIR,$(ALL_SRC_DIR_APP),-I$(DIR)))
release: $(APP_PATH)

#Target specific variable for enabling debugging required for GDB
debug: CXXFLAGS += -g
debug: release

#Target specific variable for includes and enable debugging required for GDB
unit-tests: INCLUDES += $(strip $(foreach DIR,$(ALL_SRC_DIR_APP) $(ALL_SRC_DIR_TEST),-I$(DIR)))
unit-tests: CXXFLAGS += -g
unit-tests: $(TESTS_PATH)

#Clean is used to remove all the build files, e.g. forcing recompile
clean:
	@printf "\033[0;36mCleaning Files\033[0m\n"
	@rm -rf $(APP_OBJ_DIR) $(TEST_OBJ_DIR)
	@rm -f $(APP_PATH) $(TESTS_PATH)


#Build the app objects directory if it doesn't exist
$(APP_OBJ_DIR):
	@mkdir $(APP_OBJ_DIR)

#Build the test objects directory if it doesn't exist
$(TEST_OBJ_DIR):
	@mkdir $(TEST_OBJ_DIR)


#==============================Dynamic Build Rule==============================#
#Create build rule for object files, strip function used to clean up spacing in terminal window
define MAKE_RULE
# Argument List (In order)
#1 File Name: Includes directory and extention
#2 Object Directory: Where the compiled object files will be placed
$(patsubst %,$(2)/%.o,$(basename $(notdir $(1)))): $(1) | $(2)
	@printf "\033[0;36mBuilding $$(@F)\033[0m\n"
	$$(strip $$(CXX) $$(CFLAGS) $$(CXXFLAGS) $$(EXTRACXXFLAGS) $$(INCLUDES) -o $$@ -c $$<)
endef


#==============================Magic Parsing==============================#
#Don't mess with these unless you know what you're doing

#Generate rules for building application object files
$(foreach EXT,$(EXTENTIONS),\
	$(foreach DIR,$(ALL_SRC_DIR_APP),\
		$(foreach FILE,$(wildcard $(DIR)/*$(EXT)),\
			$(eval $(call MAKE_RULE,$(FILE),$(APP_OBJ_DIR))) )))

#Generate rules for building test object files
$(foreach EXT,$(EXTENTIONS),\
	$(foreach DIR,$(ALL_SRC_DIR_TEST),\
		$(foreach FILE,$(wildcard $(DIR)/*$(EXT)),\
			$(eval $(call MAKE_RULE,$(FILE),$(TEST_OBJ_DIR))) )))

#Create list of needed files for application
APP_SRC_LIST := $(strip $(foreach EXT,$(EXTENTIONS),\
				$(foreach DIR,$(ALL_SRC_DIR_APP),\
					$(foreach FILE,$(filter-out $(APP_MAIN) $(TEST_MAIN),$(wildcard $(DIR)/*$(EXT))),\
						$(patsubst %,$(APP_OBJ_DIR)/%.o,$(basename $(notdir $(FILE)))) ))))

#Manually differentiate main object file to prevent multiple-mains
#APP_MAIN_OBJ := $(patsubst %,$(APP_OBJ_DIR)/%.o,$(basename $(notdir $(APP_MAIN))))

#Create list of needed files for unit tests (test files and app files)
TEST_SRC_LIST := $(strip $(foreach EXT,$(EXTENTIONS),\
				$(foreach DIR,$(ALL_SRC_DIR_TEST),\
					$(foreach FILE,$(filter-out $(TEST_MAIN) $(APP_MAIN),$(wildcard $(DIR)/*$(EXT))),\
						$(patsubst %,$(TEST_OBJ_DIR)/%.o,$(basename $(notdir $(FILE)))) ))))

#Manually differentiate main object file to prevent multiple-mains
TEST_MAIN_OBJ := $(patsubst %,$(TEST_OBJ_DIR)/%.o,$(basename $(notdir $(TEST_MAIN))))

#Include generated dependancies for detecting header changes
include $(wildcard $(APP_OBJ_DIR)/*.d)
include $(wildcard $(TEST_OBJ_DIR)/*.d)


#==============================Main Application Rules==============================#
#Build rule for making main application
$(APP_PATH): $(APP_SRC_LIST) $(APP_MAIN_OBJ)
	@printf "\033[0;36mLinking $(@F)\033[0m\n"
	$(strip $(CXX) -o $@ $^ $(LDFLAGS))
	@printf "\033[0;32mBuild successful\033[0m\n"

#Build rule for making the unit tests
$(TESTS_PATH): $(TEST_SRC_LIST) $(APP_SRC_LIST) $(TEST_MAIN_OBJ)
	@printf "\033[0;36mLinking $(@F)\033[0m\n"
	$(strip $(CXX) -o $@ $^ $(LDFLAGS))
	@printf "\033[0;32mBuild successful\033[0m\n"
