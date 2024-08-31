//This was a compilation between Captain Gooby and myself (Daz is writing this) Gooby did the dermas whilst I did the aimbot and other stuff, I used a lot of code from
//Fr1kin, it's not great but it was for fun. Enjoy.

local __package = package
local __table = table

if not __package.loaded.coldfirev2 then 
    require("coldfirev2") 
    MsgC(Color(116, 187, 251),'\n[Coldfire V2] - Module not yet required, requiring.\n') 
end

local lasercolor = nil

local ESPFeatures = {
    {HackName = "Crosshair", VariableName = "CRESHAIRLEL"},
    {HackName = "Laser Sights", VariableName = "LASERSIGHTLEL"},
    {HackName = "Bounding Boxes", VariableName = "EHESPE"},
    {HackName = "Skeleton", VariableName = "SKELETONLEL"},
    {HackName = "Chams", VariableName = "CHEMS"},
    {HackName = "Laser Eyes", VariableName = "LASEREYESLEL"},
}

local AimFeatures = {
    {HackName = "Aimbot", VariableName = "AIMBATLEL"},
    {HackName = "Triggerbot", VariableName = "TRIGGERBETLEL"},
    {HackName = "Target Friends", VariableName = "TARGETFRIENDS"},
    {HackName = "NoSpread", VariableName = "NOSPREADLEL"},
    {HackName = "NoSpread on Fire", VariableName = "NoSpreadOnFire"},
    {HackName = "NoShake", VariableName = "NoVisualRecoil"},
}

for k,v in pairs(ESPFeatures) do
    CreateClientConVar(v.VariableName, 0)
end

for k,v in pairs(AimFeatures) do
    CreateClientConVar(v.VariableName, 0)
end

local skeleton = {
    { S = "ValveBiped.Bip01_Head1", E = "ValveBiped.Bip01_Neck1" },
    { S = "ValveBiped.Bip01_Neck1", E = "ValveBiped.Bip01_Spine4" },
    { S = "ValveBiped.Bip01_Spine4", E = "ValveBiped.Bip01_Spine2" },
    { S = "ValveBiped.Bip01_Spine2", E = "ValveBiped.Bip01_Spine1" },
    { S = "ValveBiped.Bip01_Spine1", E = "ValveBiped.Bip01_Spine" },
    { S = "ValveBiped.Bip01_Spine", E = "ValveBiped.Bip01_Pelvis" },
 
    { S = "ValveBiped.Bip01_Spine2", E = "ValveBiped.Bip01_L_UpperArm" },
    { S = "ValveBiped.Bip01_L_UpperArm", E = "ValveBiped.Bip01_L_Forearm" },
    { S = "ValveBiped.Bip01_L_Forearm", E = "ValveBiped.Bip01_L_Hand" },
 
    { S = "ValveBiped.Bip01_Spine2", E = "ValveBiped.Bip01_R_UpperArm" },
    { S = "ValveBiped.Bip01_R_UpperArm", E = "ValveBiped.Bip01_R_Forearm" },
    { S = "ValveBiped.Bip01_R_Forearm", E = "ValveBiped.Bip01_R_Hand" },
 
    { S = "ValveBiped.Bip01_Pelvis", E = "ValveBiped.Bip01_L_Thigh" },
    { S = "ValveBiped.Bip01_L_Thigh", E = "ValveBiped.Bip01_L_Calf" },
    { S = "ValveBiped.Bip01_L_Calf", E = "ValveBiped.Bip01_L_Foot" },
    { S = "ValveBiped.Bip01_L_Foot", E = "ValveBiped.Bip01_L_Toe0" },
       
    { S = "ValveBiped.Bip01_Pelvis", E = "ValveBiped.Bip01_R_Thigh" },
    { S = "ValveBiped.Bip01_R_Thigh", E = "ValveBiped.Bip01_R_Calf" },
    { S = "ValveBiped.Bip01_R_Calf", E = "ValveBiped.Bip01_R_Foot" },
    { S = "ValveBiped.Bip01_R_Foot", E = "ValveBiped.Bip01_R_Toe0" },
}

