luastr = function()
	local temp = LuaImageActor.new()
	temp:setColors(255,0,0,1)
	temp:setTimedEvent(90, function() temp:setSize(500,500) end)
	
	local temp = LuaImageActor.new()
	temp:setPosition(400,400)
	temp:setColors(255,0,0,1)
	
	
	temp:appendFunctionToEvent("onUpdate", 
	function() 
	local rot = temp:getRotation()+5;
	temp:setRotation(rot) 
	end)
end