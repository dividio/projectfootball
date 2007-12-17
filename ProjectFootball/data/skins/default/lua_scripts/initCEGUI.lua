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
    state = PF.CStateCredits_getInstance()
    PF.CStateManager_getInstance():pushState(state)
end

function cmd_play()
    state = PF.CStateMonitor_getInstance()
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


-- End Script