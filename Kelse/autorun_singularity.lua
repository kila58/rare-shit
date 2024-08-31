/*
	Singularity by Daz
	Thanks to:
	Frost
	Atomic
	Keegan
*/

--Localization--
local copy = table.Copy

local _render 		= copy(render)
local _draw			= copy(draw)
local _surface 		= copy(surface)
local _hook			= copy(hook)
local _concommand	= copy(concommand)
local _player		= copy(player)
local _ent			= copy(ents)
local _timer		= copy(timer)
local _util 		= copy(util)
local _debug		= copy(debug)
local _math			= copy(math)
local _engine		= copy(engine)
local _vgui			= copy(vgui)
local _gui			= copy(gui)
local _input		= copy(input)
local G 			= copy(_G)
local _R 			= copy(debug.getregistry())
local _chatprint 	= copy(chat.AddText())
local build = 58


--Convars--
//NOTHING, WOO

--Fonts--
surface.CreateFont("DefaultSmallDropShadow", {
		font	= "Tahoma",
		size	= 16,
		weight	= 500,
		shadow	= true,
	}
)	

--Looking up the hitbox--

local function gethead(ent)
	local angle_pitch = ent:EyeAngles(ent).p
	if (angle_pitch > 89 or angle_pitch < -89 ) then
		local pos = ent:GetSaveTable().m_vecAbsOrigin
		pos.z = pos.z + (ent.OBBMins(ent).z - ent.OBBMaxs(ent).z) * -0.55
		return pos
	end
	if ent:GetTable().m_bInSwim == true then
		local pos = ent:GetSaveTable().m_vecAbsOrigin
		pos.z = pos.z + (ent.OBBMins(ent).z - ent.OBBMaxs(ent).z) * -0.55
		return pos
	end
	if ent:LookupBone("ValveBiped.Bip01_Head1") then
	local pos = ent:GetBonePosition(ent:GetHitBoxBone(0,0))
		return pos
	end
return ent:LocalToWorld(ent:OBBCenter())
end

--ESP, Crosshair, Watermark--
--using the same function to save from using another hook--

local function Crosshair()
// surface.SetDrawColor(255,0,0,255)
// surface.DrawLine(ScrW()/2, ScrH()/2, ScrW()/2 + 10, ScrH()/2)
// surface.DrawLine(ScrW()/2 , ScrH()/2, ScrW()/2 - 10, ScrH()/2)
// surface.DrawLine(ScrW()/2, ScrH()/2, ScrW()/2, ScrH()/2 - 10)
// surface.DrawLine(ScrW()/2, ScrH()/2, ScrW()/2, ScrH()/2 + 10)
// surface.SetDrawColor(0,0,0,255)
// surface.DrawLine(ScrW()/2, ScrH()/2 + 10, ScrW()/2 - 10, ScrH()/2 + 10)
// surface.DrawLine(ScrW()/2, ScrH()/2 + 10, ScrW()/2 + 11, ScrH()/2 + 10)
// surface.DrawLine(ScrW()/2, ScrH()/2 - 10, ScrW()/2 - 10, ScrH()/2 - 10)
// surface.DrawLine(ScrW()/2 + 10, ScrH()/2, ScrW()/2 + 10, ScrH()/2 - 10)
// surface.DrawLine(ScrW()/2 - 10, ScrH()/2, ScrW()/2 - 10, ScrH()/2 + 10)
// surface.DrawLine(ScrW()/2, ScrH()/2 - 10, ScrW()/2 + 10, ScrH()/2 - 10)
// surface.DrawLine(ScrW()/2 - 10 , ScrH()/2, ScrW()/2 - 10, ScrH()/2 - 10)
// surface.DrawLine(ScrW()/2 + 10, ScrH()/2, ScrW()/2 + 10, ScrH()/2 + 10)
for k,v in pairs(player.GetAll()) do
		if v:Alive() && v:IsValid() && v != LocalPlayer() then
			local one = v:GetPos()+Vector(0,0,v:OBBMaxs().z)
			local two = one:ToScreen()
			draw.SimpleText(v:Nick().."["..v:Health().."]","BudgetLabel",two.x,two.y,team.GetColor(v),1)
		end
	end
draw.SimpleText("Singularity Build "..build.."", "DefaultSmallDropShadow", ScrH() / 16,ScrW() / 170, Color(0,255,225), 1, 1 )
end

