//
//  NetManager.h
//  cocos2dx
//
//  Created by Cocos2d on 12-8-9.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "NetManager.h"
#include "BasicFunction.h"
#include "CCMessageQueue.h"

USING_NS_CC_NETWORK;
using namespace std;

NetManager* NetManager::m_pInstance = NULL;
NetManager::Release NetManager::Garbo;

bool NetManager::init(void)
{
//	m_mapError[-1] = "通讯错误或者返回的json数据内容错误";

    m_strToken = "3";
    m_strUrl = "http://localhost:22222/game/";
    m_nIndex = 1;
	return true;
}
//test function
bool NetManager::setToken(std::string strToken)
{
    m_strToken = strToken;
}

bool NetManager::send(ModeRequestType modEnum, DoRequestType doEnum, cocos2d::SEL_CallFuncND selector, cocos2d::CCObject *rec, const char* requestData)
{
    CCNetwork::sharedNetwork()->sendNetPackage(GenerateUrl(modEnum, doEnum), 1, GeneratePost(modEnum, doEnum, requestData).c_str(), selector, rec);
    
    return true;
}

bool NetManager::sendEx(ModeRequestType modEnum, DoRequestType doEnum, cocos2d::SEL_CallFuncND selector, cocos2d::CCObject *rec, const char* format,...)
{
	va_list   vlist;
	va_start(vlist,format); 
	char temp[1024]="";
	char* param = NULL;
	vsnprintf(temp,1024,format,vlist);
	va_end(vlist);
	if(strlen(temp) > 0)
		param = temp;
    
	return send(modEnum, doEnum, selector, rec, param);
}

string NetManager::GeneratePost(ModeRequestType modEnum, DoRequestType doEnum,const char* requestData)
{
	char temp[10240];
	if (requestData == NULL || strlen(requestData) == 0)
	{
		sprintf(temp, "{\"header\":{\"token\": \"%s\", \"index\": %d}, \"meta\":{\"mod\": \"%s\", \"do\": \"%s\", \"ver\":%d, \"in\":{}}}", m_strToken.c_str(), m_nIndex++, g_modNames[modEnum].c_str(), g_doNames[doEnum].c_str(), g_doVersion[doEnum]);
	} 
	else
	{
		sprintf(temp, "{\"header\":{\"token\": \"%s\", \"index\": %d}, \"meta\":{\"mod\": \"%s\", \"do\": \"%s\", \"ver\":%d,  \"in\":{%s}}}", m_strToken.c_str(), m_nIndex++, g_modNames[modEnum].c_str(), g_doNames[doEnum].c_str(), g_doVersion[doEnum], requestData);
	}
        
	return string(temp);
}

string NetManager::GenerateUrl(ModeRequestType modEnum, DoRequestType doEnum)
{
    return m_strUrl + g_modNames[modEnum] + "/" + g_doNames[doEnum] + "/";
}

string NetManager::GetErrorInfo(int errorCode)
{
	map<int, string>::iterator tempIter;
	tempIter = m_mapError.find(errorCode);
	if (tempIter != m_mapError.end())
	{
		return (*tempIter).second;
	}
	
	return "无效的错误代码：" + ConvertToString(errorCode);
}

const char* NetManager::processResponse(void *data)
{
    CCAssert(data != NULL, "");
    RequestInfo *info = (RequestInfo *)data;

    //通用返回数据处理，比如错误信息（timeout，业务失败）
    
    //返回数据到业务模块
    return info->strResponseData.c_str();
}

