/*
 * =====================================================================================
 *
 *       Filename:  PlayerInfoView.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/7/30 17:13:50
 *       Revision:  none
 *
 *         Author:  lihex (lhx), hexuan.li@cocos2d-x.org
 *
 *    Copyright (c) 2012 厦门雅基软件有限公司. All rights reserved.
 *
 * =====================================================================================
 */

#include "Basic.h"
#include "PlayerInfoView.h"
#include "BasicInfoView.h"
#include "EquipInfoView.h"
#include "LuckySprite.h"
#include "FuzzyBgView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;


PlayerInfoView::PlayerInfoView(){

}
PlayerInfoView::~PlayerInfoView(){

}

PlayerInfoView * PlayerInfoView::create(cocos2d::CCObject * pOwner){
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("PlayerInfoView", PlayerInfoViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("EquipInfoView", EquipInfoViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("BasicInfoView", BasicInfoViewLoader::loader());
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/playerinfo.ccbi", pOwner);
    
    PlayerInfoView *pPlayerInfoView = static_cast<PlayerInfoView *>(pNode);
    pPlayerInfoView->m_pBasicInfoView = (BasicInfoView*)pPlayerInfoView->getChildByTag(kPlayerInfoTagBasicLayer);
    pPlayerInfoView->m_pEquipInfoView = (EquipInfoView*)pPlayerInfoView->getChildByTag(kPlayerInfoTagEquipLayer);
    pPlayerInfoView->m_iType = kPlayerInfoTagPlayerBtn;
    pPlayerInfoView->showViewForType();
    return pPlayerInfoView;
}

cocos2d::SEL_MenuHandler PlayerInfoView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", PlayerInfoView::onMenuItemClicked);
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PlayerInfoView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "PlayerInfoBarBtnCallback", PlayerInfoView::PlayerInfoBarBtnCallback);
    return NULL;
}


bool PlayerInfoView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode){
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLaberTitle", cocos2d::CCLabelTTF * , this->mLaberTitle);
    return false;
}



void PlayerInfoView::onMenuItemClicked(cocos2d::CCObject *pTarget){
    
}


void PlayerInfoView::PlayerInfoBarBtnCallback(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    CCNode* btn = (CCNode*)pSender;
    //cout << btn->getTag() << endl;
    switch (btn->getTag()) {
        case kPlayerInfoTagPlayerBtn:
            m_iType = kPlayerInfoTagPlayerBtn;
            showViewForType();
            break;
        case kPlayerInfoTagHeadBtn:
            m_iType = kPlayerInfoTagHeadBtn;
            showViewForType();
            break;
        case kPlayerInfoTagArmsBtn:
            m_iType = kPlayerInfoTagArmsBtn;
            showViewForType();
            break;
        case kPlayerInfoTagClothseBtn:
            m_iType = kPlayerInfoTagClothseBtn;
            showViewForType();
            break;
        case kPlayerInfoTagShoesBtn:
            m_iType = kPlayerInfoTagShoesBtn;
            showViewForType();
            break;
        default:
            break;
    }
}

void PlayerInfoView::showViewForType(){
    if(m_iType < 0){
        CCLog("cur type is null");
        return;
    }
    
    if(m_iType > kPlayerInfoTagPlayerBtn ){
        m_pBasicInfoView->hideBasicView();
        m_pEquipInfoView->showEquipView();
    }else{
        m_pBasicInfoView->showBasicView();
        m_pEquipInfoView->hideEquipView();
    }
}