--Awful prediction--

local function examplepred(pos, ent)
	return pos + ent:GetVelocity() / 66 - LocalPlayer():GetVelocity() / 66 -- sucks, change it
end 

--Norecoil for HL2 weps--

local function simplenorecoil(ucmd)
	local wep = LocalPlayer():GetActiveWeapon()
		if LocalPlayer():GetActiveWeapon().Primary then
		if( wep:GetClass() == "weapon_pistol" or wep:GetClass() == "weapon_ar2" or wep:GetClass() == "weapon_357" or wep:GetClass() == "weapon_smg1" or wep:GetClass() == "weapon_shotgun") then
		local angle = _R.CUserCmd.GetViewAngles( ucmd ) - LocalPlayer():GetPunchAngle( ply );
		_R.CUserCmd.SetViewAngles( ucmd, angle );
		end
	end
end

--Vis Check--

local function cansee(ent)
	local me = LocalPlayer()
	
	local trace = {}
    trace.start = me:GetShootPos()
	trace.endpos = gethead(ent)

    trace.filter = {me, ent}
    trace.mask = 1174421507
	
    local tr = _util.TraceLine(trace)
	
	return tr.Fraction == 1.0
end

--Nospread start--

--Nospread end--

local function aimbot(ucmd)
	if( vgui.CursorVisible() == true ) then
		return;
	end
	if _input.IsKeyDown(KEY_B) or aim == true then
		local ply = LocalPlayer()
		for k, ent in next, _player.GetAll() do
		
		if (!IsValid(ent)) then
			continue
		end
		
		if (ent:InVehicle()) then
			continue
		end

		if (ent == LocalPlayer()) then
			continue
		end
		
		if (!ent:Alive()) then
			continue
		end

		if(ent:IsNPC()) then
			continue
		end

		if(ent:Team() == TEAM_SPECTATOR) then
			continue
		end
		
		if (ent:GetFriendStatus() == "friend") then
			continue
		end
		
			if cansee(ent) then
		
			local angle = (gethead(ent) - LocalPlayer():GetShootPos()):Angle()
			angle.p = _math.NormalizeAngle(angle.p)
			angle.y = _math.NormalizeAngle(angle.y)
			ucmd:SetViewAngles(angle)
			ucmd:SetButtons(bit.bor(ucmd:GetButtons(), IN_ATTACK ))
			end
		end
	end
end

--Target camera--

local function camidea() //readd when lasers are fixed?
	if( vgui.CursorVisible() == true ) then
		return
	end
	if _input.IsKeyDown(KEY_B) then
	for k, v in pairs(player.GetAll()) do
	if v != LocalPlayer() then
	if cansee(v) then
	local camidea = {}
	camidea.angles = Angle(v:EyeAngles().pitch,v:EyeAngles().yaw,v:EyeAngles().roll)
	camidea.origin = gethead(v)
	camidea.x = 0
	camidea.y = 0
	camidea.w = ScrW() / 3
	camidea.h = ScrH() / 3
	--v:SetNoDraw(true)
	LocalPlayer():GetViewModel():SetNoDraw(true)
	render.RenderView( camidea )
	LocalPlayer():GetViewModel():SetNoDraw(false)
	v:SetNoDraw(false)
				end
			end
		end
	end
end

--L4D-esque wallhack--

local function wallhack() //thank you based cobalt
    for k, v in next, player.GetAll() do
        local color
		local hp = v:Health()
		if v:Alive() && v:IsValid() && v:Health() > 0 then
		if hp < 10 then
			color = Color( 200, 0, 0 )
		elseif hp >= 10 and hp < 20 then
			color = Color( 180, 20, 0 )
		elseif hp >= 20 and hp < 30 then
			color = Color( 160, 40, 0 )
		elseif hp >= 30 and hp < 40 then
			color = Color( 140, 6, 0 )
		elseif hp >= 40 and hp < 50 then
			color = Color( 120, 80, 0 )
		elseif hp >= 50 and hp < 60 then
			color = Color( 100, 100, 0 )
		elseif hp >= 60 and hp < 70 then
			color = Color( 80, 120, 0 )
		elseif hp >= 70 and hp < 80 then
			color = Color( 60, 140, 0 )
		elseif hp >= 80 and hp < 90 then
			color = Color( 40, 160, 0 )
		elseif hp >= 90 and hp < 100 then
			color = Color( 20, 180, 0 )
		elseif hp == 100 then
			color = Color( 0, 200, 0 )
		else
			color = team.GetColor( v:Team() )
		end
        halo.Add( { v }, color, 5, 5, 2, true, true )
    	end
	end
