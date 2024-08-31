--[[

FrostBot by Daz
"just cause i'm an aspie doesn't mean i'm an autist"

Credits:
C0BRA
noPE
Fr1kin

Started 8/7/2014
Finished 8/8/2014

]]

--[[

Localization
Purpose: Keep things running fast as a kenyan while helping own the anti-cheats.

]]
local Frost 		= {}
local FrostTab		= table.Copy
local FrostR 		= require
local FrostPr       = print
local FrostD        = debug
local FrostRot      = rotate
local FrostGHN      = GetHostName
local FrostIn       = include
local FrostUtil     = util
local FrostVgui     = vgui
local FrostCount    = table.Count
local FrostDate     = os.date
local FrostCa       = cam
local FrostRen      = render
local RealCurTime   = SysTime
local FrostPlayer   = player
local FrostPairs    = pairs
local FrostMath     = math
local FrostPackage  = package
local FrostAngle    = Angle
local FrostInput    = input
local FrostTeam     = team
local FrostString   = string
local FrostEngine   = engine
local FrostRFT      = RealFrameTime
local Vecta         = Vector
local _R            = FrostTab(debug.getregistry()) //public version
local __R 			= FrostTab(debug.getregistry()) //private version
local __G 			= FrostTab(_G)
local __f           = file
if Frost == nil then
    FrostPr('The table "Frost" was nil\nLooks like we gotta do it all over again.') // looks like we gotta do it all over again
    FrostIn('includes/extensions/table.lua')
    Frost = {} // if Frost is nil we will try to include table again, then try to create "Frost" again.
end
if Frost == nil then
    FrostPr('Something is keeping the table "Frost" from registering correctly!') //our table isn't creating, oh well.
    return
end
Frost['__key']		= {}
Frost['__hook']     = {}
Frost['__cone']		= {}
Frost['__targ']		= {}
Frost['__dist']		= {}
Frost['__meta']		= {}
Frost['__det']		= {}
Frost['__cvar']		= {}
Frost['__bullet']	= {}
Frost['__ang']		= FrostAngle( 0, 0, 0 )
Frost['__aiming']	= false

--[[

Cheat Files
Purpose: Any cheat file should go here, this will allow us to protect it with our detours.

]]

Frost.CheatFiles = {
        "gmcl_frost_win32.dll",
        "frost.lua",
        "frost_logs.txt",
}

local copy, copyR, __c = FrostTab(__G), FrostTab(__R), {}

local function FreeMetatable(tbl)
	__G["rawset"](tbl, "__metatable", {})
	local meta = __G["debug"]["getmetatable"](tbl)
	if(meta && __G["type"](meta) != "table") then
		meta.__metatable = {}
	end
end

--[[

Copy Metas
Purpose: A function to let us copy metas we will eventually use.

]]

function Frost:CopyMeta(meta)
	if(Frost['__meta'][meta]) then return Frost['__meta'][meta] end
	Frost['__meta'][meta] = FrostTab(__R[meta])
	return Frost['__meta'][meta]
end

--[[

Detour
Purpose: Allows us to keep things from finding us.

]]

function Frost:Detour(old, new)
	Frost['__det'][new] = old
	return new
end

local oldPrint = print

--[[

Require our module and copy the table.
Purpose: This will allow us to run "bass" which is our module and copy the table from bass for later use.

]]

_G.require ("bass")

if package.loaded.bass then
    Frost.Bass = FrostTab['bass']
    _G.bass = nil
    package.loaded.bass = nil
end

--[[

Init
Purpose: Initalize the cheat, copy our metatables.

]]

function Frost:Init()
	__c.Player 	 = Frost:CopyMeta("Player")
	__c.Entity 	 = Frost:CopyMeta("Entity")
	__c.CUserCmd = Frost:CopyMeta("CUserCmd")
	__c.Angle 	 = Frost:CopyMeta("Angle")
	__c.Vector 	 = Frost:CopyMeta("Vector")
	__c.VMatrix	 = Frost:CopyMeta("VMatrix")
end

--[[

Logging System
Purpose: Log stuff, yo

]]

function Frost:Log()
    if not __f['Exists']("frost_logs.txt", "DATA") then
        //__f.CreateDir("frost_logs")
        __f['Write']( "frost_logs.txt", "Log started on "..FrostDate()..":\n")
    end