local noobhitbox = {
    ["models/alyx_ep2.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/headcrabblack.mdl"] = {
            ["default"] = 0;
            ["center"] = 0;
            ["upper"] = 0;
            ["lower"] = 0;
    },
    ["models/headcrabclassic.mdl"] = {
            ["default"] = 0;
            ["center"] = 0;
            ["upper"] = 0;
            ["lower"] = 0;
    },
    ["models/Hunter.mdl"] = {
            ["default"] = 0;
            ["center"] = 0;
            ["upper"] = 0;
            ["lower"] = 0;
    },
    
    ["models/pigeon.mdl"] = {
            ["default"] = 0;
            ["center"] = 0;
            ["upper"] = 0;
            ["lower"] = 0;
    },
    ["models/PLAYER.mdl"] = {
            ["default"] = 20;
            ["center"] = 0;
            ["upper"] = 3;
            ["lower"] = 1;
    },
    
    ["models/Seagull.mdl"] = {
            ["default"] = 0;
            ["center"] = 0;
            ["upper"] = 0;
            ["lower"] = 0;
    },
    
    ["models/vortigaunt.mdl"] = {
            ["default"] = 14;
            ["center"] = 0;
            ["upper"] = 12;
            ["lower"] = 11;
    },
    ["models/vortigaunt_slave.mdl"] = {
            ["default"] = 14;
            ["center"] = 0;
            ["upper"] = 13;
            ["lower"] = 11;
    },
    ["models/player/Group01/Female_01.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group01/Female_02.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group01/Female_03.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group01/Female_04.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group01/Female_06.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group01/Female_07.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group01/Male_01.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group01/male_02.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group01/male_03.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group01/Male_04.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group01/Male_05.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group01/male_06.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group01/male_07.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group01/male_08.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group01/male_09.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/Female_01.mdl"] = {
            ["default"] = 6;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group03/Female_02.mdl"] = {
            ["default"] = 6;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group03/Female_03.mdl"] = {
            ["default"] = 6;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group03/Female_04.mdl"] = {
            ["default"] = 6;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group03/Female_06.mdl"] = {
            ["default"] = 6;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group03/Female_07.mdl"] = {
            ["default"] = 6;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/Group03/Male_01.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/male_02.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/male_03.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/Male_04.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/Male_05.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/male_06.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/male_07.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/male_08.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Group03/male_09.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Hostage/Hostage_01.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Hostage/Hostage_02.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Hostage/hostage_03.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Hostage/hostage_04.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/alyx.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/arctic.mdl"] = {
            ["default"] = 1;
            ["center"] = 16;
            ["upper"] = 17;
            ["lower"] = 0;
    },
    ["models/player/arctic.mdl"] = {
            ["default"] = 1;
            ["center"] = 16;
            ["upper"] = 17;
            ["lower"] = 0;
    },
    ["models/player/barney.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/breen.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/charple01.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/classic.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/combie_soldier.mdl"] = {
            ["default"] = 1;
            ["center"] = 0;
            ["upper"] = 17;
            ["lower"] = 17;
    },
    ["models/player/combine_soldier_prisonguard.mdl"] = {
            ["default"] = 1;
            ["center"] = 16;
            ["upper"] = 17;
            ["lower"] = 17;
    },
    ["models/player/combine_super_soldier.mdl"] = {
            ["default"] = 1;
            ["center"] = 0;
            ["upper"] = 17;
            ["lower"] = 17;
    },
    ["models/player/corpse1.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/dod_american.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/dod_german.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/eli.mdl"] = {
            ["default"] = 0;
            ["center"] = 13;
            ["upper"] = 14;
            ["lower"] = 14;
    },
    ["models/player/gasmask.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/gman_high.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/guerilla.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Kleiner.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/leet.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/magnusson.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/monk.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/mossman.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 17;
            ["lower"] = 16;
    },
    ["models/player/dod_american.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/odessa.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/Phoenix.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/police.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/riot.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/soldier_stripped.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/swat.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/urban.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/zombie_soldier.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ["models/player/zombiefast.mdl"] = {
            ["default"] = 0;
            ["center"] = 15;
            ["upper"] = 16;
            ["lower"] = 16;
    },
    ['models/codmw2/codmw2h.mdl'] = {
            ["default"] = 12
    },
    ['models/codmw2/codmw2he.mdl'] = {
            ["default"] = 12
    },
    ['models/codmw2/codmw2hexe.mdl'] = {
            ["default"] = 12
    },
    ['models/codmw2/codmw2m.mdl'] = {
            ["default"] = 12
    },
    ['models/codmw2/t_codm.mdl'] = {
            ["default"] = 12
    },
    ['models/codmw2/t_codmw2.mdl'] = {
            ["default"] = 12
    },
    ['models/codmw2/t_codmw2h.mdl'] = {
            ["default"] = 12
    },
    ['models/player/kleiner.mdl'] = {
    ["default"] = 0
    },
    ['models/player/arctic.mdl'] = {
    ['default'] = 0
    },
}

