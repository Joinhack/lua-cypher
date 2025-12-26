local cypher= require "cypher"

local function bin2hex(s)
    local t = {}
    for i = 1, #s do
        local b = s:byte(i)
        t[#t+1] = string.char(
            (b >> 4) < 10 and (b >> 4) + 48 or (b >> 4) + 87,
            (b & 0xF) < 10 and (b & 0xF) + 48 or (b & 0xF) + 87
        )
    end
    return table.concat(t)
end
function sha256_test()
    local sha256_ctx = cypher.sha256.new()
    sha256_ctx:update("11")
    local val = sha256_ctx:final()
    assert(bin2hex(val) == '4fc82b26aecb47d2868c4efbe3581732a3e7cbcc6c2efb32062c08170a05eeb8', "sha256 fail")
end

sha256_test()