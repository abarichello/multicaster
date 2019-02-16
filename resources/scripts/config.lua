DEFAULT_CONFIG = ""

function startup()
    if not config_file_exists() then
        create_config_fie()
    end
end

function config_file_exists()
    if io.open("config.multicaster", "r") == nil then
        return false
    end
    return true
end

function create_config_fie()
    lualog.log("Config file does not exist, creating a new one.")
end