local COLDFIRE = {}

local function chamsmat()
    local BaseInfo = {
        ["$basetexture"] = "models/debug/debugwhite",
        ["$ignorez"]     = 1
    }
   local mat = CreateMaterial( "coldfire", "VertexLitGeneric", BaseInfo )
   return mat
end

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

local function VisibleCheck( person )
    if !IsValid(person) then return end

    local visiblechecks = {
        start = LocalPlayer():GetShootPos(),
        endpos = gethead(person),
        filter = {person, LocalPlayer()}
    }

    local trace = util.TraceLine( visiblechecks )

    if trace.Fraction == 1 then
        return true
    end

    return false
end

local function GetBoxPos( ent, box, group )
    if !IsValid(ent) then
        return
    end
    local angle_pitch = ent:EyeAngles().p || 0;
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
    local min, max = ent:GetHitBoxBounds( box, group )
     
    local mat = ent:GetBoneMatrix( ent:GetHitBoxBone( box, group ) )
    local pos = mat:GetTranslation()
    local box = ( min + max ) * 0.5
     
    box:Rotate( mat:GetAngles() )
    pos = pos + box
     
    return pos
end

local CONE = {}

local _R = _G.debug.getregistry();

local BULLET = {};

local oldBullets = _R.Entity.FireBullets;

function _R.Entity.FireBullets( ent, bulletinfo )
    local wep = _G.LocalPlayer():GetActiveWeapon();
    BULLET[wep:GetClass()] = bulletinfo.Spread;
    return oldBullets( ent, bulletinfo );
end

local function PredictSpread( ucmd, angl )
    local wep = _G.LocalPlayer():GetActiveWeapon();
    if( wep && _G.IsValid( wep ) ) then
        if( !CONE[wep:GetClass()] ) then
            if( wep.Base == "weapon_zs_base") then
                local ConeRamp = 2
                local basecone = wep.ConeMin
                local conedelta = wep.ConeMax - basecone
                local multiplier = math.min(LocalPlayer():GetVelocity():Length() / wep.WalkSpeed, 1) * 0.5
                if not LocalPlayer():Crouching() then multiplier = multiplier + 0.25 end
                if not wep:GetIronsights() then multiplier = multiplier + 0.25 end
                local zs_mod_cone = basecone + conedelta * multiplier ^ wep.ConeRamp
                local ang = angl:Forward() || ( ( _G.LocalPlayer():GetAimVector() ):Angle() ):Forward();
                local conevec = Vector( -zs_mod_cone, -zs_mod_cone, -zs_mod_cone )
                return( coldfirev2.Predict( ucmd, ang, conevec ) ):Angle();
            end
            if( wep.Base == "weapon_sh_base" ) then
                local Stance = LocalPlayer():IsOnGround() and LocalPlayer():Crouching() and 10 -- Crouching
                or !wep.Sprinting and LocalPlayer():IsOnGround() and 15 --Standing
                or wep.Walking and LocalPlayer():IsOnGround() and 20 --Walking
                or !LocalPlayer():IsOnGround() and 25  --Flying
                or wep.Primary.Ammo == "buckshot" and 0 --Shotguns not affected
                local WepType = ( wep.Sniper && 8 || wep.SMG && 2 || wep.Pistol && 2 || wep.Primary.Ammo == "buckshot" && 0 || 1.6 )
                local sh_mod_cone = wep.Primary.Cone * wep.Primary.Recoil * Stance * WepType
                local ang = angl:Forward() || ( ( _G.LocalPlayer():GetAimVector() ):Angle() ):Forward();
                local conevec = Vector( -sh_mod_cone, -sh_mod_cone, -sh_mod_cone )
                return( coldfirev2.Predict( ucmd, ang, conevec ) ):Angle();
            end
            if( wep.Base == "weapon_cs_base" ) then
                local wep_mod_cone = wep.Primary.Cone
                local ang = angl:Forward() || ( ( _G.LocalPlayer():GetAimVector() ):Angle() ):Forward();
                local conevec = Vector( -wep_mod_cone, -wep_mod_cone, -wep_mod_cone )
                return( coldfirev2.Predict( ucmd, ang, conevec ) ):Angle();
            end
            if( wep.Base == "bobs_gun_base" ) then
                if LocalPlayer():KeyDown(IN_ATTACK2) then
                    wep_mod_cone = wep.Primary.IronAccuracy
                else
                    wep_mod_cone = wep.Primary.Spread
                end
                local ang = angl:Forward() || ( ( _G.LocalPlayer():GetAimVector() ):Angle() ):Forward();
                local conevec = Vector( -wep_mod_cone, -wep_mod_cone, -wep_mod_cone )
                return( coldfirev2.Predict( ucmd, ang, conevec ) ):Angle();
            end
            if( BULLET[wep:GetClass()] ) then
                local ang = angl:Forward() || ( ( _G.LocalPlayer():GetAimVector() ):Angle() ):Forward();
                local conevec = _G.Vector( 0, 0, 0 ) - BULLET[wep:GetClass()] || Vector( 0, 0, 0 );
                return( coldfirev2.Predict( ucmd, ang, conevec ) ):Angle();
            end
        else
            ang = angl:Forward() || ( ( G.LocalPlayer():GetAimVector() ):Angle() ):Forward();
            conevec = CONE[wep:GetClass()];
            return( coldfirev2.Predict( ucmd, ang, conevec ) ):Angle();
        end
    end
    return angl;
