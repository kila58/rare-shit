ClientEntity = {}
ClientEntity_mt = { __index = ClientEntity }

function ClientEntity:new(cliententity)
	return setmetatable({ent = cliententity}, ClientEntity_mt)
end

function ClientEntity:Release()
	return CE_Release(self.ent);
end

function ClientEntity:GetAbsOrigin()
	return CE_GetAbsOrigin(self.ent);
end

function ClientEntity:GetAbsAngles()
	return CE_GetAbsAngles(self.ent);
end
