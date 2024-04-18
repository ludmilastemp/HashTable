a.exe:
	g++ main.cpp					  	\
		HashTable/list.cpp            	\
		HashTable/hashs.cpp 	      	\
		HashTable/hashTable.cpp       	\
		FileProcess/fileProcess.cpp   	\
		-o a.exe -O2 $(FLAGS_AVX) $(FLAGS)
		
avx:
	g++ main.cpp					  	\
		HashTable/list.cpp            	\
		HashTable/hashs.cpp 	      	\
		HashTable/hashTable.cpp       	\
		FileProcess/fileProcess.cpp   	\
		-o avx.exe -O2 $(FLAGS_AVX) $(FLAGS) -DAVX

.PHONY: a.exe

 FLAGS_AVX = -mmmx						\
 		-msse 							\
		-msse2 							\
		-mssse3 						\
		-msse4.1 						\
		-msse4.2 						\
		-mavx 							\
		-mavx2 							
 

FLAGS = -D											\
		_DEBUG										\
		-ggdb3										\
		-O0											\
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
		