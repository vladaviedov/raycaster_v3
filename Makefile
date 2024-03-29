CXX=g++
CXXFLAGS=-Wall -Wextra -g
LDFLAGS=-lglfw -lGL -lGLU

OUT=build/rc3
SUBDIRS=$(shell cd src && find * -type d)
MKSUBDIRS=$(addprefix build/, $(SUBDIRS))
SRCS=$(shell cd src && find * -type f -name '*.cpp')
OBJS=$(addprefix build/, $(SRCS:.cpp=.o))

.PHONY:
all: build $(MKSUBDIRS) $(OUT)

$(OUT): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

build:
	mkdir -p build

# Mkdir template
define mk_subdir
build/$(1):
	mkdir -p $$@
endef

# Build template
define compile_subdir
build/$(1)%.o: src/$(1)%.cpp
	$(CXX) $(CXXFLAGS) -c $$< -o $$@
endef

# Build root
$(eval $(call mk_subdir,))
$(eval $(call compile_subdir,))

# Build subdirectories
$(foreach subdir, $(SUBDIRS), $(eval $(call mk_subdir,$(subdir))))
$(foreach subdir, $(SUBDIRS), $(eval $(call compile_subdir,$(subdir))))

.PHONY: clean
clean:
	rm -rf build