end

local function PredictPos( ent, vec ) //eat this speedhackers
    sp = LocalPlayer():GetShootPos() + LocalPlayer():GetVelocity() * engine.TickInterval()
    plFrames = RealFrameTime() / 66 || 0
    tarFrames = RealFrameTime() / 25 || 0
    plVelocity = LocalPlayer():GetVelocity()  || Vector( 0, 0, 0 )
     
    tarVelocity = ent:GetVelocity()  || Vector( 0, 0, 0 )

    return( vec + ( tarVelocity * ( tarFrames ) - ( plVelocity * ( plFrames ) ) ) )  || Vector( 0, 0, 0 )
end

local function NormalizeAngle( angle ) //thanks fr1kin
        angle.p = _G.math.NormalizeAngle( angle.p );
        angle.y = _G.math.NormalizeAngle( angle.y );
        angle.r = 0;
        return angle;
end

local function IsValidEntity( ent )
    if( ent == nil ) then return false; end
    if( IsValid( ent ) == false ) then 
        return false; 
    end
    if( _R.Entity.GetMoveType( ent ) == MOVETYPE_NONE ) then 
        return false; 
    end
    if( ent:IsPlayer() ) then
        if(VisibleCheck(ent)) then
            if( _R.Player.Alive( ent ) == false ) then 
                return false; 
            end
            if( _R.Entity.Health( ent ) <= 0 ) then 
                return false; 
            end
            return true;
        end
    end
    if( ent:IsNPC() ) then
        return true;
    end
    return false;
end

local function getbesttarget()
    if aim == true then
        COLDFIRE.target = nil;
        for k, v in next, player.GetAll() do
            if(IsValidEntity(v)) then
                COLDFIRE.target = v;
            end
        end
    end
end


local lastshoot = 0;

local function autoshoot(ucmd) //thanks fr1kin
    if( SysTime() > lastshoot ) then
        lastshoot = SysTime() + 0.03;
        ucmd:SetButtons( bit.bor( ucmd:GetButtons( ), IN_ATTACK ) );
    end
end

local OLD_ANGS = Angle(0, 0, 0);
local calcviewang = nil;

