BypassConVar = function(prefix, varname)
	local convar = FindVar(varname)
	if (convar == nil) then
		WriteConsole("Failed to find " .. varname .. ".\n")
		return
	end
	local oldname = GetName(convar)
	local oldflgs = GetFlags(convar)
	WriteConsole("Found " .. GetName(convar) .. ". ConVar=" .. tostring(convar) .. "\n")
	WriteConsole("\tStripping all flags...\n")
	SetFlags(convar,  FCVAR_NONE)
	SetName(convar, prefix .. GetName(convar))
	WriteConsole("\tRenamed to: " .. GetName(convar) .. "\n")
	local spoof = CreateVar(oldname, "0", oldflgs, GetHelpString(convar))
	WriteConsole("\tSpoofed old name! '" .. GetName(spoof) .. "' ConVar=" .. tostring(spoof) .. "\n")
	return convar
end

BypassConCmd = function(prefix, cmdname)
	local concmd = FindCommand(cmdname)
	if (concmd == nil) then
		WriteConsole("Failed to find " .. cmdname .. ".\n")
		return
	end
	local oldname = GetName(concmd)
	local oldflgs = GetFlags(concmd)
	WriteConsole("Found " .. GetName(concmd) .. ". ConCmd=" .. tostring(concmd) .. "\n")
	WriteConsole("\tStripping all flags...\n")
	SetFlags(concmd,  FCVAR_NONE)
	return concmd
end

--[[
--NOT USED DO _NOT_ UNCOMMENT--

function VarChangeCallback(ConVar, OldVal, flOldVal)
	if (ConVar == 0) then return end
	WriteConsole(GetName(ConVar) .. " value changed!\n")
end

function CommandCallback(ConCmd)
	if (ConCmd == 0) then return end
	WriteConsole(GetName(ConCmd) .. " was called!\n")
end
]]
