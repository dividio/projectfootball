
---------------------------------------------------

SGoalie_Global = {}

SGoalie_Global["Enter"] = function(player)

end

SGoalie_Global["Execute"] = function(player)

end

SGoalie_Global["Exit"] = function(player)

end

SGoalie_Global["OnMessage"] = function(player, message)
    local handle = false
    local mode = player:getSimulationManager():getReferee():getGameMode()
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
        player:getFSM():changeState("SGoalie_ReturnToHomeRegion")
        handle = true
    elseif message.Msg == PF.Msg_EndMatch then
        player:getFSM():changeState("SPl_Stop")
        handle = true
    end
    return handle
end

---------------------------------------------------

SGoalie_ReturnToHomeRegion = {}

SGoalie_ReturnToHomeRegion["Enter"] = function(player)
    player:getSteering():arriveOn()
end

SGoalie_ReturnToHomeRegion["Execute"] = function(player)
    if player:isBallKickable() then
        player:getFSM():changeState("SGoalie_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player)
       and player:getTeam():isBallInOwnPenaltyArea() then
        player:getFSM():changeState("SGoalie_ChaseBall")
    elseif player:atHome() then
        player:getFSM():changeState("SGoalie_LookBall")
    else
        local strategicPosition = calculateGoaliePosition(player)
        player:getSteering():setTargetPoint(strategicPosition)
        player:getSimulationManager():dash(player, player:getSteering():calculate())
        direction = player:getSimulationManager():getBallPosition() - player:getPosition()
        player:setHeading(direction)
    end
end

SGoalie_ReturnToHomeRegion["Exit"] = function(player)
    player:getSteering():arriveOff()
end

SGoalie_ReturnToHomeRegion["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SGoalie_KickBall = {}

SGoalie_KickBall["Enter"] = function(player)

end

SGoalie_KickBall["Execute"] = function(player)
    if player:isBallKickable() then
        local ball = player:getSimulationManager():getBall()
        local direction
        if player:isTeamLeft() then
            direction = PF.btVector3(55,0,0) - ball:getPosition()
        else
            direction = PF.btVector3(-55,0,0) - ball:getPosition()
        end
        player:getSimulationManager():kick(player, direction)
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player)
       and player:getTeam():isBallInOwnPenaltyArea() then
        player:getFSM():changeState("SGoalie_ChaseBall")
    else
        player:getFSM():changeState("SGoalie_ReturnToHomeRegion")
    end
end

SGoalie_KickBall["Exit"] = function(player)

end

SGoalie_KickBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SGoalie_ChaseBall = {}

SGoalie_ChaseBall["Enter"] = function(player)
    player:getSteering():pursuitOn()
    player:getSteering():setTargetEntity(player:getSimulationManager():getBall())
end

SGoalie_ChaseBall["Execute"] = function(player)
    if player:isBallKickable() then
        player:getFSM():changeState("SGoalie_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player)
       and player:getTeam():isBallInOwnPenaltyArea() then
        player:getSteering():setTargetPoint(player:getSimulationManager():getBallPosition())
        player:getSimulationManager():dash(player, player:getSteering():calculate())
    else
        player:getFSM():changeState("SGoalie_ReturnToHomeRegion")
    end
end

SGoalie_ChaseBall["Exit"] = function(player)
    player:getSteering():pursuitOff()
end

SGoalie_ChaseBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SGoalie_LookBall = {}

SGoalie_LookBall["Enter"] = function(player)
    player:getSteering():stopOn()
end

SGoalie_LookBall["Execute"] = function(player)
    if player:isBallKickable() then
        player:getFSM():changeState("SGoalie_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player)
       and player:getTeam():isBallInOwnPenaltyArea() then
        player:getFSM():changeState("SGoalie_ChaseBall")
    elseif not player:atHome() then
        player:getFSM():changeState("SGoalie_ReturnToHomeRegion")
    else
        player:getSimulationManager():dash(player, player:getSteering():calculate())
        local direction = player:getSimulationManager():getBallPosition() - player:getPosition()
        player:setHeading(direction)
    end
end

SGoalie_LookBall["Exit"] = function(player)
    player:getSteering():stopOff()
end

SGoalie_LookBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

function calculateGoaliePosition(goalie)
    local rectangle = goalie:getTeam():getPlayerStrategicPosition(1):getPlayingArea() -- TODO player number
    local finalPoint = PF.btVector3(0,0,0)
    local topL
    local topR
    local bottomL
    local bottomR
    local goalPoint
    local lineA
    if goalie:isTeamLeft() then
        goalPoint = PF.btVector3(-55,0,0)
        topL = rectangle:getTopLeft()
        bottomR = rectangle:getBottomRight()
        bottomL = PF.btVector3(bottomR:x(), 0, topL:z())
        topR = PF.btVector3(topL:x(), 0, bottomR:z())
        lineA = PF.CLine2D(topL, topR)
    else
        goalPoint = PF.btVector3(55,0,0)
        topL = PF.btVector3(0,0,0) - rectangle:getBottomRight()
        bottomR = PF.btVector3(0,0,0) - rectangle:getTopLeft()
        bottomL = PF.btVector3(bottomR:x(), 0, topL:z())
        topR = PF.btVector3(topL:x(), 0, bottomR:z())
        lineA = PF.CLine2D(bottomL, bottomR)
    end
    local lineBall = PF.CLine2D(goalPoint, goalie:getSimulationManager():getBallPosition())
    finalPoint = lineA:getIntersectionPoint(lineBall)
    if (finalPoint:x() == 0 and finalPoint:z() == 0)
     or finalPoint:z() < topL:z() then
        lineA = PF.CLine2D(topL, bottomL)
        finalPoint = lineA:getIntersectionPoint(lineBall)
    end
    if (finalPoint:x() == 0 and finalPoint:z() == 0)
     or finalPoint:z() > topR:z() then
        lineA = PF.CLine2D(topR, bottomR)
        finalPoint = lineA:getIntersectionPoint(lineBall)
    end
    if finalPoint:x() == 0 and finalPoint:z() == 0 then
        finalPoint = goalPoint
    end
    return finalPoint
end
