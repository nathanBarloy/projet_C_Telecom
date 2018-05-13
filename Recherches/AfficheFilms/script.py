import requests
import regex
import os
from PIL import ImageFile
import simplejson as json

# opening of the JSON file
with open('../ReadBD/bd.json') as bd:
    config = json.load(bd)

# genère l'url de la requête
def URLgenerator(title):
    query = title + " cover"
    request = ""
    for letter in query:
        if letter == " ":
            request = request + "+"
        elif letter == "&":
            request = request + "%26"
        else:
            request = request + letter
    url = 'https://www.google.com/search?q=' + request + '&tbm=isch'
    print(url)
    return url

# problème de avec .text (ne lui pas la page html comme souhaité)
def selectLink(url):
    html_content = requests.get(url).text
    print(html_content)
    search_result = regex.findall(r'href=\"\/imgres\?imgurl=(.*?)&imgrefurl.*?', html_content)
    print(len(search_result))


def getSizes(url):
    # get file size *and* image size (None if not known)
    file = requests.get(url)
    size = file.headers['content-length']
    if size: size = int(size)
    p = ImageFile.Parser()
    while 1:
        data = file.content
        if not data:
            break
        p.feed(data)
        if p.image:
            return p.image.size
            break
    file.close()
    return size, None




# main
print(config[0]["Title"])
URLgenerator(config[0]["Title"])
selectLink(URLgenerator(config[0]["Title"]))
print(getSizes('http://www.zickma.fr/wp-content/uploads/2015/06/Fast-7-extended.jpg'))

# requête pour accéder au résultat des recherches images

# sélection de la première image répondant aux conditions :
#    largueur < hauteur
#    Mot Affiche dans le Mot

# Télécharger le fichier et le stocker dans un dossier