local function Aimbot( ucmd )
    if( vgui.CursorVisible() == true ) then
        return;
    end
    OLD_ANGS = OLD_ANGS + Angle( ucmd:GetMouseY() * GetConVarNumber( "m_pitch" ), ucmd:GetMouseX() * -GetConVarNumber("m_yaw"), 0 ) || Angle( 0, 0, 0 ) //thanks fr1kin

    OLD_ANGS = NormalizeAngle( OLD_ANGS );

    OLD_ANGS.y = math.NormalizeAngle( OLD_ANGS.y + ( ucmd:GetMouseX() * -0.022 * 1 ) )
    OLD_ANGS.p = math.Clamp( OLD_ANGS.p + ( ucmd:GetMouseY() * 0.022 * 1 ), -89, 90 )

    calcviewang = OLD_ANGS;
       
    ucmd:SetViewAngles( OLD_ANGS );

    if ConVarExists("NoSpreadOnFire") and GetConVar( "NoSpreadOnFire" ):GetInt() == 1 then
       if( ucmd:KeyDown( IN_ATTACK ) ) then
           local fake_angs = PredictSpread( ucmd, OLD_ANGS );
           
           fake_angs = NormalizeAngle( fake_angs );
           
           ucmd:SetViewAngles( fake_angs );
          end
    end
    if ConVarExists( "AIMBATLEL" ) and GetConVar( "AIMBATLEL" ):GetInt() == 1 then
            if aim == true then
                local ply = LocalPlayer()
                   
                if (!IsValid(COLDFIRE.target)) then
                    return
                end
                   
                if (COLDFIRE.target:InVehicle()) then
                    return
                end
     
                if (COLDFIRE.target == LocalPlayer()) then
                    return
                end
                   
                if (!COLDFIRE.target:Alive()) then
                    return
                end

                if (COLDFIRE.target == nil) then
                    return
                end
     
                if(COLDFIRE.target:IsNPC()) then
                    return
                end
     
                if(COLDFIRE.target:Team() == TEAM_SPECTATOR) then
                    return
                end

                if (COLDFIRE.target:SteamID() == "STEAM_0:1:28741409" or COLDFIRE.target:SteamID() == "STEAM_0:0:4773741" or COLDFIRE.target:SteamID() == "STEAM_0:0:21513525") then
                    return
                end

                if (COLDFIRE.target:GetFriendStatus() == "friend") and ConVarExists( "TARGETFRIENDS" ) and GetConVar( "TARGETFRIENDS" ):GetInt() == 0 then
                    return
                end

                if VisibleCheck(COLDFIRE.target) and !coldfirev2.IsDormant(COLDFIRE.target:EntIndex()) then
                    local angle = GetBoxPos(COLDFIRE.target, 0, HITGROUP_GENERIC)
                    angle = PredictPos( COLDFIRE.target, angle );
                    angle = (angle - sp):Angle()
                    angle = NormalizeAngle(angle);
                    OLD_ANGS = angle;
                    angle = PredictSpread( ucmd, angle );
                    angle = NormalizeAngle(angle);
                    ucmd:SetViewAngles(angle)
                    autoshoot(ucmd)
                    if ConVarExists( "TRIGGERBETLEL" ) and GetConVar( "TRIGGERBETLEL" ):GetInt() == 1 then
                        ucmd:SetButtons(bit.bor(ucmd:GetButtons(), IN_ATTACK ))
                    end
                end
            end
        end
    end

