local save_table = {
    last_ip = "192.168.0.1",
    username = "player",
}

local SAVENAME = "multicaster.save"

-- Functions called at every game startup
function start_save()
    if not save_exists() then
        create_save_file()
    end
    print_save_file()
end

function create_save_file()
    lualog.log("Creating a new save file: " .. SAVENAME)
    local save = io.open(SAVENAME, "w+")
    for k, v in pairs(save_table) do
        save:write(k .. " " .. v .. "\n")
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
