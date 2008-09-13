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
    local state = PF.CStateQuickPlay_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_Menu_Load()
    local state = PF.CStateLoadGame_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_Menu_Config()
    local state = PF.CStateConfig_getInstance()
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
    PF.CStateMonitor_getInstance():getSimulationManager():startMatch()
end

function cmd_Monitor_ToggleZoom()
    PF.CStateMonitor_getInstance():toogleSimulationView()
end

function cmd_Monitor_SwitchTo2DView()
    PF.CStateMonitor_getInstance():switchTo2DView()
end

function cmd_Monitor_SwitchTo3DView()
    PF.CStateMonitor_getInstance():switchTo3DView()
end

function cmd_Monitor_changeTo442()
    PF.CStateMonitor_getInstance():getSimulationManager():changeFormationEvent(1)
end

function cmd_Monitor_changeTo433()
    PF.CStateMonitor_getInstance():getSimulationManager():changeFormationEvent(0)
end


--------------------------
-- CStateConfig functions
--------------------------
-- cmd_back

function cmd_Config_Save()
    local state = PF.CStateConfig_getInstance()
    state:saveConfig()
end


--------------------------
-- CStateLoadGame functions
--------------------------
-- cmd_back

function cmd_LoadGame_New()
    PF.CStateLoadGame_getInstance():newGame()
end

function cmd_LoadGame_Load()
    PF.CStateLoadGame_getInstance():loadGame()
end

function cmd_LoadGame_Delete()
    PF.CStateLoadGame_getInstance():deleteGame()
end

--------------------------
-- CStateSelectTeam functions
--------------------------
-- cmd_back

function cmd_SelectTeam_Select()
    PF.CStateSelectTeam_getInstance():selectTeam()
end


--------------------------
-- CStateGame functions
--------------------------
-- cmd_back

function cmd_Game_Play()
    local state = PF.CStateMonitor_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_Game_Save()
    PF.CStateGame_getInstance():saveGame()
end

function cmd_Game_Ranking()
    local state = PF.CStateRanking_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_Game_TeamPlayers()
    local state = PF.CStateTeamPlayers_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_Game_Results()
    local state = PF.CStateResults_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end


--------------------------
-- CStateTeamPlayer functions
--------------------------
-- cmd_back

function cmd_Change_Players()
    PF.CStateTeamPlayers_getInstance():handleChangePlayers();
end

-- End Script
