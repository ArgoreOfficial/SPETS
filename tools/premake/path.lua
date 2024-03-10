
local t = {}

t.getProjectName = function( depth )
    local file = debug.getinfo(1).short_src
    local dir = file

    for i = 0, depth do
        dir = dir:match( "^(.+)/" )
    end

    local name = dir:gsub( "^(.*/)", "" )

    print( "  Project Directory: " .. dir )
    print( "  Project Name: " .. name )
    return name
end

return t
