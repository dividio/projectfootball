-- CEGUI initialization script

---------------------------
-- Functions definition
---------------------------
function cmd_back()
    PF.CScreenManager_getInstance():popState()
end



---------------------------
-- CScreenMainMenu functions
---------------------------
function cmd_Menu_QuickPlay()
    local state = PF.CScreenQuickPlay_getInstance()
    PF.CScreenManager_getInstance():pushState(state)
end

function cmd_Menu_Load()
    local state = PF.CScreenLoadGame_getInstance()
    PF.CScreenManager_getInstance():pushState(state)
end

function cmd_Menu_Config()
    local state = PF.CScreenConfig_getInstance()
    PF.CScreenManager_getInstance():pushState(state)
end

function cmd_Menu_Credits()
    local state = PF.CScreenCredits_getInstance()
    PF.CScreenManager_getInstance():pushState(state)
end

function cmd_Menu_Quit()
    PF.CScreenManager_getInstance():popStack()
end



--------------------------
-- CScreenCredits functions
--------------------------
-- cmd_back


--------------------------
-- CScreenSimulator functions
--------------------------
-- cmd_back

function cmd_Simulator_StartSimulation()
    PF.CScreenSimulator_getInstance():getSimulationManager():startMatch()
end

function cmd_Simulator_ToggleZoom()
    PF.CScreenSimulator_getInstance():toogleSimulationView()
end

function cmd_Simulator_SwitchTo2DView()
    PF.CScreenSimulator_getInstance():switchTo2DView()
end

function cmd_Simulator_SwitchTo3DView()
    PF.CScreenSimulator_getInstance():switchTo3DView()
end

function cmd_Simulator_changeTo442()
    PF.CScreenSimulator_getInstance():getSimulationManager():changeFormationEvent(1)
end

function cmd_Simulator_changeTo433()
    PF.CScreenSimulator_getInstance():getSimulationManager():changeFormationEvent(0)
end

function cmd_Simulator_Continue()
    local state = PF.CScreenMatchResult_getInstance()
    PF.CScreenManager_getInstance():popState()
    PF.CScreenManager_getInstance():pushState(state)
end

--------------------------
-- CScreenConfig functions
--------------------------
-- cmd_back

function cmd_Config_Save()
    local state = PF.CScreenConfig_getInstance()
    state:saveConfig()
end


--------------------------
-- CScreenLoadGame functions
--------------------------
-- cmd_back

function cmd_LoadGame_New()
    PF.CScreenLoadGame_getInstance():newGame()
end

function cmd_LoadGame_Load()
    PF.CScreenLoadGame_getInstance():loadGame()
end

function cmd_LoadGame_Delete()
    PF.CScreenLoadGame_getInstance():deleteGame()
end

--------------------------
-- CScreenSelectTeam functions
--------------------------
-- cmd_back

function cmd_SelectTeam_Select()
    PF.CScreenSelectTeam_getInstance():selectTeam()
end


--------------------------
-- CScreenGame functions
--------------------------
-- cmd_back

function cmd_Game_Play()
    PF.CScreenGame_getInstance():playButtonEvent()
end

function cmd_Game_Save()
    PF.CScreenGame_getInstance():saveGame()
end

function cmd_Game_Ranking()
    local state = PF.CScreenRanking_getInstance()
    PF.CScreenManager_getInstance():pushState(state)
end

function cmd_Game_TeamPlayers()
    local state = PF.CScreenTeamPlayers_getInstance()
    PF.CScreenManager_getInstance():pushState(state)
end

function cmd_Game_Results()
    local state = PF.CScreenResults_getInstance()
    PF.CScreenManager_getInstance():pushState(state)
end

function cmd_Game_ResultMode()
    PF.CScreenGame_getInstance():resultModeEvent()
end


--------------------------
-- CScreenTeamPlayer functions
--------------------------
-- cmd_back

function cmd_Change_Players()
    PF.CScreenTeamPlayers_getInstance():handleChangePlayers();
end


--------------------------
-- CScreenMatchResult functions
--------------------------
-- cmd_back


-- End Script
