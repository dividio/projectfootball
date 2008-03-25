
---------------------------------------------------

SRf_Global = {}

SRf_Global["Enter"] = function(referee)

end

SRf_Global["Execute"] = function(referee)
    local cycle = referee:getCycle();
    local duration = referee:getMatchDuration()
    local currentState = referee:getFSM():currentState()
    if (cycle == ( duration / 2)) and (currentState ~= "SRf_HalfTime") then
        referee:getFSM():changeState("SRf_HalfTime")
    elseif (cycle == duration) and (currentState ~= "SRf_End") then
        referee:getFSM():changeState("SRf_End")
    end
    local monitor = PF.CStateMonitor_getInstance()
    local sim = monitor:getSimulationManager()
end

SRf_Global["Exit"] = function(referee)

end

SRf_Global["OnMessage"] = function(referee, message)
    return false
end

---------------------------------------------------

SRf_BeforeStart = {}

SRf_BeforeStart["Enter"] = function(referee)
    referee:setGameMode(PF.BEFORE_START)
end

SRf_BeforeStart["Execute"] = function(referee)
    local monitor = PF.CStateMonitor_getInstance()
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_BeforeStart, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_BeforeStart, nil)
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
        if kickLeftTeam == referee:isHomeTeamInSideLeft() then
            referee:setKickTeam(homeTeam)
            referee:setNextTimeKickOffTeam(awayTeam)
        else
            referee:setKickTeam(awayTeam)
            referee:setNextTimeKickOffTeam(homeTeam)
        end
        referee:getFSM():changeState("SRf_KickOff")
        handle = true
    end
    return handle
end

---------------------------------------------------

SRf_HalfTime = {}

SRf_HalfTime["Enter"] = function(referee)
    referee:setGameMode(PF.HALF_TIME)
    local monitor = PF.CStateMonitor_getInstance()
    monitor:addToLog(referee:getGameModeString())
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    local side = referee:isHomeTeamInSideLeft()
    local team = referee:getNextTimeKickOffTeam()
    referee:setKickTeam(team)
    referee:setNextTimeKickOffTeam(team:getOpponentTeam())
    referee:setHomeTeamInSideLeft(not side)
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_HalfTime, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_HalfTime, nil)
    sim:getBall():setPosition(0,0,0)
end

SRf_HalfTime["Execute"] = function(referee)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local ballPos = sim:getBallPosition()
    sim:getBall():setPosition(0,0,0)
end

SRf_HalfTime["Exit"] = function(referee)

end

SRf_HalfTime["OnMessage"] = function(referee, message)
    local handle = false
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local homeTeam = sim:getHomeTeam()
    local awayTeam = sim:getAwayTeam()
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
    referee:incCycle()
    local monitor = PF.CStateMonitor_getInstance()
    monitor:addToLog(referee:getGameModeString())
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_KickOff, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_KickOff, nil)
end

SRf_KickOff["Execute"] = function(referee)
    referee:incCycle()
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local ballPos = sim:getBallPosition()
    sim:getBall():setPosition(0,0,0)
end

SRf_KickOff["Exit"] = function(referee)

end

SRf_KickOff["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        referee:setLastPlayerTouch(player)
        if player:getTeam():getID() == referee:getKickTeam():getID() then
            referee:getFSM():changeState("SRf_PlayOn")
        else
            referee:setKickTeam(player:getTeam():getOpponentTeam())
            referee:getFSM():changeState("SRf_KickIn")
        end
        handle = true
    end
    return handle
end

---------------------------------------------------

SRf_PlayOn = {}

SRf_PlayOn["Enter"] = function(referee)
    referee:setGameMode(PF.PLAY_ON)
    local monitor = PF.CStateMonitor_getInstance()
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_PlayOn, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_PlayOn, nil)
end

SRf_PlayOn["Execute"] = function(referee)
    referee:incCycle()
    verifyBallPosition(referee)
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
    local monitor = PF.CStateMonitor_getInstance()
    monitor:addToLog(referee:getGameModeString())
    local sim = monitor:getSimulationManager()
    local disp = PF.CMessageDispatcher_getInstance()
    disp:dispatchMsg(0, referee:getID(), sim:getHomeTeam():getID(), PF.Msg_EndMatch, nil)
    disp:dispatchMsg(0, referee:getID(), sim:getAwayTeam():getID(), PF.Msg_EndMatch, nil)
end

