
---------------------------------------------------

SPl_Global = {}

SPl_Global["Enter"] = function(player)

end

SPl_Global["Execute"] = function(player)

end

SPl_Global["Exit"] = function(player)

end

SPl_Global["OnMessage"] = function(player, message)
    local handle = false
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    if message.Msg == PF.Msg_Wait then
        player:getFSM():changeState("SPl_Wait")
        handle = true
    elseif message.Msg == PF.Msg_GoHome then
        player:getFSM():changeState("SPl_ReturnToHomeRegion")
        handle = true
    elseif message.Msg == PF.Msg_KickOff then
        player:getFSM():changeState("SPl_KickIn")
        handle = true
    end
    return handle
end

---------------------------------------------------

SPl_Wait = {}

SPl_Wait["Enter"] = function(player)

end

SPl_Wait["Execute"] = function(player)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local strategicPosition = player:getStrategicPosition()
    if (not (sim:getReferee():getGameMode() == PF.BEFORE_START)) and
       (not (sim:getReferee():getGameMode() == PF.HALF_TIME)) and
       (not (sim:getReferee():getGameMode() == PF.KICK_OFF)) then
        if player:getTeam():isNearestTeamMatePlayerToBall(player) then
            player:getFSM():changeState("SPl_ChaseBall")
        end
    elseif player:getPosition():distance(strategicPosition) > 2 then
        player:getFSM():changeState("SPl_ReturnToHomeRegion")
    end
end

SPl_Wait["Exit"] = function(player)

end

SPl_Wait["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_KickBall = {}

SPl_KickBall["Enter"] = function(player)

end

SPl_KickBall["Execute"] = function(player)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local direction
    if player:isTeamLeft() then
        direction = PF.btVector3(55,0,0) - player:getPosition()
    else
        direction = PF.btVector3(-55,0,0) - player:getPosition()
    end
    sim:kick(player, direction)
    player:getFSM():changeState("SPl_Wait")
end

SPl_KickBall["Exit"] = function(player)

end

SPl_KickBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_KickIn = {}

SPl_KickIn["Enter"] = function(player)
    player:getSteering():arriveOn()
end

SPl_KickIn["Execute"] = function(player)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local team = player:getTeam()
    if team:isKickForUs() then
        if team:isNearestPlayerToBall(player) then
            if player:isBallKickable() then
                local direction
                if player:isTeamLeft() then
                    direction = PF.btVector3(55,0,0) - player:getPosition()
                else
                    direction = PF.btVector3(-55,0,0) - player:getPosition()
                end
                sim:kick(player, direction)
            else
                player:getSteering():setTargetPoint(sim:getBallPosition())
                sim:dash(player, player:getSteering():calculate())
            end
        else
            player:getFSM():changeState("SPl_ReturnToHomeRegion")
        end
    else
        player:getFSM():changeState("SPl_ReturnToHomeRegion")
    end
end

SPl_KickIn["Exit"] = function(player)
    player:getSteering():arriveOff()
end

SPl_KickIn["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------
SPl_ChaseBall = {}

SPl_ChaseBall["Enter"] = function(player)
    player:getSteering():arriveOn()
end

SPl_ChaseBall["Execute"] = function(player)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    if player:isBallKickable() then
        player:getFSM():changeState("SPl_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player) then
        player:getSteering():setTargetPoint(sim:getBallPosition())
        sim:dash(player, player:getSteering():calculate())
    else
        player:getFSM():changeState("SPl_ReturnToHomeRegion")
    end
end

SPl_ChaseBall["Exit"] = function(player)
    player:getSteering():arriveOff()
end

SPl_ChaseBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_ReturnToHomeRegion = {}

SPl_ReturnToHomeRegion["Enter"] = function(player)
    player:getSteering():arriveOn()
end

SPl_ReturnToHomeRegion["Execute"] = function(player)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local strategicPosition = player:getStrategicPosition()
    if player:getPosition():distance(strategicPosition) > 2 then
        player:getSteering():setTargetPoint(strategicPosition)
        sim:dash(player, player:getSteering():calculate())
    else
        player:getFSM():changeState("SPl_Wait")
    end
end

SPl_ReturnToHomeRegion["Exit"] = function(player)
    player:getSteering():arriveOff()
end

SPl_ReturnToHomeRegion["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------