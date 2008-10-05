
---------------------------------------------------

SAttacker_Global = {}

SAttacker_Global["Enter"] = function(player)

end

SAttacker_Global["Execute"] = function(player)

end

SAttacker_Global["Exit"] = function(player)

end

SAttacker_Global["OnMessage"] = function(player, message)
    local handle = false
    local sim = PF.CScreenSimulator_getInstance():getSimulationManager()
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
        player:getFSM():changeState("SAttacker_ReturnToHomeRegion")
        handle = true
    elseif message.Msg == PF.Msg_EndMatch then
        player:getFSM():changeState("SPl_Stop")
        handle = true
    end
    return handle
end

---------------------------------------------------

SAttacker_ReturnToHomeRegion = {}

SAttacker_ReturnToHomeRegion["Enter"] = function(player)
    player:getSteering():arriveOn()
end

SAttacker_ReturnToHomeRegion["Execute"] = function(player)
    if player:isBallKickable() then
        player:getFSM():changeState("SAttacker_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player)
       and player:getTeam():isBallInOwnPenaltyArea() then
        player:getFSM():changeState("SAttacker_ChaseBall")
    elseif player:atHome() then
        player:getFSM():changeState("SAttacker_LookBall")
    else
        local sim = PF.CScreenSimulator_getInstance():getSimulationManager()
        local strategicPosition = player:getStrategicPosition()
        player:getSteering():setTargetPoint(strategicPosition)
        sim:dash(player, player:getSteering():calculate())
    end
end

SAttacker_ReturnToHomeRegion["Exit"] = function(player)
    player:getSteering():arriveOff()
end

SAttacker_ReturnToHomeRegion["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SAttacker_KickBall = {}

SAttacker_KickBall["Enter"] = function(player)

end

SAttacker_KickBall["Execute"] = function(player)
    if player:isBallKickable() then
        local opponentGoal
        if player:isTeamLeft() then
            opponentGoal = PF.btVector3(55,0,0)
        else
            opponentGoal = PF.btVector3(-55,0,0)
        end
        if player:getPosition():distance(opponentGoal) < 25 then
            player:kickTo(opponentGoal, 25)
            player:getFSM():changeState("SAttacker_LookBall")
        else
            player:getFSM():changeState("SAttacker_Dribble")
        end
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player)
       and player:getTeam():isBallInOwnPenaltyArea() then
        player:getFSM():changeState("SAttacker_ChaseBall")
    else
        player:getFSM():changeState("SAttacker_ReturnToHomeRegion")
    end
end

SAttacker_KickBall["Exit"] = function(player)

end

SAttacker_KickBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SAttacker_ChaseBall = {}

SAttacker_ChaseBall["Enter"] = function(player)
    local sim = PF.CScreenSimulator_getInstance():getSimulationManager()
    player:getSteering():pursuitOn()
    player:getSteering():setTargetEntity(sim:getBall())
end

SAttacker_ChaseBall["Execute"] = function(player)
    if player:isBallKickable() then
        player:getFSM():changeState("SAttacker_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player)
       and player:getTeam():isBallInOwnPenaltyArea() then
        local sim = PF.CScreenSimulator_getInstance():getSimulationManager()
        player:getSteering():setTargetPoint(sim:getBallPosition())
        sim:dash(player, player:getSteering():calculate())
    else
        player:getFSM():changeState("SAttacker_ReturnToHomeRegion")
    end
end

SAttacker_ChaseBall["Exit"] = function(player)
    player:getSteering():pursuitOff()
end

SAttacker_ChaseBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SAttacker_LookBall = {}

SAttacker_LookBall["Enter"] = function(player)
    player:getSteering():stopOn()
end

SAttacker_LookBall["Execute"] = function(player)
    if player:isBallKickable() then
        player:getFSM():changeState("SAttacker_KickBall")
    elseif player:getTeam():isNearestTeamMatePlayerToBall(player)
       and player:getTeam():isBallInOwnPenaltyArea() then
        player:getFSM():changeState("SAttacker_ChaseBall")
    elseif not player:atHome() then
        player:getFSM():changeState("SAttacker_ReturnToHomeRegion")
    else
        local sim = PF.CScreenSimulator_getInstance():getSimulationManager()
        sim:dash(player, player:getSteering():calculate())
        local direction = sim:getBallPosition() - player:getPosition()
        player:setHeading(direction)
    end
end

SAttacker_LookBall["Exit"] = function(player)
    player:getSteering():stopOff()
end

SAttacker_LookBall["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------

SAttacker_Dribble = {}

SAttacker_Dribble["Enter"] = function(player)
    player:getTeam():setControllingPlayer(player)
end

SAttacker_Dribble["Execute"] = function(player)
    local ownGoalFacing = player:getHomeGoalFacing()
    local direction = player:getHeading()
    local dot = ownGoalFacing:dot(direction)
    if dot < 0 then
        -- TODO Player has to turn with the ball
        player:kickTo(ownGoalFacing, 1)
    else
        player:kickTo(ownGoalFacing, 1)
    end
    player:getFSM():changeState("SAttacker_ChaseBall")
end

SAttacker_Dribble["Exit"] = function(player)

end

SAttacker_Dribble["OnMessage"] = function(player, message)
    return false
end

---------------------------------------------------
