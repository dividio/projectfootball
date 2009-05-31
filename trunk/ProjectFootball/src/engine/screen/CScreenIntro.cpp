/*
 * CScreenIntro.cpp
 *
 *  Created on: 15-dic-2008
 *      Author: rothgar
 */

#include "CScreenIntro.h"
#include "../CGameEngine.h"
#include "../utils/CTimer.h"
#include "../../utils/CLog.h"


CScreenIntro::CScreenIntro()
 :CWindowHandler("intro.layout")
{
    LOG_DEBUG("CScreenIntro()");
}

CScreenIntro::~CScreenIntro()
{
    LOG_DEBUG("~CScreenIntro()");
    delete m_timer;
}

void CScreenIntro::enter()
{
    CWindowHandler::enter();

    m_timer->reset();
    m_elapsedTime = 0;
}

void CScreenIntro::init()
{
	CWindowHandler::init();

    m_timer = new CTimer(1);
    m_introTime = 5;
    m_elapsedTime = 0;

    m_mainWindow = static_cast<CEGUI::Window*>(CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"Intro"));
    registerEventConnection(m_mainWindow->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&CScreenIntro::buttonClicked, this)));
}

void CScreenIntro::update()
{
    if(m_timer->nextTick()) {
        m_elapsedTime++;
        if(m_elapsedTime == m_introTime) {
            CGameEngine::getInstance()->getWindowManager()->nextScreen("MainMenu");
        }
    }
}

bool CScreenIntro::buttonClicked(const CEGUI::EventArgs& e)
{
	CGameEngine::getInstance()->getWindowManager()->nextScreen("MainMenu");
}
