
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
        local playersVector = team:getPlayers()
        local disp = PF.CMessageDispatcher_getInstance()
        local size = playersVector:size()
        for i = 0, size - 1, 1 do
            disp:dispatchMsg(0, team:getID(), playersVector[i]:getID(), PF.Msg_KickOff, nil)
        end
        handle = true
    end
    return handle
end

---------------------------------------------------
STm_BeforeStart = {}

STm_BeforeStart["Enter"] = function(referee)

end

STm_BeforeStart["Execute"] = function(referee)

end

STm_BeforeStart["Exit"] = function(referee)

end

STm_BeforeStart["OnMessage"] = function(referee, message)
    return false
end

---------------------------------------------------