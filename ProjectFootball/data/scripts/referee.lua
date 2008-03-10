
---------------------------------------------------

SRf_BeforeStart = {}

SRf_BeforeStart["Enter"] = function(referee)
    referee:setGameMode(PF.BEFORE_START)
end

SRf_BeforeStart["Execute"] = function(referee)

end

SRf_BeforeStart["Exit"] = function(referee)

end

SRf_BeforeStart["OnMessage"] = function(referee, message)
    local handle = false
    math.randomseed(os.clock())
    local left = math.random(0,1)
    local kickLeftTeam = false
    if (left == 1) then
        kickLeftTeam = true
    end
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local homeTeam = sim:getHomeTeam()
    local awayTeam = sim:getAwayTeam()
    if message.Msg == PF.Msg_StartMatch then
        referee:getFSM():changeState("SRf_KickOff")
        if kickLeftTeam == referee:isHomeTeamInSideLeft() then
            referee:setKickTeam(homeTeam)
        else
            referee:setKickTeam(awayTeam)
        end
        handle = true
    end
    return handle
end

---------------------------------------------------

SRf_HalfTime = {}

SRf_HalfTime["Enter"] = function(referee)
    referee:setGameMode(PF.HALF_TIME)
    PF.CStateMonitor_getInstance():addToLog(referee:getGameModeString())
    local side = referee:isHomeTeamInSideLeft()
    referee:setHomeTeamInSideLeft(not side)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    sim:changePlayersSide()
    sim:getBall():setPosition(0,1,0)
end

SRf_HalfTime["Execute"] = function(referee)

end

SRf_HalfTime["Exit"] = function(referee)

end

SRf_HalfTime["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_StartMatch then
        referee:getFSM():changeState("SRf_KickOff")
        handle = true
    end
    return handle
end

---------------------------------------------------

SRf_KickOff = {}

SRf_KickOff["Enter"] = function(referee)
    referee:setGameMode(PF.KICK_OFF)
    local monitor = PF.CStateMonitor_getInstance()
    monitor:addToLog(referee:getGameModeString())
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_KickOff, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_KickOff, nil)
end

SRf_KickOff["Execute"] = function(referee)
    referee:incCycle()
    local cycle = referee:getCycle();
    local duration = referee:getMatchDuration()
    if cycle == ( duration / 2) then
        referee:getFSM():changeState("SRf_HalfTime")
    elseif cycle == duration then
        referee:getFSM():changeState("SRf_End")
    end
end

SRf_KickOff["Exit"] = function(referee)

end

