/**
 * 
 * 字符类、块设备类、网络类，目前只实现字符设备
 * 
 */

typedef enum tagDevClass
{
    DEV_CLASS_CHAR = 0,
    DEV_CLASS_BLK,
    DEV_CLASS_NETWORK,

    DEV_CLASS_BUTT

}DEV_CLASS_E;


typedef struct tagDevMethod
{
    int (*_write)(int, char, int) ;
    int (*_read)(int, char, int) ;
    int (*_ioctl)(int, char, void) ;
}DEV_CLASS_METHOD;


typedef struct tagDevClass
{
    DEV_CLASS_E eDevType;

    DEV_CLASS_METHOD stMethod;
}DEV_CLASS;

typedef struct tagDevClassTable
{
    DEV_CLASS *pstClass;
}DEV_CLASS_TAB;