SRf_End["Execute"] = function(referee)
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local pos = sim:getBallPosition()
    sim:getBall():setPosition(pos:x(),pos:y(),pos:z())
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
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local ballPos = sim:getBallPosition()
    local floor = PF.btVector3(ballPos:x(),0,ballPos:z())
    sim:getBall():setPosition(floor:x(),0,floor:z())
end

SRf_KickIn["Exit"] = function(referee)

end

SRf_KickIn["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        referee:setLastPlayerTouch(player)
        if player:getTeam():getID() == referee:getKickTeam():getID() then
            referee:getFSM():changeState("SRf_PlayOn")
        else
            referee:setKickTeam(player:getTeam():getOpponentTeam())
            referee:getFSM():changeState("SRf_KickIn")
        end
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
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local ballPos = sim:getBallPosition()
    local floor = PF.btVector3(ballPos:x(),0,ballPos:z())
    sim:getBall():setPosition(floor:x(),0,floor:z())
end

SRf_CornerKick["Exit"] = function(referee)

end

SRf_CornerKick["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        referee:setLastPlayerTouch(player)
        if player:getTeam():getID() == referee:getKickTeam():getID() then
            referee:getFSM():changeState("SRf_PlayOn")
        else
            referee:setKickTeam(player:getTeam():getOpponentTeam())
            referee:getFSM():changeState("SRf_KickIn")
        end
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
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    local ballPos = sim:getBallPosition()
    local floor = PF.btVector3(ballPos:x(),0,ballPos:z())
    sim:getBall():setPosition(floor:x(),0,floor:z())
end

SRf_GoalKick["Exit"] = function(referee)

end

SRf_GoalKick["OnMessage"] = function(referee, message)
    local handle = false
    if message.Msg == PF.Msg_TouchBall then
        local player = PF.CEntityManager_getInstance():getEntityFromID(message.Sender)
        player = PF.CFootballPlayer_getPlayer(player)
        referee:setLastPlayerTouch(player)
        if player:getTeam():getID() == referee:getKickTeam():getID() then
            referee:getFSM():changeState("SRf_PlayOn")
        else
            referee:setKickTeam(player:getTeam():getOpponentTeam())
            referee:getFSM():changeState("SRf_KickIn")
        end
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
        ball:setPosition(0,0,0)
        if referee:isHomeTeamInSideLeft() then
            referee:setKickTeam(sim:getHomeTeam())
            referee:addAwayGoal(player);
        else
            referee:setKickTeam(sim:getAwayTeam())
            referee:addHomeGoal(player);
        end
    elseif ball:isInRightGoal() then
        referee:getFSM():changeState("SRf_KickOff")
        ball:setPosition(0,0,0)
        if referee:isHomeTeamInSideLeft() then
            referee:setKickTeam(sim:getAwayTeam())
            referee:addHomeGoal(player);
        else
            referee:setKickTeam(sim:getHomeTeam())
            referee:addAwayGoal(player);
        end
    elseif ball:crossLeftLine() then
        referee:setKickTeam(player:getTeam():getOpponentTeam())
        if player:isTeamLeft() then
            referee:getFSM():changeState("SRf_CornerKick")
            if z > 0 then
                ball:setPosition(-54.5,0,34.5)
            else
                ball:setPosition(-54.5,0,-34.5)
            end
        else
            referee:getFSM():changeState("SRf_GoalKick")
            if z > 0 then
                ball:setPosition(-49.5,0,9)
            else
                ball:setPosition(-49.5,0,-9)
            end
        end
    elseif ball:crossRightLine() then
        referee:setKickTeam(player:getTeam():getOpponentTeam())
        if player:isTeamLeft() then
            referee:getFSM():changeState("SRf_GoalKick")
            if z > 0 then
                ball:setPosition(49.5,0,9)
            else
                ball:setPosition(49.5,0,-9)
            end
        else
            referee:getFSM():changeState("SRf_CornerKick")
            if z > 0 then
                ball:setPosition(54.5,0,34.5)
            else
                ball:setPosition(54.5,0,-34.5)
            end
        end
    elseif ball:crossTopLine() then
        referee:setKickTeam(player:getTeam():getOpponentTeam())
        referee:getFSM():changeState("SRf_KickIn")
        ball:setPosition(x,0,-35)
    elseif ball:crossBottomLine() then
        referee:setKickTeam(player:getTeam():getOpponentTeam())
        referee:getFSM():changeState("SRf_KickIn")
        ball:setPosition(x,0,35)
    end
end