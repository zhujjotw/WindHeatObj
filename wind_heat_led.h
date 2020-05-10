

typedef enum tagWindHeatLedColor
{
	WH_COLOR_NONE = 0,
	WH_COLOR_GREN,
	WH_COLOR_RED,

	WH_COLOR_BUTT
}WH_LED_COLOR_E;

typedef struct tagWindHeatKeyClass
{
	U8 u8LedId;
	WH_LED_COLOR_E eColor;

	/* 基本方法类 */
	//Init，exit，start, stop
	VOID *pPrivate;
}WH_KEY_CLASS_S;