local function Visuals()
    if ConVarExists("EHESPE") and GetConVar( "EHESPE" ):GetInt() == 1 then
        cam.Start3D(EyePos(), EyeAngles())
                for k,v in pairs(player.GetAll()) do
                    if v:IsValid() and v:Alive() and v != LocalPlayer() and !coldfirev2.IsDormant(v:EntIndex()) then
                        render.DrawWireframeBox( v:GetPos(), Angle(), v:OBBMins(), v:OBBMaxs() + Vector( 0, 0, 7.5 ), team.GetColor(v:Team()), true ) 
                    end
                end
        cam.End3D()
    end

    if ConVarExists("CRESHAIRLEL") and GetConVar( "CRESHAIRLEL" ):GetInt() == 1 then
        surface.SetDrawColor( Color(0,255,0))
        surface.DrawLine( ScrW() / 2, ScrH() / 2 - 2, ScrW() / 2, ScrH() / 2 + 3 )
        surface.SetDrawColor( Color(0,0,0) )
        surface.DrawOutlinedRect( ScrW() / 2 - 1, ScrH() / 2 - 4, 3, 9 )
        surface.SetDrawColor( Color(0,255,0))
        surface.DrawLine( ScrW() / 2 - 2, ScrH() / 2, ScrW() / 2 + 3, ScrH() / 2 )
        surface.SetDrawColor( Color(0,0,0) )
        surface.DrawOutlinedRect( ScrW() / 2 - 4, ScrH() / 2 - 1, 9, 3 )
    end

    if ConVarExists("SKELETONLEL") and GetConVar( "SKELETONLEL" ):GetInt() == 1 then
        for k,v in pairs(player.GetAll()) do
            if v != LocalPlayer() and !coldfirev2.IsDormant(v:EntIndex()) then
                for k1, v1 in pairs( skeleton ) do
                    local sPos, ePos = v:GetBonePosition( v:LookupBone( v1.S ) ):ToScreen(), v:GetBonePosition( v:LookupBone( v1.E ) ):ToScreen()
                        
                    surface.SetDrawColor( team.GetColor( v:Team() ) )
                    surface.DrawLine( sPos.x, sPos.y, ePos.x, ePos.y )
                end
            end
        end
    end

    if ConVarExists("LASERSIGHTLEL") and GetConVar( "LASERSIGHTLEL" ):GetInt() == 1 then
        if LocalPlayer():GetActiveWeapon():IsValid() then
            if IsValid(LocalPlayer():GetActiveWeapon()) then
                local vm = LocalPlayer():GetActiveWeapon()

                if IsValid(LocalPlayer():GetViewModel()) then
                    vm = LocalPlayer():GetViewModel()
                    local attachmentIndex = vm:LookupAttachment("2")

                    if attachmentIndex == 0 then attachmentIndex = vm:LookupAttachment("muzzle") end
                    
                    pos = LocalPlayer():GetViewModel():GetAttachment(attachmentIndex)
                    pos = pos and pos.Pos or LocalPlayer():EyePos() + Vector(5,0,0)
                end
            end
            local trace = LocalPlayer():GetEyeTrace().HitPos
            cam.Start3D()
                cam.IgnoreZ( true )
                    render.SetMaterial( Material( "trails/laser" ) )
                    render.DrawBeam( pos, trace, 8, 2, 0, lasercolor)
                    render.SetMaterial( Material( "Sprites/light_glow02_add_noz" ) )
                    render.DrawQuadEasy( trace, (LocalPlayer():EyePos() - trace):GetNormal(), 12.5, 12.5, Color( 255, 255, 255, 255 ) ) 
                cam.IgnoreZ( false )   
            cam.End3D()
        end
    end
    if ConVarExists("LASEREYESLEL") and GetConVar( "LASEREYESLEL" ):GetInt() == 1 then
        for k,v in pairs(player.GetAll()) do
            if v:IsValid() and v:Alive() and v != LocalPlayer() then
                cam.Start3D()
                    cam.IgnoreZ( true )
                        render.SetMaterial( Material( "trails/laser" ) )
                        render.DrawBeam( v:EyePos(), v:GetEyeTrace().HitPos, 8, 2, 0, lasercolor)
                    cam.IgnoreZ( false )   
                cam.End3D()
            end
        end
    end
end

local function Chams()
    if ConVarExists("CHEMS") and GetConVar( "CHEMS" ):GetInt() == 1 then
        for k,v in pairs(player.GetAll()) do
            if v:Alive() and v:IsPlayer() and !coldfirev2.IsDormant(v:EntIndex()) then
                local mat = chamsmat()
                local color = team.GetColor( v:Team() )
                cam.Start3D( EyePos(), EyeAngles() )
                render.SuppressEngineLighting( false )
                render.SetColorModulation( ( color.r / 255 ), ( color.g / 255 ), ( color.b / 255 ) )
                render.MaterialOverride( mat )
                v:DrawModel()
                cam.End3D()
            end
        end
    end
end

local function novisrecoil(ply,origin,angles,fov)
    if ConVarExists("NoVisualRecoil") and GetConVar( "NoVisualRecoil" ):GetInt() == 1 then
    local view = {} 
    view.origin = origin;
    view.angles = calcviewang;
    view.fov = GetConVarNumber('fov_desired')
        
    return view
    end
    return GAMEMODE:CalcView(ply,origin,angles,fov);
