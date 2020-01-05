#ifndef LOGGER
#define LOGGER
#include <stdio.h>
#include <string>
static const int MAX_STR_LEN = 1024;

class Logger
{
private:
    // 写日志文件流
    FILE * m_pFileStream;
     FILE * Fileanother;
	// 日志的路径
	const char* m_logPath = "./";
	// 日志的名称
	const char* m_logName = "ts.log";
    // 设备ID
    std::string m_devId;

    std::string another;
public:
    Logger();
    ~Logger();
    void setDevid(const std::string & devId);
    std::string getCurrentTime(int);
    // 日志记录函数
    void log(const std::string & strInfo, int type = 0);
};

#endif