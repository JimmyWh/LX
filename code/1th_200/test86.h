
#define NAME_LENGTH 30     /* 允许出现的最长名字 */
#define ADDR_LENGTH 100    /* 允许出现的最长地址 */
#define PHONE_LENGTH 11    /* 允许出现的最长电话号码 */
#define MAX_ADDRESSES 1000 /* 允许出现的最多地址个数 */

/*
** 接口函数
** 给出一个名字，查找对应的地址
*/

char const *lookup_address(char const *name);


/*
** 给出一个名字，查找对应的电话号码
*/

char const *lookup_phone(char const *name);



