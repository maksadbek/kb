local cjson = require "cjson"
local route = require "resty.route".new()
local redis = require "resty.redis":new()

redis:set_timeout(1000)

local ok, err = redis:connect("127.0.0.1", 6379)
if not ok then
	ngx.say(cjson.encode({
		message = "fuck! failed to connect to database",
		error = true
	}))
	ngx.exit(ngx.OK)
end


route:get("/", function(self)
	ngx.say(cjson.encode({
		message = 'hello motherfucker',
		error = false
	}))

	local query_string = ngx.req.get_uri_args()

	local key = query_string["name"]

	local res, err = redis:get(key)
	if not res then
		ngx.say(cjson.encode({
			message = "oh no, failed to get data, fuck off!",
			error = true
		}))
		return
	end
	
	if res == ngx.null then
		ngx.say("not found blyat")
		return
	end

	
	ngx.say(cjson.encode({
		data = res,
		error = false
	}))

	ngx.exit(ngx.OK)
end)

route:post("/", function (self)
	ngx.req.read_body()

	local text = ngx.var.request_body
	local ok, value = pcall (cjson.decode, text)

	if (not ok) then
		ngx.say(cjson.encode({
			message = "oh no, get the fuck off!",
			error = true
		}))

		ngx.exit(ngx.OK)
	end

	for k, v in pairs(value) do
		ok, err = redis:set(k, v)
		if not ok then
			ngx.say(cjson.encode({
				message = "oh no, failed to write data into redis, fuck off!",
				error = true
			}))
		end
		
	end

	ngx.exit(ngx.OK)
end)

return route:dispatch()