end

local function drawbox()
	cam.Start3D(EyePos(), EyeAngles())
	for k, v in pairs(player.GetAll()) do
		if v:IsValid() and v:Alive() and v != LocalPlayer() then
		local pos, eyeang = v:GetPos(), Angle()
		local min, max = v:OBBMaxs(), v:OBBMins()
		render.DrawWireframeBox(pos, eyeang, min, max, team.GetColor(v:Team()), true)
	   end
    end
	cam.End3D()
end

--Drawing barrel from the weapon--

local function barrel()
    local model = LocalPlayer():GetViewModel()
    local attachment = model:LookupAttachment("1")
    if model and IsValid(LocalPlayer():GetActiveWeapon()) then
        if (LocalPlayer():GetActiveWeapon():GetClass() == "weapon_frag" or LocalPlayer():GetActiveWeapon():GetClass() == "gmod_camera" or LocalPlayer():GetActiveWeapon():GetClass() == "keys" or LocalPlayer():GetActiveWeapon():GetClass() == "pocket" or LocalPlayer():GetActiveWeapon():GetClass() == "weapon_ttt_confgrenade" or LocalPlayer():GetActiveWeapon():GetClass() == "weapon_zm_molotov" or LocalPlayer():GetActiveWeapon():GetClass() == "weapon_real_cs_knife" or LocalPlayer():GetActiveWeapon():GetClass() == "weapon_madcow_knife" or LocalPlayer():GetActiveWeapon():GetClass() == "weapon_knife" or LocalPlayer():GetActiveWeapon():GetClass() == "med_kit" or LocalPlayer():GetActiveWeapon():GetClass() == "cw_keys" or LocalPlayer():GetActiveWeapon():GetClass() == "cw_hands" or LocalPlayer():GetActiveWeapon():GetClass() == "nut_keys" or LocalPlayer():GetActiveWeapon():GetClass() == "nut_fists" or LocalPlayer():GetActiveWeapon():GetClass() == "srp_scrap" or LocalPlayer():GetActiveWeapon():GetClass() == "srp_bolt" or LocalPlayer():GetActiveWeapon():GetClass() == "scrap" or LocalPlayer():GetActiveWeapon():GetClass() == "bolt" or LocalPlayer():GetActiveWeapon():GetClass() == "dayz_hands") then return end
        if model:LookupAttachment("1") == 0 then model:LookupAttachment("muzzle") end
            cam.Start3D(EyePos(),EyeAngles())
            render.SetMaterial(Material("sprites/bluelaser1"))
            render.DrawBeam(model:GetAttachment("1").Pos,LocalPlayer():GetEyeTrace().HitPos,3,0,0,Color(255,255,255))
            render.SetMaterial(Material("Sprites/light_glow02_add_noz"))
            render.DrawQuadEasy(LocalPlayer():GetEyeTrace().HitPos, LocalPlayer():EyePos() - LocalPlayer():GetEyeTrace().HitPos, 25, 25, Color(255,255,255))
            cam.End3D()
        end
    end

--Awful bunnyhop--

local function bunnyhop(ucmd)
	if bit.band(ucmd:GetButtons(), IN_JUMP) ~= 0 then
		if !LocalPlayer():IsOnGround()
			then
			ucmd:SetButtons(bit.band(ucmd:GetButtons(), bit.bnot(IN_JUMP)))
		end
	end
end

--NutScript item ESP--

local function nutscriptesp()
    for k,v in ipairs(ents.FindByClass("nut_item")) do
        if v then
            local item = v:GetItemTable()
            if item then
    local pos = v:LocalToWorld(v:OBBCenter()):ToScreen()
    local text = (item.name or "unknown")
    surface.SetFont("DefaultSmallDropShadow")
    local width,height = surface.GetTextSize(text)
    surface.SetTextPos(pos.x - width / 2, pos.y - height)
    surface.SetTextColor(Color(255,255,255,255))
    surface.DrawText(text)
                end
            end
        end
    end

