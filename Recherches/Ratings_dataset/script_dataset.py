import requests
import regex
import os
from PIL import ImageFile
import simplejson as json
import csv

# opening of the JSON file
with open('../ReadBD/bd.json') as bd:
    config = json.load(bd)

csv_file = open("./ratings.csv")
csv_reader = csv.reader(csv_file)

dest = open("users_rates.json", "w")


# Problème entre titres français et anglais variants : plus simple à la main
base_list = []
base_list.append([115713, "Ex Machina"])
base_list.append([116823, "Hunger Games: La révolte - 1ère partie"])
base_list.append([127194, "The D Train"])
base_list.append([134368, "Spy"])
base_list.append([129250, "Superfast!"])
base_list.append([120466, "Chappie"])
base_list.append([130083, "Kidnapping Mr. Heineken"])
base_list.append([140715, "Straight Outta Compton"])
base_list.append([122902, "Fantastic Four"])
base_list.append([130448, "Poltergeist"])
base_list.append([117176, "Une merveilleuse histoire du temps"])
base_list.append([118898, "A Most Violent Year"])
base_list.append([118900, "Wild"])
base_list.append([127198, "Dope"])
base_list.append([130634, "Fast & Furious 7"])
base_list.append([136020, "Spectre"])
base_list.append([130073, "Cendrillon"])
base_list.append([122892, "Avengers: L'ère d'Ultron"])
base_list.append([130490, "Divergente 2: L'insurrection"])
base_list.append([109487, "Interstellar"])
base_list.append([130520, "Home"])
base_list.append([131013, "Get Hard"])
base_list.append([136864, "Batman v Superman: Dawn of Justice"])
base_list.append([121231, "It Follows"])
base_list.append([122882, "Mad Max: Fury Road"])
base_list.append([119145, "Kingsman: Services secrets"])
base_list.append([125916, "Cinquante nuances de Grey"])
base_list.append([118997, "Into the Woods: Promenons-nous dans les bois"])
base_list.append([139642, "Southpaw"])
base_list.append([129354, "Diversion"])
base_list.append([117529, "Jurassic World"])
base_list.append([108190, "Divergente"])
base_list.append([116797, "Imitation Game"])
base_list.append([112852, "Les Gardiens de la Galaxie"])
base_list.append([102716, "Fast & Furious 6"])
base_list.append([115617, "Les nouveaux héros"])
base_list.append([126548, "The DUFF"])
base_list.append([122886, "Star Wars: Episode VII - Le Réveil de la Force"])
base_list.append([112183, "Birdman"])
base_list.append([112552, "Whiplash"])
base_list.append([116887, "Exodus"])
base_list.append([119655, "Le septième fils"])
base_list.append([112556, "Gone Girl"])
base_list.append([118696, "Le Hobbit: La bataille des cinq armées"])
base_list.append([118702, "Invincible"])
base_list.append([4369, "Fast and Furious"])


rates = []
for row in csv_reader:
    for data in base_list:
        if str(data[0]) == str(row[1]):
            rates.append([row[0], row[1], row[2]])
            break

print("on obtient " + str(len(rates)) + " notes")

#obtenir nombre utilisateurs différents
list_users = []
for a in rates:
    list_users.append(a[0])

users_unique = list(set(list_users))
print(len(users_unique))


#initialisation
final = []
for b in users_unique:
    final.append([b,[]])

for c in rates:
    for d in range(0, len(final)):
        if str(c[0]) == str(final[d][0]):
            final[d][1].append([c[1],c[2]])
            break

print("toto : " + str(final[1][1]))
#ecriture du JSON
dest.write("[\n")
for f in final:
    dest.write("{\n")
    dest.write("\"Id\": " + f[0] + ",\n")
    dest.write("\"History\":\n")
    dest.write("    {\n")
    dest.write("    \"Rates\":\n")
    dest.write("    [\n")
    for g in f[1]:
        dest.write("        {\n")
        dest.write("        \"Id\": " + g[0] + ",\n")
        dest.write("        \"Rate\": " + g[1] + ",\n")
        dest.write("        },\n")
    dest.write("    ]\n")
    dest.write("    }\n")
    dest.write("},\n")
dest.write("]\n")
