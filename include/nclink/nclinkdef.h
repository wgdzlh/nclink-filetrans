/*!
 * @file nclink.h
 * @brief NC-Link设备模型、消息等定义
 * @note
 * @version V1.00
 * @date 2020/03/21
 * @author Wang Xiao
 * @copyright
 */
#ifndef __NCLINK_H__
#define __NCLINK_H__

#include "config.h"
#include "request_output.h"
///模型结点路径分割符
#define NLK_SEP_TYPE            "/"
///number分割符
#define NLK_SEP_NUM             "@"
///路径中的指令/实际标识
///@deprecated
#define NLK_FLG_CMD                "+"
///模型、请求、查询的结点id字段Key
#define NLK_KW_ID               "id"
///模型结点名称字段Key
#define NLK_KW_NAME             "name"
///模型结点描述字段Key
#define NLK_KW_DESCRIPTION      "description"
///查询、设置请求列表字段Key，采样通道采样列表字段Key
#define NLK_KW_IDS              "ids"
///模型结点类型字段Key
#define NLK_KW_TYPE             "type"
///采样通道结点采样周期字段Key
#define NLK_KW_SAMPLE_INTERVAL  "sampleInterval"
///采样周期结点上传周期Key
#define NLK_KW_UPLOAD_INTERVAL  "uploadInterval"
///模型设备字段Key
#define NLK_KW_DEVICES          "devices"
///模型结点source字段Key
#define NLK_KW_SOURCE           "source"
///模型结点config字段Key
#define NLK_KW_CONFIGS          "configs"
///模型结点number字段Key
#define NLK_KW_NUMBER           "number"
///模型结点dataItem字段Key
#define NLK_KW_DATA_ITEMS       "dataItems"
///模型结点component字段Key
#define NLK_KW_COMPONENTS       "components"
///模型结点dataType字段Key
#define NLK_KW_DATA_TYPE        "dataType"
///模型结点settable字段Key
#define NLK_KW_SETTABLE         "settable"
///查询、设置、采样项offset字段Key
#define NLK_KW_OFFSET           "offset"
///查询、设置、采样项length字段Key
#define NLK_KW_LENGTH           "length"
///查询、采样项keys字段Key
#define NLK_KW_KEYS             "keys"
///查询、采样项indexes字段Key
#define NLK_KW_INDEXES          "indexes"
///设置key字段Key
#define NLK_KW_KEY              "key"
///设置index字段Key
#define NLK_KW_INDEX            "index"
///查询、设置、采样项params字段Key
#define NLK_KW_PARAMS           "params"
///查询、设置、采样项operation字段Key
#define NLK_KW_OPERATION        "operation"
///查询、设置、模型查询、模型设置响应消息code字段Key
#define NLK_KW_CODE             "code"
///查询、设置、模型查询、模型设置响应消息reason字段Key
#define NLK_KW_REASON           "reason"
///设置响应消息value字段Key
#define NLK_KW_VALUE            "value"
///查询响应消息、设置消息values字段Key
#define NLK_KW_VALUES           "values"
///采样消息data字段Key
#define NLK_KW_DATA             "data"
///模型结点unit字段Key
#define NLK_KW_UNIT             "unit"
///采样消息beginTime字段Key
#define NLK_KW_BEGIN_TIME       "beginTime"
///采样消息beginTime字段Key
#define NLK_KW_VERSION          "version"
///模型设备结点guid字段Key
#define NLK_KW_GUID             "guid"
///设置响应消息result字段Key
#define NLK_KW_RESULT           "result"
///设置响应消息results字段Key
#define NLK_KW_RESULTS          "results"
///模型结点commanded字段Key
///@deprecated
#define NLK_KW_COMMANDED        "commanded"
#define NLK_KW_PROBE            "probe"
#define NLK_CODE_OK             "OK"
#define NLK_CODE_NG             "NG"


///LIST数据类型结点的dataType字段值
#define NLK_DATA_TYPE_LIST        "LIST"
///LIST数据类型结点的HASH字段值
#define NLK_DATA_TYPE_HASH        "HASH"

///查询、采样项中的operation字段值,表示取LIST类型数据长度
#define NLK_OP_GET_LENGTH       "get_length"
///查询、采样项中的operation字段默认值,表示取数据的值
#define NLK_OP_GET_VALUE        "get_value"
///查询、采样项中的operation字段值,表示取HASH类型数据的所有key
#define NLK_OP_GET_KEYS         "get_keys"
///查询、采样项中的operation字段值,表示取类型数据的属性
#define NLK_OP_GET_ATTR         "get_attributes"