--TacoScript item ESP--

local function tacoscript2esp()
    for k,v in ipairs(ents.FindByClass("ts2_item")) do
        if v then
            local item = v:GetTable().ItemName
            if item then
    local pos = v:LocalToWorld(v:OBBCenter()):ToScreen()
    local text = (item.name or "unknown")
    surface.SetFont("DefaultSmallDropShadow")
    local width,height = surface.GetTextSize(text)
    surface.SetTextPos(pos.x - width / 2, pos.y - height)
    surface.SetTextColor(Color(255,255,255,255))
    surface.DrawText(text)
                end
            end
        end
    end

--Madwombat's server anom esp thingy--

local function anomesp() // fucking gmod fucks up if i do something else, so i'm doing it this way, forgive me.
	        for k, v in pairs(ents.GetAll()) do 
               if v:GetClass() == "anom_burner" then
                        local pos1 = v:GetPos() + Vector(10, 0, 0);
                        local pos2 = (pos1 + Vector(0, 0, 5)):ToScreen();
                        draw.SimpleText("Burner", 'DefaultSmallDropShadow', pos2.x, pos2.y, Color(255, 0, 0, 255), 1, 1, 1)
                end
                if v:GetClass() == "anom_bubble" then
                        local pos1 = v:GetPos() + Vector(10, 0, 0);
                        local pos2 = (pos1 + Vector(0, 0, 5)):ToScreen();
                        draw.SimpleText("Bubble", 'DefaultSmallDropShadow', pos2.x, pos2.y, Color(0, 255, 255, 255), 1, 1, 1)
                end
                if v:GetClass() == "anom_whirlgig" then
                        local pos1 = v:GetPos() + Vector(10, 0, 0);
                        local pos2 = (pos1 + Vector(0, 0, 5)):ToScreen();
                        draw.SimpleText("Whirlgig", 'DefaultSmallDropShadow', pos2.x, pos2.y, Color(0, 255, 0, 255), 1, 1, 1)
                end
                if v:GetClass() == "anom_damage" then
                        local pos1 = v:GetPos() + Vector(10, 0, 0);
                        local pos2 = (pos1 + Vector(0, 0, 5)):ToScreen();
                        draw.SimpleText("Radiation", 'DefaultSmallDropShadow', pos2.x, pos2.y, Color(255, 0, 0, 255), 1, 1, 1)
                end
                if v:GetClass() == "anom_electro" then
                        local pos1 = v:GetPos() + Vector(10, 0, 0);
                        local pos2 = (pos1 + Vector(0, 0, 5)):ToScreen();
                        draw.SimpleText("Electro", 'DefaultSmallDropShadow', pos2.x, pos2.y, Color(0, 255, 255, 255), 1, 1, 1)
                end
                if v:GetClass() == "anom_vortex" then
                        local pos1 = v:GetPos() + Vector(10, 0, 0);
                        local pos2 = (pos1 + Vector(0, 0, 5)):ToScreen();
                        draw.SimpleText("Vortex", 'DefaultSmallDropShadow', pos2.x, pos2.y, Color(0, 200, 255, 255), 1, 1, 1)
                end
		end
end

local function gayesp()
    for k,v in ipairs(ents.FindByClass("dz_item")) do
        if v then
    local text = ("Some Item")
    local pos = v:LocalToWorld(v:OBBCenter()):ToScreen()
    surface.SetFont("DefaultSmallDropShadow")
    local width,height = surface.GetTextSize(text)
    surface.SetTextPos(pos.x - width / 2, pos.y - height)
    surface.SetTextColor(Color(255,255,255,255))
    surface.DrawText(text)
        end
	end
end

hook.Add("HUDPaint","ASDASDADAS",Crosshair)
hook.Add("CreateMove","new",simplenorecoil)
hook.Add("CreateMove","yes",aimbot)
hook.Add("CreateMove","yes6",propkillaimbot)
--hook.Add("HUDPaint","aisdijsad",camidea)
hook.Add("CreateMove","teaisdjf",bunnyhop)
--hook.Add("PreDrawHalos","yes2",wallhack)
hook.Add("HUDPaint","idk",barrel)
hook.Add("HUDPaint","idkroflmao3",drawbox)