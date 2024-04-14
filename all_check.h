#ifndef ALL_CHECK_H
#define ALL_CHECK_H
#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"
#include "string.h"

#define ALLCHECK_SHOW_TYPE

	enum {
		ALL_CHECK_NONE	=0U,
		ALL_CHECK_ERROR	,
		ALL_CHECK_WARN	,
		ALL_CHECK_INFO	,
		ALL_CHECK_DEBUG	,
	};
#define MAX_SIZE 100

	typedef struct {
		char* func;
		char* line;
		uint32_t counter;
	}acheck_t;
extern acheck_t buffer[MAX_SIZE];

	const char* get_parent_path(const char* path);
#define ALL_CHECK_LEVEL ALL_CHECK_DEBUG
#define ALL_CHECK_SHOW_CHECK_DEBUG 1

#define ALL_PRINTF printf
#if ALL_CHECK_SHOW_CHECK_DEBUG
#define ALL_CHECK_PRINTF ALL_PRINTF
#else
#define ALL_CHECK_PRINTF 
#endif
#define AMARK(level)do{																\
	static uint32_t counter = __COUNTER__;				\
	/*将数据记录到buffer中保存下来*/															\
	if (counter >= MAX_SIZE) { ALL_PRINTF("[all_check] overflow the buffer\r\n"); return; }		\
	buffer[counter].counter++;\
	buffer[counter].func = __func__;\
	buffer[counter].line = __LINE__;\
	ALL_CHECK_PRINTF("[all_check]the if is false pos(%u)counter(%u) \r\n", counter,buffer[counter].counter);	\
}while (0)
	

#define IF(data) if(!(data)){AMARK(ALL_CHECK_LEVEL); } if(data)

#define isError(__x) __IsError(__x,0)

#define __IsError(__x,__ok__)do{\
	uint32_t __return = __x;\
	if (__x != __ok__)ALL_PRINTF("func return error(%d)", __return);\
	}while(0)

#ifdef ALLCHECK_SHOW_TYPE
#define TYPE_UINT8_T	" uint8_t"
#define TYPE_UINT16_T	"uint16_t"
#define TYPE_UINT32_T	"uint32_t"
#define TYPE_UINT64_T	"uint64_t"

#define TYPE_INT8_T		"  int8_t"
#define TYPE_INT16_T	" int16_t"
#define TYPE_INT32_T	" int32_t"
#define TYPE_INT64_T	" int64_t"

#define TYPE_FLOAT_T	"   float"
#define TYPE_DOUBLE_T	"  double"
#define TYPE_BOOL_T		"    bool"
#else
#define TYPE_UINT8_T	""
#define TYPE_UINT16_T	""
#define TYPE_UINT32_T	""
#define TYPE_UINT64_T	""

#define TYPE_INT8_T		""
#define TYPE_INT16_T	""
#define TYPE_INT32_T	""
#define TYPE_INT64_T	""

#define TYPE_FLOAT_T	""
#define TYPE_DOUBLE_T	""
#define TYPE_BOOL_T		""
#endif
#define aShow(_var_) _Generic((_var_), \
/*signed char*/                 signed char : ALL_PRINTF("%s %s=%d\n",TYPE_INT8_T,#_var_, _var_), \
/*signed short*/                signed short : ALL_PRINTF("%s %s=%hd\n",TYPE_INT16_T,#_var_, _var_), \
/*signed int*/                  signed int : ALL_PRINTF("%s %s=%d\n",TYPE_INT32_T,#_var_, _var_), \
/*signed long int */            signed long int : ALL_PRINTF("%s %s=%ld\n",TYPE_INT32_T,#_var_, _var_), \
/*signed long int */            signed long long int : ALL_PRINTF("%s %s=%lld\n",TYPE_INT64_T,#_var_, _var_), \
/*unsigned char*/               unsigned char : ALL_PRINTF("%s %s=%c\n",TYPE_UINT8_T,#_var_, _var_), \
/*unsigned short*/              unsigned short : ALL_PRINTF("%s %s=%hu\n",TYPE_UINT16_T,#_var_, _var_), \
/*unsigned int*/                unsigned int : ALL_PRINTF("%s %s=%u\n",TYPE_UINT32_T,#_var_, _var_), \
/*signed long int */            unsigned long long int : ALL_PRINTF("%s v%lld\n",TYPE_UINT64_T,#_var_, _var_), \
/*float*/                       float : ALL_PRINTF("%s %s=%f\n",TYPE_FLOAT_T,#_var_, _var_), \
/*double*/                      double : ALL_PRINTF("%s %s=%lf\n",TYPE_DOUBLE_T,#_var_, _var_), \
/*_Bool*/                       _Bool : ALL_PRINTF("%s %s=%d\n",TYPE_BOOL_T,#_var_, _var_),  \
/*default*/                     default : ALL_PRINTF("type default! show with pointer %s=0x%x\n",#_var_,_var_) \
)
	void all_check_show_check(void);
/**

*/
#define stepDo(step,_DO) do{static time=0;if(time++%step==0){_DO;}}while(0)


#ifdef __cplusplus
}
#endif
#endif // !ALL_CHECK_H