end

--[[

Calling Frost:Log() will create our logging system's files, and then we can call __f.Append to log stuff.

]]

Frost:Log()

--[[

Time to do real detours.

]]

debug.getinfo = Frost:Detour( debug.getinfo, function( func, ... )
	local newFunc = ( type( func ) == "number" ) && func + 1 || func
	
	local tbl = Frost.__det[debug.getinfo]( Frost.__det[func] || newFunc, ... )
	if( tbl != nil ) then
		tbl.func = Frost.__det[func] || tbl.func
	end
	return tbl
end )

debug.getupvalue = Frost:Detour( debug.getupvalue, function( func, ... )
	return Frost.__det[debug.getupvalue]( Frost.__det[func] || func, ... )
end )

table.Empty = Frost:Detour(table.Empty, function( tbl )
	if( tbl == _G || tbl == _R ) then
        oldPrint("On "..FrostDate().." We stopped an attempt to empty _G or _R on "..FrostGHN()..".\n")
		__f['Append']( "frost_logs.txt", "On "..FrostDate().." We stopped an attempt to empty _G or _R on "..FrostGHN()..".\r\n" )
		return
	end
	return Frost.__det[table.Empty]( tbl )
end )

file.Find = Frost:Detour( file.Find, function( filename, userbase )
    if not filename then return end
    
    for k, file_ in copy['pairs']( Frost.CheatFiles ) do
        if copy['string']['find']( filename, file_ ) then
            oldPrint("On "..FrostDate().." "..FrostGHN().." looked for "..filename..", nope.\n")
            __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." looked for "..filename..", nope.\r\n" )
            return false
        end
    end
    
    if copy['string']['find']( filename, "/*." ) then
        oldPrint("On "..FrostDate().." "..FrostGHN().." looked for "..filename..", spoofing.\n")
        __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." looked for "..filename..", spoofing.\r\n" )
            
        local filetable = Frost.__det[file.Find]( filename, userbase )
        local tabletoreturn = {}
            
        for k, file_ in copy['pairs']( filetable ) do
            if !copy['table']['HasValue']( Frost.CheatFiles, file_ ) then
                copy['table']['insert']( tabletoreturn, file_ )
            end
        end
        
        if ( #tabletoreturn or FrostCount( tabletoreturn ) ) == 0 then
            oldPrint("On "..FrostDate().." "..FrostGHN().." requested a file from us, the list returned empty.\n")
            __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." requested a file from us, the list returned empty.\r\n" )
        else
            oldPrint("On "..FrostDate().." "..FrostGHN().." looked in our file list, spoofed: "..copy['table']['concat'](tabletoreturn,",")..".\n")
            __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." looked in our file list, spoofed: "..copy['table']['concat'](tabletoreturn,",")..".\r\n")
        end
        
        return tabletoreturn
    end
    
    return Frost.__det[ file.Find ]( filename, userbase )
end )

file.Exists = Frost:Detour( file.Exists, function( filename, userbase )
    if not filename then return end
    
    for k, file in copy['pairs']( Frost.CheatFiles ) do
        if copy['string']['find']( filename, file ) then
                oldPrint("On "..FrostDate().." "..FrostGHN().." looked for us.\n")
              __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." looked for us.\r\n" )
            return false
        end
    end
    return Frost.__det[file.Exists]( filename, userbase )
end )

RunConsoleCommand = Frost:Detour( RunConsoleCommand, function( cmd, ... )
    if cmd == "dac_pleasebanme" or cmd == "dac_imcheating" then
        oldPrint("On "..FrostDate().." Daz Anti-Cheat tried to ban us from "..FrostGHN()..".\n")
        __f['Append']( "frost_logs.txt", "On "..FrostDate().." Daz Anti-Cheat tried to ban us from "..FrostGHN()..".\r\n" )
        return
    end
    
    return Frost.__det[RunConsoleCommand]( cmd, ... )
end )

file.ExistsEx = Frost:Detour( file.ExistsEx, function( filename, addons )
    if not filename then return end
    
    for k, file in copy['pairs']( Frost.CheatFiles ) do
        if copy['string']['find']( filename, file ) then
            oldPrint("On "..FrostDate().." "..FrostGHN().." tried to search for: "..filename..", nope!\n" )
            __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." tried to search for: "..filename..", nope!\r\n" )
            return false
        end
    end
    
    return Frost.__det[file.ExistsEx]( filename, addons )