///设置消息中的operation字段默认值，表示设置值
#define NLK_OP_SET_VALUE        "set_value"
///设置消息中的operation字段值，表示向LIST或HASH类型数据中添加元素
#define NLK_OP_ADD              "add"
///设置消息中的operation字段值，表示删除LIST或HASH类型数据中的元素
#define NLK_OP_DELETE           "delete"

///失败消息
#define ERR_NG_MESSAGE                    "{\"code\":\"NG\"}"
///查询、设置消息中的reason字段的值，表示权限不足
#define REASON_PERMISSION_DENIED            "Permission Denied"
///查询、设置消息中的reason字段的值，表示参数不匹配
#define REASON_PARAMETER_NOT_MATCH            "Parameter Not Match"
///查询、设置消息中的reason字段的值，表示不支持的操作
#define REASON_UNSUPPORTED_OPERATION        "Unsupported Operation"
///查询、设置消息中的reason字段的值，表示结点不存在
#define REASON_ID_NOT_EXISTS                "Id Not Exists"
///查询、设置消息中的reason字段的值，表示内存不足
#define REASON_NO_MEMORY                    "No Memory"

///模型结点settable字段位掩码
#define ITEM_SETTABLE    (0x0001)
///模型结点commanded字段位掩码
///@deprecated
#define ITEM_COMMANDED    (0x0002)

///查询、设置、采样项operation字段位掩码
#define ITEM_OPERATION    (0x0001)
///查询、设置、采样项index/indexes字段位掩码
#define ITEM_INDEX        (0x0002)
///查询、设置、采样项key/keys字段位掩码
#define ITEM_KEY        (0x0004)
///查询、设置、采样项offset字段位掩码
#define ITEM_OFFSET        (0x0008)
///查询、设置、采样项length字段位掩码
#define ITEM_LENGTH        (0x0010)
///设置项value字段位掩码
#define ITEM_VALUE        (0x0020)

#define HasParams(flags,params) ((flags&params)!=params?-1:0)
#if PARAMS_CHECK_ENABLE
#if STRICT_PARAMS_CHECK_ENABLE
///严格参数检查
#define CheckParams(flags, reqFlags) ((flags&(~ITEM_OPERATION))!=(reqFlags)?-1:0)
#else
///宽松参数检查
#define CheckParams(flags,reqFlags) ((((flags)&(reqFlags))!=(reqFlags))?-1:0)
#endif
#else
///无参数检查
#define CheckParams(flags, reqFlags)            (0)
#endif


#if PRIVILEGE_CHECK_ENABLE
///权限检查
#define CheckPrivilegeLevel(level, reqLevel) ((level)<(reqLevel)?-1:0)
#else
///无权限检查
#define CheckPrivilegeLevel(level, reqLevel)    (0)
#endif

typedef enum
{
    RootNodeType, DeviceNodeType, ComponentNodeType, DataItemNodeType, ConfigNodeType, SampleNodeType
} ModelNodeType;

///操作类型枚举
typedef enum
{
    OperationGetValue = (1u << 0u),        ///<取值
    OperationGetAttribute = (1u << 1u),    ///<取属性
    OperationGetLength = (1u << 2u), ///<取长度
    OperationGetKeys = (1u << 3u),   ///<取所有key
    OperationSetValue = (1u << 4u),  ///<设置值
    OperationAdd = (1u << 5u),       ///<添加元素
    OperationDelete = (1u << 6u)     ///删除元素
} OperationType;

//4字节对齐
#pragma pack(push, 4)

///请求对象
typedef struct _Request
{
    char *messageId;        ///<消息id
    int messageIdPos;       ///<消息id位置
} Request;

///查询请求请求项对象
typedef struct _QueryRequestItem
{
    const char *id;       ///<结点id
    int flags;     ///<请求项信息位标识
    OperationType operation;///<操作类型标识
    int offset;             ///<offset参数
    int length;             ///<length参数
    unsigned indexOrKeyNumber;  ///<index/indexes或key/keys字段值得项数
    int indexes[MAX_INDEX_NUMBER * 2];///<存放index/indexes值，每项用两个数字表示，因此乘以2
    const char *keys[MAX_KEY_NUMBER]; ///<存放key/keys值
} QueryRequestItem;