SRf_KickOff["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        if player:getTeam():getID() == referee:getKickTeam():getID() then
            referee:getFSM():changeState("SRf_PlayOn")
        else
            referee:getFSM():changeState("SRf_KickIn")
        end
        referee:setLastPlayerTouch(player)
        handle = true
    end
    return handle
end

---------------------------------------------------

SRf_PlayOn = {}

SRf_PlayOn["Enter"] = function(referee)
    referee:setGameMode(PF.PLAY_ON)
end

SRf_PlayOn["Execute"] = function(referee)
    referee:incCycle()
    local cycle = referee:getCycle();
    local duration = referee:getMatchDuration()
    verifyBallPosition(referee)
    if cycle == ( duration / 2) then
        referee:getFSM():changeState("SRf_HalfTime")
    elseif cycle == duration then
        referee:getFSM():changeState("SRf_End")
    end
end

SRf_PlayOn["Exit"] = function(referee)

end

SRf_PlayOn["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        referee:setLastPlayerTouch(player)
        handle = true
    end
    return handle
end

---------------------------------------------------

SRf_End = {}

SRf_End["Enter"] = function(referee)
    referee:setGameMode(PF.END)
    PF.CStateMonitor_getInstance():addToLog(referee:getGameModeString())
end

SRf_End["Execute"] = function(referee)

end

SRf_End["Exit"] = function(referee)

end

SRf_End["OnMessage"] = function(referee, message)
    return false
end

---------------------------------------------------

SRf_KickIn = {}

SRf_KickIn["Enter"] = function(referee)
    referee:setGameMode(PF.KICK_IN)
    local monitor = PF.CStateMonitor_getInstance()
    monitor:addToLog(referee:getGameModeString())
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_KickOff, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_KickOff, nil)
end

SRf_KickIn["Execute"] = function(referee)
    referee:incCycle()
    local cycle = referee:getCycle();
    local duration = referee:getMatchDuration()
    if cycle == ( duration / 2) then
        referee:getFSM():changeState("SRf_HalfTime")
    elseif cycle == duration then
        referee:getFSM():changeState("SRf_End")
    end
end

SRf_KickIn["Exit"] = function(referee)

end

SRf_KickIn["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        if player:getTeam():getID() == referee:getKickTeam():getID() then
            referee:getFSM():changeState("SRf_PlayOn")
        end
        referee:setLastPlayerTouch(player)
        handle = true
    end
    return handle
end

---------------------------------------------------

SRf_CornerKick = {}

SRf_CornerKick["Enter"] = function(referee)
    referee:setGameMode(PF.CORNER_KICK)
    local monitor = PF.CStateMonitor_getInstance()
    monitor:addToLog(referee:getGameModeString())
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_KickOff, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_KickOff, nil)
end

SRf_CornerKick["Execute"] = function(referee)
    referee:incCycle()
    local cycle = referee:getCycle();
    local duration = referee:getMatchDuration()
    if cycle == ( duration / 2) then
        referee:getFSM():changeState("SRf_HalfTime")
    elseif cycle == duration then
        referee:getFSM():changeState("SRf_End")
    end
end

SRf_CornerKick["Exit"] = function(referee)

end

SRf_CornerKick["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        if player:getTeam():getID() == referee:getKickTeam():getID() then
            referee:getFSM():changeState("SRf_PlayOn")
        else
            referee:getFSM():changeState("SRf_KickIn")
        end
        referee:setLastPlayerTouch(player)
        handle = true
    end
    return handle
end


---------------------------------------------------

SRf_GoalKick = {}

SRf_GoalKick["Enter"] = function(referee)
    referee:setGameMode(PF.GOAL_KICK)
    local monitor = PF.CStateMonitor_getInstance()
    monitor:addToLog(referee:getGameModeString())
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_KickOff, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_KickOff, nil)
end

SRf_GoalKick["Execute"] = function(referee)
    referee:incCycle()
    local cycle = referee:getCycle();
    local duration = referee:getMatchDuration()
    if cycle == ( duration / 2) then
        referee:getFSM():changeState("SRf_HalfTime")
    elseif cycle == duration then
        referee:getFSM():changeState("SRf_End")
    end
end

SRf_GoalKick["Exit"] = function(referee)

end

SRf_GoalKick["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        if player:getTeam():getID() == referee:getKickTeam():getID() then
            referee:getFSM():changeState("SRf_PlayOn")
        else
            referee:getFSM():changeState("SRf_KickIn")
        end
        referee:setLastPlayerTouch(player)
        handle = true
    end
    return handle
end

---------------------------------------------------

function verifyBallPosition(referee)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local ball = sim:getBall()
    local x = ball:getPosition():x()
    local z = ball:getPosition():z()
    local player = referee:getLastPlayerTouch()
    if ball:isInLeftGoal() then
        referee:getFSM():changeState("SRf_KickOff")
        ball:setPosition(0,1,0)
        if referee:isHomeTeamInSideLeft() then
            referee:setKickTeam(sim:getHomeTeam())
            referee:addAwayGoal(player);
        else
            referee:setKickTeam(sim:getAwayTeam())
            referee:addHomeGoal(player);
        end
    elseif ball:isInRightGoal() then
        referee:getFSM():changeState("SRf_KickOff")
        ball:setPosition(0,1,0)
        if referee:isHomeTeamInSideLeft() then
            referee:setKickTeam(sim:getAwayTeam())
            referee:addHomeGoal(player);
        else
            referee:setKickTeam(sim:getHomeTeam())
            referee:addAwayGoal(player);
        end
    elseif ball:crossLeftLine() then
        if player:isTeamLeft() then
            referee:getFSM():changeState("SRf_CornerKick")
            if z > 0 then
                ball:setPosition(-54.5,1,34.5)
            else
                ball:setPosition(-54.5,1,-34.5)
            end
            if referee:isHomeTeamInSideLeft() then
                referee:setKickTeam(sim:getAwayTeam())
            else
                referee:setKickTeam(sim:getHomeTeam())
            end
        else
            referee:getFSM():changeState("SRf_GoalKick")
            if z > 0 then
                ball:setPosition(-49.5,1,9)
            else
                ball:setPosition(-49.5,1,-9)
            end
            if referee:isHomeTeamInSideLeft() then
                referee:setKickTeam(sim:getHomeTeam())
            else
                referee:setKickTeam(sim:getAwayTeam())
            end
        end
    elseif ball:crossRightLine() then
        if player:isTeamLeft() then
            referee:getFSM():changeState("SRf_GoalKick")
            if z > 0 then
                ball:setPosition(49.5,1,9)
            else
                ball:setPosition(49.5,1,-9)
            end
            if referee:isHomeTeamInSideLeft() then
                referee:setKickTeam(sim:getAwayTeam())
            else
                referee:setKickTeam(sim:getHomeTeam())
            end
        else
            referee:getFSM():changeState("SRf_CornerKick")
            if z > 0 then
                ball:setPosition(54.5,1,34.5)
            else
                ball:setPosition(54.5,1,-34.5)
            end
            if referee:isHomeTeamInSideLeft() then
                referee:setKickTeam(sim:getHomeTeam())
            else
                referee:setKickTeam(sim:getAwayTeam())
            end
        end
    elseif ball:crossTopLine() then
        referee:getFSM():changeState("SRf_KickIn")
        ball:setPosition(x,1,-35)
        if player:isTeamLeft() == referee:isHomeTeamInSideLeft() then
            referee:setKickTeam(sim:getAwayTeam())
        else
            referee:setKickTeam(sim:getHomeTeam())
        end
    elseif ball:crossBottomLine() then
        referee:getFSM():changeState("SRf_KickIn")
        ball:setPosition(x,1,35)
        if player:isTeamLeft() == referee:isHomeTeamInSideLeft() then
            referee:setKickTeam(sim:getAwayTeam())
        else
            referee:setKickTeam(sim:getHomeTeam())
        end
    end
end