end )

file.FindDir = Frost:Detour( file.FindDir, function( path, userbase )
    if not path then return end
    
    if copy['string']['find']( path, "*" ) then
        oldPrint("On "..FrostDate().." "..FrostGHN().." tried to request a file list, nope!\n")
        __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." tried to request a file list, nope!\r\n" )
        
        local dirtable = Frost.__det[file.FindDir]( path, userbase )
        local tabletoreturn = {}
        
        for k, dir_ in copy['pairs']( dirtable ) do
            if dir != "frost" then
                copy['table']['insert']( tabletoreturn, dir_ )
            end
        end
        
        if ( #tabletoreturn or FrostCount( tabletoreturn ) ) == 0 then
            oldPrint("On "..FrostDate().." "..FrostGHN().." asked for a table, the table returned empty.\n")
            __f['Append'].Append( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." asked for a table, the table returned empty.\r\n" )
        end
        
        return tabletoreturn
    end
    
    if copy['string']['find']( path, "frost" ) then return false end
    
    return Frost.__det[ file.FindDir ]( path, userbase )
end )

file.FindInLua = Frost:Detour( file.FindInLua, function( path, userbase )
    if not path then return end
    
    if copy['string']['find']( path, "*" ) then
        oldPrint("On "..FrostDate().." "..FrostGHN().." tried to request a file list in: "..path..", nope!\n")
        __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." tried to request a file list in: "..path..", nope!\r\n" )
            
        local filetable = Frost.__det[file.FindInLua]( path, userbase )
        local tabletoreturn = {}
            
        for k, file_ in copy['pairs']( filetable ) do
            if !copy['table']['HasValue']( Frost.CheatFiles, file_ ) then
                copy['table']['insert']( tabletoreturn, file_ )
            end
        end
        
        if ( #tabletoreturn or FrostCount( tabletoreturn ) ) == 0 then
            oldPrint("On "..FrostDate().." "..FrostGHN().." requested a table, the table returned empty.\n")
            __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." requested a table, the table returned empty.\r\n" )
        else
            oldPrint("On "..FrostDate().." "..FrostGHN().." looked in our file list, spoofed: "..copy['table']['concat'](tabletoreturn,",")..".\n")
            __f['Append']( "frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." looked in our file list, spoofed: "..copy['table']['concat'](tabletoreturn,",")..".\r\n")
        end
        
        return tabletoreturn
    end
    
    return Frost.__det[ file.FindInLua ]( path, userbase )
end )

