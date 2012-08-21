//
//  Cover.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "CoverScene.h"
#include "ChapterScene.h"
#include "LevelDataManager.h"
#include "LuckySprite.h"
#include "NetManager.h"
#include "PageScene.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

#define TAG_BUTTON_BOOK 1

USING_NS_CC;
USING_NS_CC_EXT;

Cover *Cover::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("Cover", CoverLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/cover.ccbi", pOwner);
    
    Cover *pCover = static_cast<Cover *>(pNode);
    return pCover;
}

cocos2d::SEL_MenuHandler Cover::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", Cover::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler Cover::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", Cover::onCCControlButtonClicked );
    return NULL;
}
bool Cover::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    return false;
}

void Cover::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pTarget);
    printf("tag %d\n",p->getTag());
}

void Cover::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pSender);
    printf("tag %d\n",p->getTag());
    
    unsigned int tag = p->getTag();
    
    if ( tag == TAG_BUTTON_BOOK )
    {
        this->menuBookCallback(NULL);
    }
}

CCScene* Cover::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        Cover *layer = Cover::create(scene);
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

// on "init" you need to initialize your instance
bool Cover::init()
{
    CCTouchPageTurn::init();

    CCSprite* pSprite = CCSprite::create("pub/image/fullscreen/fuzzy.png");
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    pSprite->setPosition(ccp(winsize.width/2, winsize.height/2));
    this->addChild(pSprite, -1);
    return true;
}

void Cover::menuDaggerCallback(CCObject* pSender)
{
}

void Cover::menuMagicCallback(CCObject* pSender)
{
}

void Cover::menuBookCallback(CCObject* pSender)
{
    CCScene *pScene = Chapter::scene();
    
    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
    
    CCDirector::sharedDirector()->pushScene(pTp);
}

void Cover::menuCardCallback(CCObject* pSender)
{
}

void Cover::menuOptionCallback(CCObject* pSender)
{
    LevelDataManager::shareLevelDataManager()->reload();
}

void Cover::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

