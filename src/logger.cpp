#include "Logger.h"
#include <iostream>
#include <sys/file.h>
#include <string.h>
#include "defines.h"

extern Config g_config;

Logger::Logger()
{
    //初始化
    m_pFileStream = NULL;
    char temp[1024] = {0};
    strcat(temp, m_logPath);
    strcat(temp, m_logName);
    m_pFileStream = fopen(temp, "a+");
    another="ts_count.xls";
    if (!m_pFileStream)
    {
        std::cerr << "Can't open log file." << std::endl;
        return;
    }
}

Logger::~Logger()
{
    //关闭文件流
    if (m_pFileStream)
        fclose(m_pFileStream);
}

//获取系统当前时间
std::string Logger::getCurrentTime(int type = 0)
{
    time_t curTime;
    struct tm *pTimeInfo = NULL;
    time(&curTime);
    pTimeInfo = localtime(&curTime);
    char temp[MAX_STR_LEN] = {0};
    if (type == 0)
        sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d", pTimeInfo->tm_year + 1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday, pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
    else
        sprintf(temp, "%02d:%02d:%02d", pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
    std::string pTemp = temp;
    return pTemp;
}

// 设置devid
void Logger::setDevid(const std::string &devId)
{
    this->m_devId = devId;
}

//写文件操作
void Logger::log(const std::string &strInfo, int type)
{
    if (!strInfo.length())
        return;

    if (type == 2)
    {
        try
        {
            //若文件流没有打开，则重新打开
            if (!Fileanother)
            {
                char temp[1024] = {0};
                strcat(temp, another.c_str());

                Fileanother = fopen(temp, "a+");

                if (!Fileanother)
                {
                    std::cerr << "Can't open log file." << std::endl;
                    return;
                }
            }
            int m_fd = fileno(Fileanother);
            //进入临界区，文件上锁
            flock(m_fd, LOCK_EX);
            //写日志信息到文件流
            fprintf(Fileanother, "%s\t%s\t%s\n", getCurrentTime().c_str(), m_devId.c_str(), strInfo.c_str());
            fflush(Fileanother);
            //离开临界区
            flock(m_fd, LOCK_UN);
        }
        //若发生异常，则先离开临界区，防止死锁
        catch (...)
        {
            int m_fd = fileno(Fileanother);
            flock(m_fd, LOCK_UN);
        }
        return;
    }

    if (g_config.showDbg | type)
    {
        std::cout << getCurrentTime().c_str() << " [" << m_devId.c_str() << "] " << strInfo << std::endl;
    }

    try
    {
        //若文件流没有打开，则重新打开
        if (!m_pFileStream)
        {
            char temp[1024] = {0};
            strcat(temp, m_logPath);
            strcat(temp, m_logName);

            if (g_config.delLog == 1)
                m_pFileStream = fopen(temp, "w");
            else
                m_pFileStream = fopen(temp, "a+");

            if (!m_pFileStream)
            {
                std::cerr << "Can't open log file." << std::endl;
                return;
            }
        }
        int m_fd = fileno(m_pFileStream);
        //进入临界区，文件上锁
        flock(m_fd, LOCK_EX);
        //写日志信息到文件流
        fprintf(m_pFileStream, "%s [%s] %s\n", getCurrentTime().c_str(), m_devId.c_str(), strInfo.c_str());
        fflush(m_pFileStream);
        //离开临界区
        flock(m_fd, LOCK_UN);
    }
    //若发生异常，则先离开临界区，防止死锁
    catch (...)
    {
        int m_fd = fileno(m_pFileStream);
        flock(m_fd, LOCK_UN);
    }
}