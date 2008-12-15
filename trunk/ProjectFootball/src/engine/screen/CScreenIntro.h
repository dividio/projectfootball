/*
 * CScreenIntro.h
 *
 *  Created on: 15-dic-2008
 *      Author: rothgar
 */

#ifndef CSCREENINTRO_H_
#define CSCREENINTRO_H_

#include "../CScreen.h"

class CTimer;

class CScreenIntro: public CScreen {
public:
    CScreenIntro();
    virtual ~CScreenIntro();

    virtual void enter();
    virtual void update();

private:
    bool buttonClicked(const CEGUI::EventArgs& e);

    CTimer        *m_timer;
    int            m_introTime;
    int            m_elapsedTime;
    CEGUI::Window *m_mainWindow;
};

#endif /* CSCREENINTRO_H_ */
