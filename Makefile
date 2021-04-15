# quisp/Makefile is generated by opp_makemake.
# you can create this file with `$ make makefile-exe` or `$ make maakefile-lib`
# or also OMNet++IDE
QUISP_MAKEFILE=./quisp/Makefile
# when you setup OMNet++IDE, this file will be generated.
# this file contaians the options for opp_makemake.
# see also https://github.com/sfc-aqua/quisp/blob/master/doc/Build_on_docker.md
OPP_BUILD_SPEC_FILE=./quisp/.oppbuildspec

ifneq (,$(wildcard $(QUISP_MAKEFILE)))
include $(QUISP_MAKEFILE)
endif

# you can pass the file path you want to check as SRCS environment variable. see the example below.
# $ SRCS=./quisp/modules/Application.cc make tidy # checks only Application.cc
# $ make tidy # checks all sources
SRCS?=./quisp/modules/*.cc ./quisp/rules/*.cc 
HEADERS=./quisp/modules/*.h ./quisp/rules/*.h

ifneq (,$(wildcard $(OPP_BUILD_SPEC_FILE)))
# this need GNU Make 4.2 or later
# see also https://lists.gnu.org/archive/html/info-gnu/2016-05/msg00013.html
OPP_BUILD_SPEC=$(file < $(OPP_BUILD_SPEC_FILE))
INCLUDES=$(filter -I%,$(OPP_BUILD_SPEC))
endif
$(warning $(INCLUDES))

.PHONY: all tidy format ci makefile-exe makefile-lib checkmakefile

all: makefile-exe

tidy:
	clang-tidy -header-filter="./quisp/(rules|modules)/.*.h" $(SRCS) -- $(COPTS:-I.=-I./quisp)

format:
	clang-format -i $(SRCS) $(HEADERS)

ci: checkmakefile
	@make -C ./quisp msgheaders
	@clang-format $(SRCS) $(HEADERS) -output-replacements-xml | grep -c "<replacement " -q ; if [ $$? -ne 1 ]; then echo "error: run make format and then push it again"; exit 1; fi
	@clang-tidy -warnings-as-errors="*" -header-filter="./quisp/(rules|modules)/.*.h" $(SRCS) -- $(COPTS:-I.=-I./quisp)

makefile-exe:
	cd quisp && opp_makemake -f --deep -O out $(INCLUDES)

makefile-so: 
	cd quisp && opp_makemake -f --deep -O out $(INCLUDES) --make-so

checkmakefile:
	@if [ ! -f $(QUISP_MAKEFILE) ]; then \
	echo; \
	echo '===================================================================================================='; \
	echo 'quisp/Makefile does not exist. Please use "make makefile-exe" or "make makefile-lib" to generate it!'; \
	echo '===================================================================================================='; \
	echo; \
	exit 1; \
	fi


