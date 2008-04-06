
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
    local mode = sim:getReferee():getGameMode()
    if (message.Msg == PF.Msg_Interrupt) then
        player:getFSM():changeState("SPl_GoToStrategicPosition")
        handle = true
    elseif message.Msg == PF.Msg_GoHome or
       (message.Msg == PF.Msg_KickOff) then
        player:getFSM():changeState("SPl_BeforeStart")
        handle = true
    elseif (message.Msg == PF.Msg_KickIn) and not (mode == PF.END) and not (mode == PF.HALF_TIME) then
        player:getFSM():changeState("SPl_GoToKickPosition")
        handle = true
    elseif message.Msg == PF.Msg_PlayOn then
        player:getFSM():changeState("SPl_ReturnToHomeRegion")
        handle = true
    elseif message.Msg == PF.Msg_EndMatch then
        player:getFSM():changeState("SPl_Stop")
        handle = true
    end
    return handle
end

---------------------------------------------------

SPl_BeforeStart = {}

SPl_BeforeStart["Enter"] = function(player)

end

SPl_BeforeStart["Execute"] = function(player)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    if player:atHome() then
        player:getFSM():changeState("SPl_Stop")
    else
        local pos = player:getStrategicPosition()
        sim:move(player, pos:x(), pos:z())
    end
end

SPl_BeforeStart["Exit"] = function(player)

end

SPl_BeforeStart["OnMessage"] = function(player, message)
    local handle = false
    return handle
end

---------------------------------------------------

SPl_Stop = {}

SPl_Stop["Enter"] = function(player)
    player:getSteering():stopOn()
end

SPl_Stop["Execute"] = function(player)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    sim:dash(player, player:getSteering():calculate())
    direction = sim:getBallPosition() - player:getPosition()
    player:setHeading(direction)
end

SPl_Stop["Exit"] = function(player)
    player:getSteering():stopOff()
end

SPl_Stop["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_LookBall = {}

SPl_LookBall["Enter"] = function(player)
    player:getSteering():stopOn()
end

SPl_LookBall["Execute"] = function(player)
    if player:isBallKickable() then
        player:getFSM():changeState("SPl_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player) then
        player:getFSM():changeState("SPl_ChaseBall")
    elseif not player:atHome() then
        player:getFSM():changeState("SPl_ReturnToHomeRegion")
    else
        local sim = PF.CStateMonitor_getInstance():getSimulationManager()
        sim:dash(player, player:getSteering():calculate())
        local direction = sim:getBallPosition() - player:getPosition()
        player:setHeading(direction)
    end
end

SPl_LookBall["Exit"] = function(player)
    player:getSteering():stopOff()
end

SPl_LookBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_GoToKickPosition = {}

SPl_GoToKickPosition["Enter"] = function(player)
    player:getSteering():arriveOn()
end

SPl_GoToKickPosition["Execute"] = function(player)
    if player:atKickPosition() then
        player:getFSM():changeState("SPl_KickIn")
    else
      local sim = PF.CStateMonitor_getInstance():getSimulationManager()
      player:getSteering():setTargetPoint(sim:getBallPosition())
      sim:dash(player, player:getSteering():calculate())
    end
end

SPl_GoToKickPosition["Exit"] = function(player)
    player:getSteering():arriveOff()
end

SPl_GoToKickPosition["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_GoToStrategicPosition = {}

SPl_GoToStrategicPosition["Enter"] = function(player)
    player:getSteering():arriveOn()
end

SPl_GoToStrategicPosition["Execute"] = function(player)
    if player:atHome() then
        player:getFSM():changeState("SPl_Stop")
    else
        local sim = PF.CStateMonitor_getInstance():getSimulationManager()
        player:getSteering():setTargetPoint(player:getStrategicPosition())
        sim:dash(player, player:getSteering():calculate())
    end
end

SPl_GoToStrategicPosition["Exit"] = function(player)
    player:getSteering():arriveOff()
end

SPl_GoToStrategicPosition["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_KickBall = {}

SPl_KickBall["Enter"] = function(player)
    player:getTeam():setControllingPlayer(player)
    if not player:isBallKickable() then
        player:getFSM():changeState("SPl_ChaseBall")
    end
end

SPl_KickBall["Execute"] = function(player)
    if player:isBallKickable() then
        local direction
        if player:isTeamLeft() then
            direction = PF.btVector3(55,0,0)
        else
            direction = PF.btVector3(-55,0,0)
        end
        player:kickTo(direction, 25)
        player:getFSM():changeState("SPl_LookBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player) then
        player:getFSM():changeState("SPl_ChaseBall")
    else
        player:getFSM():changeState("SPl_ReturnToHomeRegion")
    end
end

SPl_KickBall["Exit"] = function(player)

end

SPl_KickBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_KickIn = {}

SPl_KickIn["Enter"] = function(player)

end

SPl_KickIn["Execute"] = function(player)
    if player:isBallKickable() then
        local sim = PF.CStateMonitor_getInstance():getSimulationManager()
        local ball = sim:getBall()
        local direction
        if player:isTeamLeft() then
            direction = PF.btVector3(55,0,0)
        else
            direction = PF.btVector3(-55,0,0)
        end
        player:kickTo(direction, 25)
    end
end

SPl_KickIn["Exit"] = function(player)

end

SPl_KickIn["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SPl_ChaseBall = {}

SPl_ChaseBall["Enter"] = function(player)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    player:getSteering():pursuitOn()
    player:getSteering():setTargetEntity(sim:getBall())
end

SPl_ChaseBall["Execute"] = function(player)
    if player:isBallKickable() then
        player:getFSM():changeState("SPl_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player) then
        local sim = PF.CStateMonitor_getInstance():getSimulationManager()
        player:getSteering():setTargetPoint(sim:getBallPosition())
        sim:dash(player, player:getSteering():calculate())
    else
        player:getFSM():changeState("SPl_ReturnToHomeRegion")
    end
end

SPl_ChaseBall["Exit"] = function(player)
    player:getSteering():pursuitOff()
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
    if player:isBallKickable() then
        player:getFSM():changeState("SPl_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player) then
        player:getFSM():changeState("SPl_ChaseBall")
    elseif player:atHome() then
        player:getFSM():changeState("SPl_LookBall")
    else
        local sim = PF.CStateMonitor_getInstance():getSimulationManager()
        local strategicPosition = player:getStrategicPosition()
        player:getSteering():setTargetPoint(strategicPosition)
        sim:dash(player, player:getSteering():calculate())
    end
end

SPl_ReturnToHomeRegion["Exit"] = function(player)
    player:getSteering():arriveOff()
end

SPl_ReturnToHomeRegion["OnMessage"] = function(player, message)
    return false
end
