//
//  LevelDataManager.h
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#if !defined _LevelDataManager_H__
#define _LevelDataManager_H__

#include "Basic.h"
#include "json/json.h"

class LevelDataManager
{
public:
	static LevelDataManager* shareLevelDataManager(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new LevelDataManager();
			m_pInstance->init();
		}
		return m_pInstance;

	}

    stPage *getNewPage(int chapterId);
    
    bool isChapterEnd(int chapterId);
    
    stBible m_stBible;
    
    template <class T> 
	static std::string ConvertToString(T value) {
		std::stringstream ss;
		ss << value;
		return ss.str();
        
	}
protected:
	void init(void);
	LevelDataManager(void);
	virtual ~LevelDataManager(void);

	static LevelDataManager *m_pInstance;

	class XLRelease
	{
	public:
		~XLRelease()
		{
			if(LevelDataManager::m_pInstance)
			{
				delete LevelDataManager::m_pInstance;
				LevelDataManager::m_pInstance = NULL;
			}
		}
	};
	static XLRelease Garbo;
    
};

#endif