file.Read = Frost:Detour( file.Read, function( path, userbase )
    if not path then return end
    
    if copy['string']['find']( path, "frost" ) then
        
        oldPrint("On "..FrostDate().." "..FrostGHN().." tried to read our source!\n")
        __f['Append']("frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." tried to read our source!\r\n")
        
        return "fuck you."
    end
    
    return Frost.__det[ file.Read ]( path, userbase )
end )

// file.Open = Frost:Detour( file.Open, function( name, fileMode, path )
//     if not name then return end
    
//     if string.find( name, "frost" ) then
        
//         oldPrint("On "..FrostDate().." "..FrostGHN().." tried to open our file!\n")
//         __f.Append("frost/frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." tried to read open our file!")
        
//         return
//     end
    
//     return Frost.__det[ file.Open ]( path, fileMode, path )
// end )

--[[

The above will not work with the logging system, if you want to detour file.Open you will have to remove the logging system. This will also break file.Append so any gamemodes that rely on it will break as well.

]]

file.Size = Frost:Detour( file.Open, function( path, userbase )
    if not path then return end
    
    if copy['string']['find']( path, "frost" ) then
        
        oldPrint("On "..FrostDate().." "..FrostGHN().." tried to check our file size!\n")
        __f['Append']("frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." tried to check our file size!\r\n")
        
        return -1
    end
    
    return Frost.__det[ file.Size ]( path, userbase )
end )

file.Time = Frost:Detour( file.Time, function( path, userbase )
    if not path then return end
    
    if copy['string']['find']( path, "frost" ) then
        
        oldPrint("On "..FrostDate().." "..FrostGHN().." tried to check our file's last modified date!\n")
        __f['Append']("frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." tried to check our file's last modified date!\r\n")
        
        return 0
    end
    
    return Frost.__det[ file.Time ]( path, userbase )
end )

util.RelativePathToFull = Frost:Detour( util.RelativePathToFull, function ( path )
    __f['Append']("frost_logs.txt", "On "..FrostDate().." "..FrostGHN().." tried to check our file's path!\r\n")
    return "no."
end )

_G.require = Frost:Detour( _G.require, function( module )
    oldPrint("On "..FrostDate().." we required "..module.." on "..FrostGHN().."!\n")
    __f['Append']("frost_logs.txt", "On "..FrostDate().." we required "..module.." on "..FrostGHN().."!\r\n")
    return Frost.__det[_G.require]( module )
end )

--[[

Initalize our cheat so that we have a copy of our metatables, with a copy of the metatables we can do things like aimbot and use usercmd without worrying about them being overriden.

]]

Frost:Init()

--[[

We can now start the cheat because we have a copy of our metatables, this means no one can override anything we want to use.

]]

--[[

GetHead
Purpose: It's not really used too much in the cheat besides in VisiblityChecks.

]]

local function gethead(ent)
if !__c.Entity['IsValid'](ent) then
        return
    end
    local angle_pitch = __c.Entity['EyeAngles'](ent, ent).p || 0
    if (angle_pitch > 89 or angle_pitch < -89 ) then
        local pos = __c.Entity['GetSaveTable'](ent).m_vecAbsOrigin
        pos.z = pos.z + (__c.Entity['OBBMins'](ent).z - __c.Entity['OBBMins'](ent).z * -0.55)
        return pos
    end
    if __c.Entity['GetTable'](ent).m_bInSwim == true then
        local pos = __c.Entity['GetSaveTable'](ent).m_vecAbsOrigin
        pos.z = pos.z + (__c.Entity['OBBMins'](ent).z - __c.Entity['OBBMins'](ent).z * -0.55)
        return pos
    end    
    if __c.Entity['LookupBone']( ent, "ValveBiped.Bip01_Head1") then
        local pos = __c.Entity['GetBonePosition']( ent, __c.Entity['GetHitBoxBone'](ent, 0, 0))
        return pos
    end
    return __c.Entity['LocalToWorld'](__c.Entity['OBBCenter'](ent))
end

--[[

GetBoxPos
Purpose: Get the hitboxes dynamically!

]]

local function GetBoxPos( ent, box, group )
    if !__c.Entity['IsValid'](ent) then
        return
    end
    local angle_pitch = __c.Entity['EyeAngles'](ent).p || 0
    if (angle_pitch > 89 or angle_pitch < -89 ) then
        local pos = __c.Entity['GetSaveTable'](ent).m_vecAbsOrigin
        pos.z = pos.z + (__c.Entity['OBBMins'](ent).z - __c.Entity['OBBMaxs'](ent).z * -0.55)
        return pos
    end
    if __c.Entity['GetTable'](ent).m_bInSwim == true then
        local pos = __c.Entity['GetSaveTable'](ent).m_vecAbsOrigin
        pos.z = pos.z + (__c.Entity['OBBMins'](ent).z - __c.Entity['OBBMaxs'](ent).z * -0.55)
        return pos
    end  
    local min, max = __c.Entity['GetHitBoxBounds'](ent, box, group)
     
    local mat = __c.Entity['GetBoneMatrix'](ent, __c.Entity['GetHitBoxBone'](ent, box, group))
    local pos = mat:GetTranslation()
    local box = (min + max) * 0.5
     
    box:Rotate(mat:GetAngles())
    pos = pos + box
     
    return pos
end

--[[

CanSee
Purpose: Visiblity check.

]]

local function cansee(ent)
    local me = copy['LocalPlayer']()
    
    if (__c.Entity['IsValid'](ent)) then

    local trace = {}
    trace.start = __c.Player['GetShootPos'](me)
    trace.endpos = gethead(ent)

    trace.filter = {me, ent}
    trace.mask = 1174421507
    
    local tr = util['TraceLine'](trace)
    
    return tr.Fraction == 1.0
    end
end

--[[

PredictPos
Purpose: Predict those sorry motherfuckers.

]]

local function PredictPos(ent, vec) //thanks C0BRA
    local ply = copy['LocalPlayer']()
    if(cansee(ent) && __c.Entity['IsValid'](ent)) then
    sp = __c.Player['GetShootPos'](ply) + __c.Entity['GetVelocity'](ply) * engine['TickInterval']()
    plFrames = FrostRFT() / 66 || 0
    tarFrames = FrostRFT() / 25 || 0
    plVelocity = __c.Entity['GetVelocity'](ply)  || Vecta(0, 0, 0)
     
    tarVelocity = __c.Entity['GetVelocity'](ent)  || Vecta(0, 0, 0)

    return(vec + (tarVelocity * (tarFrames) - (plVelocity * (plFrames))))  || Vecta(0, 0, 0)
    end
end

--[[

FireBullets
Purpose: Allows us to do NoSpread for some basic weapons.

]]

local CONE = {}
Frost.bullet = {}

_R.Entity.FireBullets = Frost:Detour( _R.Entity.FireBullets, function(e, bullet)
    local w = __c.Player["GetActiveWeapon"](ply)
    Frost.bullet[__c.Entity["GetClass"](w)] = bullet.Spread
    return Frost.__det[ _R.Entity.FireBullets ](e, bullet)
end)

--[[

PredictSpread
Purpose: When called in CreateMove (correctly) we can do NoSpread!

]]

local function PredictSpread(cmd, angl)
    local ply = copy['LocalPlayer']()
    local wep = __c.Player["GetActiveWeapon"](ply)
    if( wep && __c.Entity["IsValid"](wep)) then
        if( !CONE[__c.Entity['GetClass'](wep)] ) then
            if( wep.Base == "weapon_zs_base") then
                local pl = copy['LocalPlayer']()
                local velocity = (__c.Vector["Length"]( __c.Entity["GetVelocity"](pl)))
                local ConeRamp = 2
                local basecone = wep.ConeMin
                local conedelta = wep.ConeMax - basecone
                local multiplier = FrostMath.min(velocity / wep.WalkSpeed, 1) * 0.5
                if not __c.Player['KeyDown'](pl, IN_DUCK) then multiplier = multiplier + 0.25 end
                if not wep:GetIronsights() then multiplier = multiplier + 0.25 end
                local zs_mod_cone = basecone + conedelta * multiplier ^ wep.ConeRamp
                local ang = __c.Angle['Forward'](angl) || ((__c.Vector["Forward"]( __c.Vector["Angle"]( __c.Player["GetAimVector"]))))
                local conevec = Vecta(-zs_mod_cone, -zs_mod_cone, -zs_mod_cone)
                return __c.Vector['Angle'](dickwrap.Predict(cmd, ang, conevec))
            end
            if( wep.Base == "weapon_sh_base" ) then
                local pl = copy['LocalPlayer']()
                local Stance = !__c.Player['KeyDown'](pl, IN_JUMP) and __c.Player['KeyDown'](pl, IN_DUCK) and 10 -- Crouching
                or !wep.Sprinting and !__c.Player['KeyDown'](pl, IN_JUMP) and 15 --Standing
                or wep.Walking and !__c.Player['KeyDown'](pl, IN_JUMP) and 20 --Walking
                or __c.Player['KeyDown'](pl, IN_JUMP) and 25  --Flying
                or wep.Primary.Ammo == "buckshot" and 0 --Shotguns not affected
                local WepType = ( wep.Sniper && 8 || wep.SMG && 2 || wep.Pistol && 2 || wep.Primary.Ammo == "buckshot" && 0 || 1.6 )
                local sh_mod_cone = wep.Primary.Cone * wep.Primary.Recoil * Stance * WepType
                local ang = __c.Angle['Forward'](angl) || ((__c.Vector["Forward"]( __c.Vector["Angle"]( __c.Player["GetAimVector"]))))
                local conevec = Vecta(-sh_mod_cone, -sh_mod_cone, -sh_mod_cone)
                return __c.Vector['Angle'](dickwrap.Predict(cmd, ang, conevec))
            end
            if( wep.Base == "weapon_cs_base" ) then
                local pl = copy['LocalPlayer']()
                local wep_mod_cone = wep.Primary.Cone
                local ang = __c.Angle['Forward'](angl) || ((__c.Vector["Forward"]( __c.Vector["Angle"]( __c.Player["GetAimVector"]))))
                local conevec = Vecta(-wep_mod_cone, -wep_mod_cone, -wep_mod_cone)
                return __c.Vector['Angle'](dickwrap.Predict( cmd, ang, conevec))
            end
            if(wep.Base == "weapon_mad_base") then
                local pl = copy['LocalPlayer']()
                if __c.Player['KeyDown'](pl, IN_ATTACK2) then
                    wep_mod_cone = wep.Primary.Cone * wep.data.Cone
                else
                    wep_mod_cone = wep.Primary.Cone
                end
                local ang = __c.Angle['Forward'](angl) || ((__c.Vector["Forward"]( __c.Vector["Angle"]( __c.Player["GetAimVector"]))))
                local conevec = Vecta(-wep_mod_cone, -wep_mod_cone, -wep_mod_cone)
                return __c.Vector['Angle'](dickwrap.Predict(cmd, ang, conevec))
            end
            if( wep.Base == "bobs_gun_base" ) then
                local pl = copy['LocalPlayer']()
                if __c.Player['KeyDown'](pl, IN_ATTACK2) then
                    wep_mod_cone = wep.Primary.IronAccuracy
                else
                    wep_mod_cone = wep.Primary.Spread
                end
                local ang = __c.Angle['Forward'](angl) || ((__c.Vector["Forward"]( __c.Vector["Angle"]( __c.Player["GetAimVector"]))))
                local conevec = Vecta(-wep_mod_cone, -wep_mod_cone, -wep_mod_cone)
                return __c.Vector['Angle'](dickwrap.Predict(cmd, ang, conevec))
            end
            if( Frost.bullet[__c.Entity['GetClass'](wep)] ) then
                local ang = __c.Angle['Forward'](angl) || ((__c.Vector["Forward"]( __c.Vector["Angle"]( __c.Player["GetAimVector"]))))
                local conevec = Vecta(0, 0, 0) - BULLET[__c.Entity['GetClass'](wep)] || Vecta(0, 0, 0)
                return __c.Vector['Angle'](dickwrap.Predict(cmd, ang, conevec))
            end
        else
            ang = __c.Angle['Forward'](angl) || ((__c.Vector["Forward"]( __c.Vector["Angle"]( __c.Player["GetAimVector"]))))
            conevec = CONE[__c.Entity['GetClass'](wep)]
            return __c.Vector['Angle'](dickwrap.Predict(cmd, ang, conevec))
        end
    end
    return angl
end

--[[

IsValidEntity
Purpose: Checks if the entity is valid for our targetting system.

]]

local function IsValidEntity(ent)
    if( ent == nil ) then return false end
    if(__c.Entity['IsValid'](ent) == false) then 
        return false
    end
    if(__c.Entity['GetMoveType'](ent) == MOVETYPE_NONE) then 
        return false 
    end
    if(__c.Entity['IsPlayer']) then
        if(cansee(ent)) then
            if(__c.Player['Alive'](ent) == false) then 
                return false 
            end
            if(__c.Entity['Health'](ent) <= 0) then 
                return false 
            end
            if (__c.Player['GetFriendStatus'](ent) == "friend") then
                return false
            end
            if(__c.Player['InVehicle'](ent)) then 
                return false 
            end
        end
    end
    if(__c.Entity['IsNPC']) then
        return true
    end
    return false
end

--[[

Target
Purpose: Runs in Think, this means it won't loop through the entire entity list every tick, it saves us FPS.

]]

function Frost.Target()
    local ply = copy['LocalPlayer']()
    if !FrostInput['IsKeyDown'](KEY_B) then
        Frost['__targ'] = nil
    end
    if FrostInput['IsKeyDown'](KEY_B) then
        Frost['__targ'] = nil
        for k, v in next, copy['player']['GetAll']() do
            if(v != ply) then
                if(cansee(v)) then
                    if(IsValidEntity(v)) then
                        Frost['__targ'] = v
                    end
                end
            end
        end
    end
end

--[[

Autoshoot
Purpose: Allows us to use the correct CurTime() (predicted one) to check if the current time is greater than the last fire time...and...fires.

]]

local lastshoot = 0

local function autoshoot(ucmd) //thanks fr1kin
    if(RealCurTime() > lastshoot) then
        lastshoot = RealCurTime() + 0.03
        ucmd:SetButtons(bit.bor(ucmd:GetButtons(), IN_ATTACK)) // change to use metatable later
    end
end

--[[

Aimbot
Purpose: Aims for you, either because you suck too much or you're fat and lazy.

]]

function Frost.Aimbot(cmd)
    if(FrostVgui['CursorVisible']() == true) then
        return
    end
    if !FrostInput['IsKeyDown'](KEY_B) then
        Frost['__targ'] = nil
    end
    if FrostInput['IsKeyDown'](KEY_B) then
        local ply = copy['LocalPlayer']()

            if (Frost['__targ'] == ply) then
                return
            end

            if(!__c.Entity['IsValid'](Frost['__targ'])) then
                return
            end

            if(__c.Entity['Health'](Frost['__targ'])) <= 0 then
                return
            end
        
        if cansee(Frost['__targ']) then
            local angle = GetBoxPos(Frost['__targ'], 0, HITGROUP_GENERIC)
            angle = PredictPos(Frost['__targ'], angle)
            angle = __c.Vector['Angle'](angle - sp)
            angle.p = FrostMath['NormalizeAngle'](angle.p)
            angle.y = FrostMath['NormalizeAngle'](angle.y)
            angle = PredictSpread(cmd, angle)
            angle.p = FrostMath['NormalizeAngle'](angle.p)
            angle.y = FrostMath['NormalizeAngle'](angle.y)
            __c.CUserCmd['SetViewAngles'](cmd, angle)
            autoshoot(cmd)
            end
        end
    end

--[[

ESP
Purpose: Draws an ESP over the players because you suck and need to see them through walls.

]]

function Frost.HUDPaint()
    for k, v in copy['pairs'](copy['player']['GetAll']()) do
        local ply = copy['LocalPlayer']()
        if __c.Player['Alive'](v) && __c.Entity['Health'](v) > 0 && v != ply then
            local col       = FrostTeam['GetColor'](__c.Player['Team'](v))
            local om        = (__c.Entity['GetPos'](v) + Vecta(0, 0, 20))
            local nom       = (__c.Entity['GetPos'](v) + Vecta(0, 0, 50))
            local bottom    = (__c.Vector['ToScreen'](om))
            local toppom    = (__c.Vector['ToScreen'](nom))
            local height    = (bottom['y'] - toppom['y'])
            local width     = (height / 2)
        
            copy['surface']['SetDrawColor'](col)
            copy['surface']['DrawOutlinedRect'](toppom['x'] - width, toppom['y'], width * 2, height)

            copy['surface']['SetDrawColor'](0, 0, 0, 255)
            copy['surface']['DrawOutlinedRect'](toppom['x'] - width - 1, toppom['y'] - 1, width * 2 + 2, height + 2)
            copy['surface']['DrawOutlinedRect'](toppom['x'] - width + 1, toppom['y'] + 1, width * 2 - 2, height - 2)
        end
    end
end

function Frost.RenderScreenspaceEffects() //XQZ from Herpes v3, i think it looks ugly but if you want to use it uncomment the RenderScreenspaceEffects hook
    FrostCa.Start3D(copy['EyePos'](), copy['EyeAngles']())
    for k, v in copy['pairs'](copy['player']['GetAll']()) do
        if(!v) then continue end
        if(v == pl) then continue end
        if(!__c.Player['Alive'](v)) then continue end
        
        FrostCa.IgnoreZ(true)
        FrostRen.SuppressEngineLighting(true)
        __c.Entity['DrawModel'](v)
        FrostCa.IgnoreZ(false)
        FrostRen.SuppressEngineLighting(false)
    end
    FrostCa.End3D()
end

--[[

Hooks
Purpose: Allows us to run hooks, would detour hook.Call but it's not possible anymore because Garry localizes it and only calls it when a hook is modified.

]]

hook.Add("CreateMove", "hii", Frost.Aimbot)
hook.Add("Think", "hii2", Frost.Target)
hook.Add("HUDPaint", "hii3", Frost.HUDPaint)
//hook.Add("RenderScreenspaceEffects", "hii4", Frost.RenderScreenspaceEffects)