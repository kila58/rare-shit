EntList = {}
EntList_mt = { __index = EntList }

function EntList:new()
	return setmetatable({}, EntList_mt)
end

function EntList:GetClientEntity(idx)
	return EL_GetClientEntity(idx)
end

function EntList:GetHighestEntityIndex()
	return EL_GetHighestEntityIndex()
end

function EntList:NumberOfEntities()
	return EL_NumberOfEntities()
end

function EntList:MaxEntities()
	return EL_GetMaxEntities()
end
