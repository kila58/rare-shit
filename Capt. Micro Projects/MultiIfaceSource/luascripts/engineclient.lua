EngineClient = {}
EngineClient_mt = { __index = EngineClient }

function EngineClient:new()
	return setmetatable({}, EngineClient_mt)
end

function EngineClient:GetScreenSize()
	return EC_GetScreenSize()
end

function EngineClient:ServerCmd(cmdstr)
	EC_ServerCmd(cmdstr)
end

function EngineClient:ClientCmd(cmdstr)
	EC_ClientCmd(cmdstr)
end

function EngineClient:ClientCmd_Unrestricted(cmdstr)
	EC_ClientCmd_Unrestricted(cmdstr)
end

function EngineClient:GetPlayerInfo(entidx)
	local userid, name, guid, friendsname,
		fakeplayers, ishltv, customfiles,
		filesdownloaded = EC_GetPlayerInfo(cmdstr)
	return {userid = userid, name = name,
		friendsname = friendsname, fakeplayers = fakeplayers,
		ishltv = ishltv, customfiles = customfiles,
		filesdownloaded = filesdownloaded}
end

function EngineClient:GetPlayerForUserID(userid)
	return EC_GetPlayerForUserID(userid)
end

function EngineClient:Con_IsVisible()
	return EC_Con_IsVisible()
end

function EngineClient:GetLocalPlayer()
	return EC_GetLocalPlayer()
end

function EngineClient:GetViewAngles()
	return EC_GetViewAngles()
end

function EngineClient:SetViewAngles(p, y, r)
	EC_SetViewAngles(p, y, r)
end

function EngineClient:GetMaxClients()
	return EC_GetMaxClients()
end

function EngineClient:Key_LookupBinding(binding)
	return EC_Key_LookupBinding(binding)
end

function EngineClient:IsInGame()
	return EC_IsInGame()
end

function EngineClient:IsConnected()
	return EC_IsConnected()
end

function EngineClient:IsDrawingLoadingImage()
	return EC_IsDrawingLoadingImage()
end

function EngineClient:Con_NPrintf(pos, str)
	return EC_IsDrawingLoadingImage()
end

function EngineClient:IsBoxVisible(x1,y1,z1, x2,y2,z2)
	return EC_IsBoxVisible(x1,y1,z1, x2,y2,z2)
end

function EngineClient:CullBox(x1,y1,z1, x2,y2,z2)
	return EC_CullBox(x1,y1,z1, x2,y2,z2)
end

function EngineClient:GetGameDirectory()
	return EC_GetGameDirectory()
end

function EngineClient:GetLevelName()
	return EC_GetLevelName()
end

function EngineClient:IsPaused()
	return EC_IsPaused()
end

function EngineClient:IsTakingScreenshot()
	return EC_IsTakingScreenshot()
end

function EngineClient:ExecuteClientCmd(cmdstr)
	EC_ExecuteClientCmd(cmdstr)
end

function EngineClient:SetRestrictServerCommands(restrict)
	EC_SetRestrictServerCommands(restrict)
end

function EngineClient:SetRestrictClientCommands(restrict)
	EC_SetRestrictClientCommands(restrict)
end

function EngineClient:ChangeTeam(teamname)
	EC_ChangeTeam(teamname)
end
