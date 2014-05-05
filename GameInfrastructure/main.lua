init = 
function()
	local temp = LuaImageActor.new()
	temp:setColors(255,0,0,1)
	temp:setAsButton(1)
	--[[temp:appendFunctionToEvent("onPressed",
		function()
			print "pressed"
		end
	)--]]
	
	local temp = LuaImageActor.new()
	temp:setAutoMove(1)
	temp:setDestinationCoordinates(0,400)
	temp:setPosition(400,400)
	temp:setColors(255,0,0,1)
	
	--[[temp:appendFunctionToEvent("onUpdate", 
		function() 
			local rot = temp:getRotation()-1;
			temp:setRotation(rot) 
		end
	)--]]
end

update = 
function()
	print "yup"
end

render = 
function()

end