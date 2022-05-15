import redis
import json
import pandas as pd
data = {
    	"lat": 43.4507, "lon": 39.9585, "H": 1000.0,
		"psi": 1.9,"tet": 51.0,"gam": 0.0,"tetZ": 0.0, "gamZ": 0.0, "psiZ": 1.9,
		"Upsi": 0.0,"Ugam": 0.0,"Utet": 0.0,"V": 10.0,"Vzad": 0.0, "VzadMax": 70.0,
		"Ve": 0.0,"Vn": 0.0,"Vh": 0.0,				
		"ax":0.0, "ay":0.0, "az":0.0,			  				
		"ny":1.0,"nymax":10.0
}
data1 = bytes(4)
data3 = {
    	"lat": 43.4507, "lon": 39.9585, "H": 1000.0,
		"psi": 1.9,"tet": 51.0,"gam": 0.0,"tetZ": 0.0, "gamZ": 0.0, "psiZ": 1.9,
		"Upsi": 0.0,"Ugam": 0.0,"Utet": 0.0,"V": 10.0,"Vzad": 0.0, "VzadMax": 70.0,
		"Ve": 0.0,"Vn": 0.0,"Vh": 0.0,				
		"ax":0.0, "ay":0.0, "az":0.0,			  				
		"ny":1.0,"nymax":10.0
}
r = redis.StrictRedis()
r.execute_command('SET LAstruct', json.dumps(data))
#r.execute_command('SET KBOstruct', json.dumps(data))
#r.execute_command('GET LAstruct', json.dumps(data))
data1 = r.get("LAstruct")
df =pd.read_json(data1)
print(df)
#хороший пример https://stackoverflow.com/questions/21104592/json-to-pandas-dataframe
#print(data1)
#jsondata = json.loads(data1)
#print(jsondata["lat"])
#lat = jsondata["lat"] + 1
#print(lat)
#lat.decode("utf-8")
#jsondata["lat"] = jsondata["lat"] + 1
#json.dumps(data1)
#r.execute_command('GET LAstruct', data1)
#print(data.dump())
#reply = json.loads(r.execute_command('GET LAstruct', 'doc'))