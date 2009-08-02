
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
    team:getCurrentFormation():setCurrentFormationType(PF.FT_Initial)
    local playersVector = team:getPlayers()
    local disp = PF.CMessageDispatcher_getInstance()
    local size = playersVector:size()
    local id = team:getID()
    for i = 0, size - 1, 1 do
        disp:dispatchMsg(0, id, playersVector[i]:getID(), PF.Msg_GoHome, nil)
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
    team:getCurrentFormation():setCurrentFormationType(PF.FT_Initial)
    team:changeSide()
    local playersVector = team:getPlayers()
    local disp = PF.CMessageDispatcher_getInstance()
    local size = playersVector:size()
    for i = 0, size - 1, 1 do
        disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_GoHome, nil)
    end
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
        disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_EndMatch, nil)
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
    local formation = team:getCurrentFormation()
    local playersVector = team:getPlayers()
    local disp = PF.CMessageDispatcher_getInstance()
    local size = playersVector:size()
    if team:getSimulationManager():getReferee():getGameMode() == PF.KICK_OFF then
        formation:setCurrentFormationType(PF.FT_Initial)
        for i = 0, size - 1, 1 do
            disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_KickOff, nil)
        end
    elseif team:isKickForUs() then
        formation:setCurrentFormationType(PF.FT_Offensive)
        for i = 0, size - 1, 1 do
            disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_Interrupt, nil)
        end
    else
        formation:setCurrentFormationType(PF.FT_Defensive)
        for i = 0, size - 1, 1 do
            disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_Interrupt, nil)
        end
    end
    if team:isKickForUs() then
        local playerId = team:getKickPlayerID()
        disp:dispatchMsg(1, team:getID(), playerId, PF.Msg_KickIn, nil)
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
    local formation = team:getCurrentFormation()
    if team:getSimulationManager():getReferee():getLastPlayerTouch():getTeam():getID() == team:getID() then
        formation:setCurrentFormationType(PF.FT_Offensive)
    else
        formation:setCurrentFormationType(PF.FT_Defensive)
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