///查询请求对象
typedef struct _QueryRequest
{
    const char *messageId;        ///<消息id
    int messageIdPos;       ///<消息id位置
    unsigned int itemNumber;    ///<请求项数
    QueryRequestItem queryItems[MAX_REQUEST_NUMBER];///请求项
} QueryRequest;

///设置请求请求项
typedef struct _SetRequestItem
{
    const char *id;    ///<结点id
    int flags;     ///<请求项信息位标识
    OperationType operation;///<操作类型标识
    int offset;             ///<offset参数
    int length;             ///<length参数
    unsigned indexOrKeyNumber;  ///<index/indexes或key/keys字段值得项数，值为0或1
    int index;              ///<index字段值
    const char *key;              ///<key字段值
    void *value;            ///<value字段值，JSON对象指针
} SetRequestItem;

///设置请求
typedef struct _SetRequest
{
    const char *messageId;    ///<消息id
    int messageIdPos;   ///<消息id位置
    unsigned int itemNumber;    ///<请求项数
    SetRequestItem setItems[MAX_REQUEST_NUMBER];    ///请求项
} SetRequest;

///模型设置请求
typedef struct _ProbeSetRequest
{
    const char *messageId;    ///<消息id
    int messageIdPos;   ///<消息id位置
    char modelContent[MAX_MODEL_SIZE]; ///<设置的模型文件内容
} ProbeSetRequest;

///查询、设置对应driver层函数的绑定参数，被调用时自动传入
typedef union _BindParams
{
    void *ptrVal;
    int intVal;
    unsigned uintVal;
    long long int64Val;
    unsigned long long uint64Val;
} BindParams;
#ifdef __cplusplus
extern "C" {
#endif
///查询操作driver层入口函数定义
typedef int(*GetExecutor)(QueryRequestItem *request, BindParams *bindParams, RequestOutput output);
///设置操作driver层入口函数定义
typedef int(*SetExecutor)(SetRequestItem *request, BindParams *bindParams, RequestOutput output);
///获取当前请求用户的权限等级
int GetPrivilegeLevel();
///查询、设置操作失败时写入失败原因
void SetErrorReason(const char *err);

///失败返回
#define ErrorReturn(err, ret) do{SetErrorReason(err);return ret;}while(0)

#ifdef __cplusplus
}
#endif

///模型中数据结点绑定的执行体
typedef struct _DataDriver
{
    unsigned int OperationMask;///<允许的操作
    GetExecutor Get;           ///<查询时的driver层入口函数
    int GetPrivilegeLevel;     ///<查询权限等级
    SetExecutor Set;           ///<设置时的driver层入口函数
    int SetPrivilegeLevel;     ///<设置操作的权限等级
    union _BindParams BindParams;   ///<调用Get/Set函数时传入的与结点绑定的绑定参数
} DataDriver;

///基本结点对象
typedef struct _BaseNode
{
    ModelNodeType nodeType; ///<结点类型
    const char *name;             ///<名称字段
    const char *description;      ///<描述字段
    const char *id;               ///<结点id字段
    const char *type;             ///<结点type字段
    const char *path;             ///<结点的路径
} BaseNode;

///数据结点对象
typedef struct _DataNode
{
    ModelNodeType nodeType; ///<结点类型
    const char *name;             ///<名称字段
    const char *description;      ///<描述字段
    const char *id;               ///<结点id字段
    const char *type;             ///<结点type字段
    const char *path;             ///<结点的路径
    const char *number;           ///<结点number字段
    int flags;     ///<结点位标识信息，例如settable，占用其中一位
    DataDriver *driver; ///<结点绑定的执行体
    void *defaultValue;     ///<默认值，直接在模型文件中定义的值
    char reserved[8];       ///<保留字段，用于保持结构体对象大小与SampleNode大小一致，亦可用于后续扩展使用
} DataNode;
///数据项结点对象
typedef DataNode DataItemNode;
///配置项数据结点对象
typedef DataNode ConfigNode;
///采样项对象
typedef struct _SampleItem
{
    const char *id;                    ///<结点id
    int flags;          ///<请求项信息位标识
    OperationType operation;     ///<操作类型标识
    int offset;                  ///<offset参数
    int length;                  ///<length参数
    unsigned indexOrKeyNumber;   ///<index/indexes或key/keys字段值得项数，值为0或1
    int indexes[MAX_INDEX_NUMBER * 2];///<存放index/indexes值，每项用两个数字表示，因此乘以2
    const char *keys[MAX_KEY_NUMBER];  ///<存放key/keys值
    const DataNode *node;              ///<采样项对应的数据结点
} SampleItem;

