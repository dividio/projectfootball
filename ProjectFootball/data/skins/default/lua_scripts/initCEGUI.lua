-- CEGUI initialization script

---------------------------
-- Functions definition
---------------------------
function cmd_back()
    PF.CStateManager_getInstance():popState()
end



---------------------------
-- CStateMainMenu functions
---------------------------
function cmd_Menu_QuickPlay()
    local state = PF.CStateMonitor_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_Menu_Load()
    local state = PF.CStateLoadGame_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_Menu_Credits()
    local state = PF.CStateCredits_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_Menu_Quit()
    PF.CStateManager_getInstance():popStack()
end



--------------------------
-- CStateCredits functions
--------------------------
-- cmd_back


--------------------------
-- CStateMonitor functions
--------------------------
-- cmd_back

function cmd_Monitor_StartSimulation()

end

function cmd_Monitor_SwitchTo2DView()
    PF.CStateMonitor_getInstance():switchTo2DView()
end

function cmd_Monitor_SwitchTo3DView()
    PF.CStateMonitor_getInstance():switchTo3DView()
end



--------------------------
-- CStateLoadGame functions
--------------------------
-- cmd_back

function cmd_LoadGame_New()
    local state = PF.CStateLoadGame_getInstance()
    state:createNewGame()
end

function cmd_LoadGame_Load()
    local state = PF.CStateLoadGame_getInstance()
    state:loadGame()
end


--------------------------
-- CStateGame functions
--------------------------
-- cmd_back

function cmd_Game_Play()
    local state = PF.CStateMonitor_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

-- End Script