
---------------------------------------------------

SGoalie_Global = {}

SGoalie_Global["Enter"] = function(player)
    print("Boo")
end

SGoalie_Global["Execute"] = function(player)

end

SGoalie_Global["Exit"] = function(player)

end

SGoalie_Global["OnMessage"] = function(player, message)
    local handle = false
    local sim = PF.CStateMonitor_getInstance():getSimulationManager()
    if (message.Msg == PF.Msg_Interrupt) or
       (message.Msg == PF.Msg_KickOff) then
        player:getFSM():changeState("SPl_GoToStrategicPosition")
        handle = true
    elseif message.Msg == PF.Msg_GoHome then
        player:getFSM():changeState("SPl_BeforeStart")
        handle = true
    elseif message.Msg == PF.Msg_KickIn then
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