lualog = {}

function lualog.log(message)
    io.write("--> LUA: " .. message .. "\n")
    io.flush()
end

return lualog
