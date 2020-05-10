
#define WH_KEY_NUM        2

enum
{
	WH_KEY_SET = 0,
	WH_KEY_POW,

	WH_KEY_BUTT
};


/* 输入是业务级的，定义一套输入类/方法 */

typedef enum tagWindHeatKeyState
{
	WH_KEY_NONE = 0,
	WH_KEY_SHORT,
	WH_KEY_LONG,

	WH_KEY_BUTT
}WH_KEY_STATE_E;


typedef struct tagWindHeatKeyClass
{
	U8 u8KeyId;
	WH_KEY_STATE_E eState;

	/* 类方法 */
	//Init，exit，
	
	VOID *pPrivate;
}WH_KEY_CLASS_S;

