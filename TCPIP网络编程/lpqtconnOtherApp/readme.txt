库文件名：lpconnOtherApp
功能说明：与第三方软件通信模块
1、实现和第三方app之间的数据发送、接收等操作
相关文件：lpIPUServer.json
依赖库：lpqtConfig.dll
 
 新增文件 lpOtherAppConfig.json


使用示例：
lpOtherAppConfig.json
{
    "config":{
        "tcp_server_ip": "8.135.10.183 ", //ip地址
        "tcp_server_port": 32375, //端口号  跟第三方app保持一致  
        "b_print": true   //是否打印日志
    }
}

lpIPUServer.json
"extend_funtion":{
        "auto_change_model":{
            "enable":false,       //默认不开启
        }
    }

版本说明

初版     V1.0.1.0      2024-09-23
1、初版
2、发送工单号跟配方号（模板）到新建工单模块