local cjson = require "cjson"
local cbson = require("cbson")
local moongoo = require("resty.moongoo")
local route = require "resty.route".new()
local validation = require "resty.validation"

local mgo, err = moongoo.new("mongodb://127.0.0.1")
if not mgo then
	error(err)
end

local col = mgo:db("recipes"):collection("recipes")

route:get("/", function(self)
	local doc, err = col:find()
	if not doc then
		ngx.say(cjson.encode({
			message = "failed to get recipes",
			error = err
		}))
		return
	end

	ngx.say(cjson.encode({
		data = cbson.to_json(cbson.encode(doc))
	}))

	ngx.exit(ngx.OK)
end)

route:post("/", function(self)
	ngx.req.read_body()
	local text = ngx.var.request_body
	local ok, value = pcall (cjson.decode, text)

	ngx.log(ngx.NOTICE, "blyat")

	if (not ok) then
		ngx.say(cjson.encode({
			message = "invalid data"
		}))

		return
	end

	local group = validation.new{
		name = validation.string:minlen(5),
		prepTime = validation.number:between(2, 500),
		difficulty = validation.number:between(1, 5),
		vegetarian = validation.boolean
	}

	local valid, fields, errs = group(value)

	if not valid then
		ngx.say(cjson.encode({
			message = "invalid data",
			errors = errs
		}))
		return
	end

	local id, err = col:insert({
		name = value["name"],
		prepTime = value["prepTime"],
		difficulty = value["difficulty"],
		vegatarian = value["vegatarian"]
	})

	if not id then
		ngx.say(cjson.encode({
			message = "failed to create a recipe",
			error = err
		}))
		return
	end

	ngx.say(cjson.encode({
		data = cbson.to_json(cbson.encode(id))
	}))
end)

route:get("/{id}", function(self)
	ngx.say("get /{id}")
end)

route:put("/{id}", function(self)
	ngx.say("put /{id}")
end)

route:patch("/{id}", function(self)
	ngx.say("patch /{id}")
end)

route:delete("/{id}", function(self)
	ngx.say("delete /{id}")
end)

route:put("/{id}/rate", function(self)
	ngx.say("put /{id}/rate")
end)

route:patch("/{id}/rate", function(self)
	ngx.say("patch /{id}/rate")
end)

return route:dispatch()
