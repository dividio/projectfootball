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
 :CScreen("intro.layout")
{
    LOG_DEBUG("CScreenIntro()");
    m_timer = new CTimer(1);
    m_introTime = 5;
    m_elapsedTime = 0;

    m_mainWindow   = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Intro"));

    m_mainWindow->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&CScreenIntro::buttonClicked, this));
}

CScreenIntro::~CScreenIntro()
{
    LOG_DEBUG("~CScreenIntro()");
    delete m_timer;
}

void CScreenIntro::enter()
{
    CScreen::enter();

    m_timer->reset();
    m_elapsedTime = 0;
}

void CScreenIntro::update()
{
    if(m_timer->nextTick()) {
        m_elapsedTime++;
        if(m_elapsedTime == m_introTime) {
            CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getMainMenuScreen());
        }
    }
}

bool CScreenIntro::buttonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getMainMenuScreen());
}
