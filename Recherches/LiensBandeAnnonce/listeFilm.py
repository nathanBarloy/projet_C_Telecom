import simplejson as json

with open('../ReadBD/bd.json') as bd:
    config = json.load(bd)
i = 0
while i < 100:
    print(i+1)
    print(config[i]["Title"])
    i = i+1
