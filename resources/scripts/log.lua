lualog = {}

function log(message)
    io.write("--> LUA: " .. message .. "\n")
    io.flush()
end

lualog["log"] = log
return lualog