struct _SampleNode;

///采样驱动对象
typedef struct _SampleDriver
{
    const struct _SampleNode *sampleNode; ///<采样通道结点
    int doSampleInterval;   ///<调度周期，即调用DoSample函数的周期，单位ms
    int getSampleInterval;   ///<调度周期，即调用DoSample函数的周期，单位ms
    long long doSampleTime; ///采样函数调用时间戳记录，内部调度使用
    long long getSampleTime;///取采样数据函数调用时间戳记录，内部调度使用
    void (*SampleDriverInit)(struct _SampleDriver *sampleDriver);   ///采样驱动初始化函数，采样开始前调用，为NULL则不被调用
    void (*SampleDriverDeinit)(struct _SampleDriver *sampleDriver); ///采样驱动资源释放函数，采样结束后时调用，为NULL则不被调用
    int (*DoSample)(struct _SampleDriver *sampleDriver);    ///<采样函数，按scheduleInterval间隔周期调用
    int (*GetSampleData)(struct _SampleDriver* sampleDriver, char *dataBuffer,int dataBufferSize,int* length,long long* timestamp);  ///<取数据函数，按采样通道uploadInterval周期调用
} SampleDriver;

///采样通道对象
typedef struct _SampleNode
{
    ModelNodeType nodeType;     ///<结点类型
    const char *name;                 ///<名称字段
    const char *description;          ///<描述字段
    const char *id;                   ///<结点id字段
    const char *type;                 ///<结点type字段
    const char *path;                 ///<结点的路径
    const char *number;               ///<结点number字段
    int sampleInterval;         ///<采样周期字段
    int uploadInterval;         ///<上传周期字段
    unsigned int sampleItemNumber;  ///<采样项数
    SampleItem *sampleItems;        ///<采样项
    SampleDriver *sampleDriver;     ///<采样通道的采样驱动
} SampleNode;

///组件结点对象
typedef struct _ComponentNode
{
    ModelNodeType nodeType;     ///<结点类型
    const char *name;                 ///<名称字段
    const char *description;          ///<描述字段
    const char *id;                   ///<结点id字段
    const char *type;                 ///<结点type字段
    const char *path;                 ///<结点的路径
    const char *number;               ///<结点number字段
    unsigned int configNumber;  ///<配置项数
    ConfigNode *configs;        ///<配置项
    unsigned int dataItemNumber;///<数据项数
    DataItemNode *dataItems;    ///<数据项
    unsigned int componentNumber;///<组件项数
    struct _ComponentNode *components;///<组件项
} ComponentNode;

///设备结点对象
typedef struct _DeviceNode
{
    ModelNodeType nodeType;     ///<结点类型
    const char *name;                 ///<名称字段
    const char *description;          ///<描述字段
    const char *id;                   ///<结点id字段
    const char *type;                 ///<结点type字段
    const char *path;                 ///<结点的路径
    const char *number;               ///<结点number字段
    unsigned int configNumber;  ///<配置项数
    ConfigNode *configs;        ///<配置项
    unsigned int dataItemNumber;///<数据项数
    DataItemNode *dataItems;    ///<数据项
    unsigned int componentNumber;///<组件项数
    struct _ComponnetNode *components;///<组件项
    const char *version;              ///<版本号字段
    const char *guid;                 ///<设备guid字段
} DeviceNode;

///根结点对象，即模型文件对象
typedef struct _RootNode
{
    ModelNodeType nodeType;     ///<结点类型
    const char *name;                 ///<名称字段
    const char *description;          ///<描述字段
    const char *id;                   ///<结点id字段
    const char *type;                 ///<结点type字段
    const char *path;                 ///<结点的路径
    unsigned int configNumber;  ///<配置项数
    ConfigNode *configs;        ///<配置项
    unsigned int deviceNumber;  ///<配置项数
    DeviceNode *devices;        ///<配置项
    void *state;                ///<原始模型文件Json数据对象
} RootNode;

//关闭4字节对齐
#pragma pack(pop)

#endif