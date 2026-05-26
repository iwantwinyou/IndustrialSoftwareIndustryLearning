库文件名：lpAutoChangeModel.dll
功能说明：RTP自动切工单功能
相关文件：lpIPUServer.json
依赖库：lpqtConfig.dll
             mb002/include
             lpDataMgr.dll


使用示例：
lpIPUServer.json

"extend_funtion":{
	"auto_change_model":{
            		"enable":false,       //默认false为不开启
		"time_interval_sec":5,			//请求plc时间间隔（单位：秒）
		"time_undetected_min":5           //一定时间内未检测(单位：分钟)
		},
                }



版本说明

初版     V1.0.1.0      2024-09-14
1、初版
2、RTP自动切换工单功能


V1.0.1.1      2024-09-23
1、修改 一定时间内未检测时间单位为分钟
2、删除 没有用到的函数 void init ();

V1.0.2.0   2024-11-26
1、删除 readModelJson方法
2、修改 获取模板宽高的方法为modelCtrl::getModelSize 去构建modelSize
3、修复自动切换工单的工单json数据的构建，job_detail字段的数据删除掉 alg_param,修复工单算法alg字段的数据错误问题
4、增加析构函数 释放定时器资源
5、删除没用的成员变量m_map

V1.0.2.1   2024-12-11
1、把切换成功或失败提示语 中文改为英文

V1.0.3.0   2025-2-25
1、删除machine_id=9判断，因为片料跟RTP共用一套切换代码
2、支持昆山恒美扫码功能，通过扫码发送信息给第三方app，进行切换工单需求
tapd:【昆山恒美AOI软件对接厂内扫码软件】
https://www.tapd.cn/42589486/prong/stories/view/1142589486001027240

V1.0.4.0   2025-06-09
1、PLC 自动切型  去除防呆，原来只支持1-999的型号，现在需要支持其他字符串的型号


V1.0.5.0   2025-11-24
1、切换模板执行函数onAutoChangeModel(const QString &modelName,const QString &jobName,jobSwitchingType jobType)添加枚举用来走不同的业务逻辑，
如果是PLC切换则走PLC切换的逻辑，如果是第三方APP切换则走第三方切换的逻辑，原来是仅仅通过job_name是否为空来判断是PLC切换还是第三方app切换，不利于后续拓展，
添加了枚举，后续如果有其他切换业务，可以直接添加，而不需要大范围去修改onAutoChangeModel函数，同时修改该函数的流程，减少代码冗余
2、去除了一些多余代码，比如声明了没有使用等

V1.0.6.0   2025-12-22
1、适配新版换模板跟工单(结合sinspect换模板)

V1.0.7.0   2026-05-14
1、PLC切型失败，软件给PLC发送报警信号

