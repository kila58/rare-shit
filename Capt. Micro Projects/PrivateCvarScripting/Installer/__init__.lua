require("__keys__") --include msdn VK_ defines
require("__helpers__") --include BypassConVar/BypassConCmd

local prefix = "pcs_"

--wallhax
BypassConVar(prefix, "r_drawothermodels")

--speedhax
BypassConVar(prefix, "sv_cheats")
BypassConVar(prefix, "host_timescale")

--camideals
BypassConVar(prefix, "cam_idealyaw")
BypassConVar(prefix, "cam_idealdist")

--thirdperson
BypassConCmd(prefix, "thirdperson")

--rename exec
--local exec = FindCommand("exec")
--SetName(exec, "execute_cfg")
