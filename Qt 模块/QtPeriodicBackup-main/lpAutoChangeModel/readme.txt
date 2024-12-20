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

V1.0.3.0   2024-12-06
1、删除machine_id=9判断，因为片料跟RTP共用一套切换代码

