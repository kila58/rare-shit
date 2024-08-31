Entity = {}
Entity_mt = { __index = Entity }

function Entity:From(baseentity)
	return setmetatable({ent = baseentity}, EntList_mt)
end

