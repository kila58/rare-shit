Vector = {}
Vector_mt = { __index = Vector }

function Vector:new(x, y, z)
	return setmetatable({x = x, y = y, z = z}, Vector_mt)
end

function Vector:get()
	return self.x, self.y, self.z
end

function Vector:Distance(vec2)
	local deltaX = self.x - vec2.x
	local deltaY = self.y - vec2.y
	local deltaZ = self.z - vec2.z
	return math.sqrt((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ))
end
