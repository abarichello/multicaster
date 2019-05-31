save_table = {
    last_ip = "127.0.0.1",
    username = "player",
}

local SAVENAME = "multicaster.save"
local SEPARATOR = "|"

-- Functions called at every game startup
function start_save()
    if not save_exists() then
        write_save_file()
    else
        load_save_file()
    end
    print_save_file()
end

function write_save_file()
    lualog.log("Writing save file to: " .. SAVENAME)
    local save = io.open(SAVENAME, "w")
    for k, v in pairs(save_table) do
        print(v)
        save:write(k .. SEPARATOR .. v .. "\n")
    end
    save:close()
end

function load_save_file()
    lualog.log("Loading save file")
    local save = io.open(SAVENAME, "r")
    for line in save:lines() do
        local sep = line:find(SEPARATOR)
        local key = line:sub(0, sep - 1)
        local value = line:sub(sep + 1, line:len())
        save_table[key] = value
    end
    save:close()
end

function save_exists()
    local save = io.open(SAVENAME, "r")
    if save ~= nil then
        io.close(save)
        return true
    else
        return false
    end
end

function print_save_file()
    lualog.log("Printing current save file:")
    for k, v in pairs(save_table) do
        print(k, v)
    end
end
