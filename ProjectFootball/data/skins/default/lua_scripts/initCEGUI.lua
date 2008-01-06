-- CEGUI initialization script

-- Functions definition

function cmd_back()
    PF.CStateManager_getInstance():popState()
end


---------------------------
-- CStateMainMenu functions
---------------------------

function cmd_quit()
    PF.CStateManager_getInstance():popStack()
end

function cmd_credits()
    local state = PF.CStateCredits_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_play()
    local state = PF.CStateMonitor_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end


--------------------------
-- CStateCredits functions
--------------------------

-- cmd_back


--------------------------
-- CStateMonitor functions
--------------------------

-- cmd_back

function cmd_startSimulation()

end

function cmd_switchTo2DView()
    PF.CStateMonitor_getInstance():switchTo2DView()
end

function cmd_switchTo3DView()
    PF.CStateMonitor_getInstance():switchTo3DView()
end

-- End Script