end

hook.Add('CalcView','novisrecoil', novisrecoil)

local function bhop(ucmd)
    if bit.band( ucmd:GetButtons(), IN_JUMP ) ~= 0 then
        if !LocalPlayer():IsOnGround() then
            ucmd:SetButtons( bit.band( ucmd:GetButtons(), bit.bnot( IN_JUMP ) ) )
        end
    end
end

local function CreateMoveHook(ucmd)
    Aimbot(ucmd);
    bhop(ucmd);
end

local function ThinkHook()
    getbesttarget()
end

local function VisualsHook()
    Visuals()
end

local function OpenMenu( ply, key )
    if key != KEY_INSERT then return end
    local Frame = vgui.Create("DFrame")
    Frame:SetSize( 590, 410 )
    Frame:SetPos( ScrW() / 2 - 295, ScrH() / 2 + 1000 )
    Frame:MakePopup()
    Frame:SetTitle("ColdFire V2 - Menu")
    Frame:SetDraggable( false )
    Frame.btnMinim:Hide()
    Frame.btnMaxim:Hide()
    Frame.btnClose:Hide()
    Frame:MoveTo( ScrW() / 2 - 295, ScrH() / 2 - 205, 0.75, 0, 1 )
    
    function Frame:Paint( w, h )
        draw.RoundedBox( 1, 0, 0, w, h, Color( 116, 187, 251, 85 ) )
        surface.SetDrawColor(211, 211, 211 , 235)
        surface.DrawOutlinedRect( 0, 0, w, h )
    end

    local CloseBtn = Frame:Add("DButton")
    CloseBtn:SetSize( 15, 15 )
    CloseBtn:SetPos( Frame:GetWide() - 17.5 , 2.5 )
    CloseBtn:SetText("")
    function CloseBtn:DoClick()
        Frame:MoveTo( ScrW() / 2 - 295, ScrH() / 2 + 1000, 0.75, 0, 1 )

        timer.Simple( 0.75, function()
            Frame:Close()
        end)
    end

    function CloseBtn:Paint( w, h )
        draw.SimpleText( "r", "Marlett", w / 2 - 6.5, h / 2 - 7.5, Color( 255, 255, 255, 255 ) )
    end

    local TabMenu = Frame:Add("DPropertySheet")
    TabMenu:SetSize( Frame:GetWide() - 2, Frame:GetTall() - 22.5 )
    TabMenu:SetPos( 1, 22.5 )

    local AimPanel = TabMenu:Add("DPanel")
    AimPanel:SetSize( TabMenu:GetWide(), TabMenu:GetTall() )
    AimPanel:SetPos( 0, 0 )

    function AimPanel:Paint( w, h )
    end

    local ESPPanel = TabMenu:Add("DPanel")
    ESPPanel:SetSize( TabMenu:GetWide(), TabMenu:GetTall() )
    ESPPanel:SetPos( 0, 0 )

    function ESPPanel:Paint( w, h )
        draw.SimpleText( "Laser Eye/Laser Sight Color Settings", "ChatFont", 130, 10, Color( 102, 102, 102, 255 ), TEXT_ALIGN_LEFT, TEXT_ALIGN_CENTER )
    end

    local MiscPanel = TabMenu:Add("DPanel")
    MiscPanel:SetSize( TabMenu:GetWide(), TabMenu:GetTall() )
    MiscPanel:SetPos( 0, 0 )

    function MiscPanel:Paint( w, h )
    end

    TabMenu:AddSheet("Aimbot", AimPanel, "gui/silkicons/bomb", false, false, "Change Aimbot settings here.")
    TabMenu:AddSheet("ESP/Wallhack", ESPPanel, "gui/silkicons/group", false, false, "Change ESP and Wallhack settings here.")
    TabMenu:AddSheet("Changelog + Misc", MiscPanel, "gui/silkicons/plugin", false, false, "Change miscellaneous settings here.")

    // ESP/Wallhack
    local ESPOptionsPanel = ESPPanel:Add("DScrollPanel")
    ESPOptionsPanel:SetPos( 0, 0 )
    ESPOptionsPanel:SetSize( 120, ESPPanel:GetTall() )
    function ESPOptionsPanel:PaintOver( w, h )
        surface.SetDrawColor( 72, 72, 72 , 235 )
        surface.DrawOutlinedRect( 0, 0, w, h / 1.1 )
    end

    local ESPOptions = ESPOptionsPanel:Add("DIconLayout")
    ESPOptions:SetSize( ESPOptionsPanel:GetWide() - 10, ESPOptionsPanel:GetTall() - 10 )
    ESPOptions:SetPos( 5, 5 )
    ESPOptions:SetSpaceY( 5 )
    ESPOptions:SetSpaceX( 5 )

    for k,v in SortedPairsByMemberValue( ESPFeatures, "HackName", false ) do
        local ESPLabel = ESPOptions:Add("DCheckBoxLabel")
        ESPLabel:SetText( v.HackName )
        ESPLabel:SetConVar( v.VariableName )
        ESPLabel:SizeToContents()
    end

    local LaserColor = ESPPanel:Add("DColorMixer")
    LaserColor:SetPos( 130, 25 )
    LaserColor:SetPalette( true )
    LaserColor:SetAlphaBar( true )
    LaserColor:SetWangs( true )
    LaserColor:SetColor( Color( 30, 100, 160 ) )
    function LaserColor:ValueChanged( cubecolor )
        lasercolor = cubecolor
    end

    // Aimbot
    local AimOptionsPanel = AimPanel:Add("DScrollPanel")
    AimOptionsPanel:SetPos( 0, 0 )
    AimOptionsPanel:SetSize( 120, AimPanel:GetTall() )
    function AimOptionsPanel:PaintOver( w, h )
        surface.SetDrawColor( 72, 72, 72 , 235 )
        surface.DrawOutlinedRect( 0, 0, w, h / 1.1 )
    end

    local AimOptions = AimOptionsPanel:Add("DIconLayout")
    AimOptions:SetSize( AimOptionsPanel:GetWide() - 10, AimOptionsPanel:GetTall() - 10 )
    AimOptions:SetPos( 5, 5 )
    AimOptions:SetSpaceY( 5 )
    AimOptions:SetSpaceX( 5 )

    for k,v in SortedPairsByMemberValue( AimFeatures, "HackName", false ) do
        local AimLabel = AimOptions:Add("DCheckBoxLabel")
        AimLabel:SetText( v.HackName )
        AimLabel:SetConVar( v.VariableName )
        AimLabel:SizeToContents()
    end

    //Misc Panel
    local Changelog = MiscPanel:Add("DTextEntry")
    Changelog:SetPos( 145, 10 )
    Changelog:SetSize( MiscPanel:GetWide() - 165, 150 )
    Changelog:SetText("Changelog 7/10/2014:\nChanged to a less performance taxing (but more buggy) targeting method.\n\nChangelog 7/8/2014:\nAdded nospread on fire.\nAdded noshake for nospread.\nAdded bunnyhop.\nAdded autoshoot, it's buggy right now.\nHook code cleanup.\nWill need to add code cleanup.\n\n---IMPORTANT---\nThis is a pre-alpha version of the cheat. If I break shit, you need to tell me.")
    Changelog:SetMultiline( true )
    Changelog:SetEditable( false )
end

hook.Add( "PlayerButtonDown", "OpenMenu", OpenMenu )
hook.Add( "CreateMove", "Aimbot", CreateMoveHook )
hook.Add( "HUDPaint", "Visuals", VisualsHook )
hook.Add( "Think", "Target", ThinkHook )
hook.Add( "RenderScreenspaceEffects", "Chams", Chams )

_R = debug.getregistry()

local ban = _R.Player.SetViewAngles

_R.Player.SetEyeAngles = function( self, a )
--print(debug.getinfo(2).short_src)
local dbgsrc = debug.getinfo( 3, 'S' )[ 'short_src' ]
    if dbgsrc:lower():find( 'weapon' ) then
--if debug.getinfo(2).short_src:lower():find('weapon') then
    return
end
    return ban( self, a )
end

concommand.Add( "+CFv2_aimbot", function()
    aim = true;
end )

concommand.Add( "-CFv2_aimbot", function()
    aim = false;
end )