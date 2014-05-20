
update = 
function()
	local rot = LuaCameraInterface.getRotation()
	rot = rot - 1
	LuaCameraInterface.setRotation(rot)
	
	local x,y = LuaCameraInterface.getPosition()
	x  = x + 20
	LuaCameraInterface.setPosition(x,y)
	
	--LuaCameraInterface.setRotation(0);
	--LuaCameraInterface.setPosition(0,0);
end

render = 
function()

end

start_pressed
=
function()
	
end
	
init = 
function()
	--DO NOT FRIGGIN TOUCH
	local LuaController = LuaImageActor.new()
	LuaController:setSize(0,0)
	LuaController:setColors(0,0,0,0)
	LuaController:appendFunctionToEvent("onUpdate",
	function()
		update()
	end)

	LuaController:appendFunctionToEvent("onRender",
	function()
		render()
	end)
	--END OF NONE OF YOUR BEEzWAX

	--BG
	local temp = LuaImageActor.new("wall")
	temp:setPosition(0,50)
	temp:setSize(256,400)
	
	local temp = LuaImageActor.new("wall")
	temp:setPosition(251,50)
	temp:setSize(256,400)
	
	local temp = LuaImageActor.new("wall")
	temp:setPosition(502,50)
	temp:setSize(256,400)
	
	local temp = LuaImageActor.new("logo")
	temp:setSize(320,180)
	temp:setPosition(250,120)
	
	local temp = LuaImageActor.new("dresser")
	temp:setSize(130, 200)
	temp:setPosition(330,280)
	
	--END OF BG

	sbutton = LuaImageActor.new("start_button")
	sbutton:setAsButton(1)
	sbutton:setSize(150,60)
	sbutton:setPosition(465,320)
	
	sbutton:appendFunctionToEvent("onPressed", 
		function() 
			start_pressed()
		end
	)
	
	--cuts frames in half
	local temp = LuaImageActor.new("haze")
	temp:setDepth(100)
	temp:setSize(800,600)
end

start_pressed
=
function()
	local rot = sbutton:getRotation()+5;
	sbutton:setRotation(rot) 
end