
FLAGS_OPT =

SOURCES = main.cpp								\
		HashTable/list.cpp            			\
		HashTable/hashTable.cpp       			\
		HashTable/hashs.cpp       				\
		hashs-asm.o								\
		FileProcess/fileProcess.cpp   			\
		FileProcess/bufferPreparate.cpp   		\
		ResultProcess/measureProcess.cpp   		\
		ResultProcess/measureDistribution.cpp	\
		ResultProcess/plotBuild.cpp		  	

hashTable_0: hashs-asm.o
	g++ $(SOURCES) $(FLAGS)					\
		-o hashTable_0.exe

hashTable_1: hashs-asm.o
	g++ $(SOURCES) $(FLAGS)	-O3				\
		-o hashTable_1.exe

hashTable_2: hashs-asm.o
	g++ $(SOURCES) $(FLAGS)	-O3				\
		-DFIRST_OPTIMIZATION				\
		-o hashTable_2.exe

hashTable_3: hashs-asm.o
	g++ $(SOURCES) $(FLAGS)	-O3				\
		-DFIRST_OPTIMIZATION				\
		-DSECOND_OPTIMIZATION				\
		-o hashTable_3.exe

hashTable_4: hashs-asm.o
	g++ $(SOURCES) $(FLAGS)	-O3				\
		-DFIRST_OPTIMIZATION				\
		-DSECOND_OPTIMIZATION				\
		-DTHIRD_OPTIMIZATION				\
		-o hashTable_4.exe
		
union: hashs-asm.o
	g++ $(SOURCES) $(FLAGS)					\
		-DUNION								\
		-o union.exe

hashs-asm.o: HashTable/crc32.asm
	nasm -f elf64 HashTable/crc32.asm -o hashs-asm.o

makedirs:
	mkdir -p Distribution /				\
			 Measurements /				\
			 Plot-py /					\
			 img /

.PHONY: simple union simple-avx union-avx makedirs

 FLAGS_AVX = -mmmx						\
 		-msse 							\
		-msse2 							\
		-mssse3 						\
		-msse4.1 						\
		-msse4.2 						\
		-mavx 							\
		-mavx2 							

FLAGS =  $(FLAGS_OPT) $(FLAGS_AVX) 					\
		-D											\
		_DEBUG										\
		-ggdb3										\
		-pie										\
		-std=c++17									\
		-Waggressive-loop-optimizations 			\
		-Wall										\
		-Wc++14-compat								\
		-Wcast-align								\
		-Wcast-qual									\
		-Wchar-subscripts							\
		-Wconditionally-supported					\
		-Wconversion								\
		-Wctor-dtor-privacy							\
		-Weffc++									\
		-Wempty-body								\
		-Werror=vla									\
		-Wextra										\
		-Wfloat-equal								\
		-Wformat-nonliteral							\
		-Wformat-security							\
		-Wformat-signedness							\
		-Wformat=2									\
		-Winit-self									\
		-Winline									\
		-Wlarger-than=8192							\
		-Wlogical-op								\
		-Wmissing-declarations						\
		-Wno-literal-suffix							\
		-Wno-missing-field-initializers				\
		-Wno-narrowing								\
		-Wno-old-style-cast							\
		-Wno-varargs								\
		-Wnon-virtual-dtor							\
		-Wopenmp-simd								\
		-Woverloaded-virtual						\
		-Wpacked									\
		-Wpointer-arith								\
		-Wredundant-decls							\
		-Wshadow									\
		-Wsign-conversion							\
		-Wsign-promo								\
		-Wstack-protector							\
		-Wstack-usage=8192							\
		-Wstrict-null-sentinel						\
		-Wstrict-overflow=2							\
		-Wsuggest-attribute=noreturn				\
		-Wsuggest-final-methods						\
		-Wsuggest-final-types						\
		-Wsuggest-override							\
		-Wswitch-default							\
		-Wswitch-enum								\
		-Wsync-nand									\
		-Wundef										\
		-Wunreachable-code							\
		-Wunused									\
		-Wuseless-cast								\
		-Wvariadic-macros							\
		-fcheck-new									\
		-flto-odr-type-merging						\
		-fno-omit-frame-pointer						\
		-fPIE										\
		-fsized-deallocation						\
		-fstack-protector							\
		-fstrict-overflow							
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
		