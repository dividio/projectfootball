
---------------------------------------------------

STm_Global = {}

STm_Global["Enter"] = function(team)

end

STm_Global["Execute"] = function(team)

end

STm_Global["Exit"] = function(team)

end

STm_Global["OnMessage"] = function(team, message)
    local handle = false
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    if message.Msg == PF.Msg_KickOff then
        team:getFSM():changeState("STm_Kick")
        handle = true
    elseif message.Msg == PF.Msg_BeforeStart then
        team:getFSM():changeState("STm_BeforeStart")
        handle = true
    elseif message.Msg == PF.Msg_HalfTime then
        team:getFSM():changeState("STm_HalfTime")
        handle = true
    elseif message.Msg == PF.Msg_EndMatch then
        team:getFSM():changeState("STm_EndMatch")
        handle = true
    elseif message.Msg == PF.Msg_PlayOn then
        team:getFSM():changeState("STm_PlayOn")
        handle = true
    end
    return handle
end

---------------------------------------------------

STm_BeforeStart = {}

STm_BeforeStart["Enter"] = function(team)
    team:getCurrentFormation():changeToInitialPosition()
    local playersVector = team:getPlayers()
    local disp = PF.CMessageDispatcher_getInstance()
    local size = playersVector:size()
    for i = 0, size - 1, 1 do
        disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_GoHome, nil)
    end
end

STm_BeforeStart["Execute"] = function(team)

end

STm_BeforeStart["Exit"] = function(team)

end

STm_BeforeStart["OnMessage"] = function(team, message)
    return false
end

---------------------------------------------------

STm_HalfTime = {}

STm_HalfTime["Enter"] = function(team)
    team:getCurrentFormation():changeToInitialPosition()
    local playersVector = team:getPlayers()
    local disp = PF.CMessageDispatcher_getInstance()
    local size = playersVector:size()
    for i = 0, size - 1, 1 do
        disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_GoHome, nil)
    end
    team:changeSide()
end

STm_HalfTime["Execute"] = function(team)

end

STm_HalfTime["Exit"] = function(team)

end

STm_HalfTime["OnMessage"] = function(team, message)
    return false
end

---------------------------------------------------

STm_EndMatch = {}

STm_EndMatch["Enter"] = function(team)
    local playersVector = team:getPlayers()
    local disp = PF.CMessageDispatcher_getInstance()
    local size = playersVector:size()
    for i = 0, size - 1, 1 do
        disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_GoHome, nil)
    end
end

STm_EndMatch["Execute"] = function(team)

end

STm_EndMatch["Exit"] = function(team)

end

STm_EndMatch["OnMessage"] = function(team, message)
    return false
end

---------------------------------------------------

STm_Kick = {}

STm_Kick["Enter"] = function(team)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local formation = team:getCurrentFormation()
    if sim:getReferee():getGameMode() == PF.KICK_OFF then
        formation:changeToInitialPosition()
    elseif team:isKickForUs() then
        formation:changeToOffensive()
    else
        formation:changeToDefensive()
    end
    local playersVector = team:getPlayers()
    local disp = PF.CMessageDispatcher_getInstance()
    local size = playersVector:size()
    for i = 0, size - 1, 1 do
        disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_Interrupt, nil)
    end
    if team:isKickForUs() then
        local playerId = team:getKickPlayerID()
        disp:dispatchMsg(0, team:getID(), playerId, PF.Msg_KickIn, nil)
    end
end

STm_Kick["Execute"] = function(team)

end

STm_Kick["Exit"] = function(team)

end

STm_Kick["OnMessage"] = function(team, message)
    return false
end

---------------------------------------------------

STm_PlayOn = {}

STm_PlayOn["Enter"] = function(team)
    local playersVector = team:getPlayers()
    local disp = PF.CMessageDispatcher_getInstance()
    local size = playersVector:size()
    for i = 0, size - 1, 1 do
        disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_PlayOn, nil)
    end
end

STm_PlayOn["Execute"] = function(team)

end

STm_PlayOn["Exit"] = function(team)

end

STm_PlayOn["OnMessage"] = function(team, message)
    return false
end

---------------------------------------------------