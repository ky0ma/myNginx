ifeq ($(DEBUG),true)
#-g是生成调试信息。GNU调试器可以利用该信息
CC = g++ -g
VERSION = debug
else
CC = g++
VERSION = release
endif

# %$(wildcard *.cxx)表示扫描当前目录下所有.cxxxx文件，并保存
SRCS = $(wildcard *.cxx)

# 将SRCS中扫描到的.cxx文件名后缀改为.o，方便生成文件名
OBJS = $(SRCS:.cxx=.o)

# 把字符串中的.cxx替换为.d
DEPS = $(SRCS:.cxx=.d)

# 指定BIN文件的位置。addprefix是增加字符串前缀
# BUILD_ROOT = /mnt/hgfs/linux/
BIN := $(addprefix $(BUILD_ROOT)/,$(BIN))

# 定义存放ojb文件的目录，目录统一到一个位置才方便后续链接
LINK_OBJ_DIR = $(BUILD_ROOT)/app/link_obj
# 存放.d文件目录
DEP_DIR = $(BUILD_ROOT)/app/dep

# 创建保存目录，-p是递归创建目录，没有就创建，有就不需要创建了
$(shell mkdir -p $(LINK_OBJ_DIR))
$(shell mkdir -p $(DEP_DIR))

# 给目标文件名怎加前缀，保存到对应的目录中
OBJS := $(addprefix $(LINK_OBJ_DIR)/,$(OBJS))
DEPS := $(addprefix $(DEP_DIR)/,$(DEPS))

# 扫描LINK_OBJ_DIR目录下已经生成的所有.o文件
LINK_OBJ = $(wildcard $(LINK_OBJ_DIR)/*.o)
# 添加未编译文件的.o文件（在这轮要编译），
LINK_OBJ += $(OBJS)

#---------------------------------------------------------------

all:$(DEPS) $(OBJS) $(BIN)

# 如果DEPS中文件不为空
ifneq ("$(wildcard $(DEPS))", "")
include $(DEPS)
endif

TEXT = "123"
#----------------------------------------------------------------1begin------------------
#$(BIN):$(OBJS)
$(BIN):$(LINK_OBJ)
	@echo "------------------------build $(VERSION) mode--------------------------------"		
	@echo "     __         ____                 "
	@echo "    / /____  __/ __ \____ ___  ____ _"
	@echo "   / //_/ / / / / / / __ \`__ \/ __ \`/"
	@echo "  / ,< / /_/ / /_/ / / / / / / /_/ / "
	@echo " /_/|_|\__, /\____/_/ /_/ /_/\__,_/  "
	@echo "      /____/                         "
	@echo "\nSUCCESS"
#一些变量：$@：目标，     $^：所有目标依赖
# gcc -o 是生成可执行文件
	$(CC) -o $@ $^

#----------------------------------------------------------------1end-------------------


#---------------------------------------------------------------
# %.o:%.cxx
$(LINK_OBJ_DIR)/%.o:%.cxx
# gcc -c生成.o目标文件 -I指定头文件的路径
	$(CC) -I$(INCLUDE_PATH) -o $@ -c $(filter %.cxx,$^)

#---------------------------------------------------------------



#---------------------------------------------------------------
# 当修改一个.h时，也能够让make自动重新编译我们的项目，所以，我们需要指明让.o依赖于.h文件
# 使用“ gcc -MM c程序文件名 ” 来获取.o依赖于哪些.h文件

$(DEP_DIR)/%.d:%.cxx
	echo -n $(LINK_OBJ_DIR)/ > $@
	gcc -I$(INCLUDE_PATH) -MM $^ >> $@


#---------------------------------------------------------------


#----------------------------------------------------------------nbegin-----------------
#clean:			
#rm 的-f参数是不提示强制删除
#可能gcc会产生.gch这个优化编译速度文件
#	rm -f $(BIN) $(OBJS) $(DEPS) *.gch
#----------------------------------------------------------------nend------------------





