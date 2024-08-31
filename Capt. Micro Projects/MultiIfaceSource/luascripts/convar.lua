ConVar = {}
ConVar_mt = { __index = ConVar }

function ConVar:new(x,y,z)
	return setmetatable({convar = nil, is_cmd = nil}, ConVar_mt)
end

function ConVar:FindVar(name)
	local cv = CV_FindVar(name)
	if (cv ~= nil) then
		return setmetatable({convar = cv, is_cmd = false}, ConVar_mt)
	end
	return nil
end

function ConVar:FindCmd(name)
	local cv = CV_FindCmd(name)
	if (cv ~= nil) then
		return setmetatable({convar = cv, is_cmd = true}, ConVar_mt)
	end
	return nil
end

function ConVar:CreateVar(name, defval, flags, helptext)
	local cv = CV_CreateVar(name, defval, flags, helptext)
	if (cv ~= nil) then
		return setmetatable({convar = cv, is_cmd = false}, ConVar_mt)
	end
	return nil
end

function ConVar:CreateCmd(name, flags, helptext)
	local cv = CV_CreateCmd(name, flags, helptext)
	if (cv ~= nil) then
		return setmetatable({convar = cc, is_cmd = true}, ConVar_mt)
	end
	return nil
end

function ConVar:Delete()
	CV_Delete(self.convar)
end

function ConVar:Dispatch(argstr)
	if (not is_cmd) then return end
	CC_DispatchCmd(self.convar, argstr)
end

function ConVar:GetName()
	return CV_GetName(self.convar)
end

function ConVar:SetName(name)
	CV_SetName(self.convar, name)
end

function ConVar:GetFlags()
	return CV_GetFlags(self.convar)
end

function ConVar:SetFlags(flags)
	CV_SetFlags(self.convar, flags)
end

function ConVar:GetHelpText()
	return CV_GetHelpText(self.convar)
end

function ConVar:SetHelpText(helptext)
	CV_SetHelpText(self.convar, helptext)
end

function ConVar:GetFloat()
	if (is_cmd) then return end
	return CV_GetFloat(self.convar)
end

function ConVar:GetInt()
	if (is_cmd) then return end
	return CV_GetInt(self.convar)
end

function ConVar:GetBool()
	if (is_cmd) then return end
	return CV_GetBool(self.convar)
end

function ConVar:GetString()
	if (is_cmd) then return end
	return CV_GetString(self.convar)
end

function ConVar:SetFloat(value)
	if (is_cmd) then return end
	return CV_SetFloat(self.convar, value)
end

function ConVar:SetInt(value)
	if (is_cmd) then return end
	return CV_SetInt(self.convar, value)
end

function ConVar:SetString(value)
	if (is_cmd) then return end
	return CV_SetString(self.convar, value)
end

function ConVar:Revert()
	if (is_cmd) then return end
	CV_Revert(self.convar)
end

function ConVar:GetMin()
	if (is_cmd) then return end
	return CV_GetMin(self.convar)
end

function ConVar:GetMax()
	if (is_cmd) then return end
	return CV_GetMax(self.convar)
end

function ConVar:GetDefault()
	if (is_cmd) then return end
	return CV_GetDefault(self.convar)
end
