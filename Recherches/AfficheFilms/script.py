import requests
import regex
import os
from PIL import ImageFile
import simplejson as json

# opening of the JSON file
with open('../ReadBD/bd.json') as bd:
    config = json.load(bd)

def MovieDBUrl(id):
    title = config[id]["Title"]
    # préparation de la requête
    request = ""
    for letter in title:
        if letter == " ":
            request = request + "+"
        elif letter == "&":
            request = request + "%26"
        else:
            request = request + letter
    # Film ou TV series
    type = config[id]["Type"]
    if type == "Film":
        cat = "movie"
    elif type == "TV Series" or type == "TV Movie":
        cat = "tv"
    # Finalisation de l'URL
    url = 'https://www.themoviedb.org/search/' + cat +'?query=' + request
    # print(url)
    return url, cat


# problème de avec .text (ne lui pas la page html comme souhaité)
def selectLink(url):
    html_content = requests.get(url[0]).text
    # Film ou TV series
    search_result = regex.findall(r'href=\"/' + url[1] + '/(.*?)\" title', html_content)
    # search_result = regex.findall(r'/film/fichefilm_gen_cfilm=198750.html', html_content)
    print("On a " + str(len(search_result)) + " résultat(s)")
    # for i in range(len(search_result)):
    #     print(search_result[i])
    return search_result, url[1]

def checkDate(url, id):
    # print(url)
    html_content = requests.get(url).text
    date = regex.findall(r'class=\"release_date\">\((.{4})\)', html_content)
    if date[0] == str(config[id]["Year"]):
        return 1
    else:
        return 0

def getImageURL(url):
    # print(page)
    html_content = requests.get(url).text
    result = regex.findall(r'<img class="poster".*?srcset=.*?1x, https://(.*?).jpg 2x', html_content)
    # print(result[0])
    return result[0]

def downloadImage(url, id):
    newUrl = "https://" + url + ".jpg"
    r = requests.get(newUrl)
    open('./../../Sources/web/img/covers/'+ str(id) + '.jpg', 'wb').write(r.content)
    print("Image téléchargé pour " + config[id]["Title"])

# obtenir les infos (dimensions de l'image) pour avoir une qualité suffisante
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
for i in range(85,100):
    urlRequest = MovieDBUrl(i)
    answer = selectLink(urlRequest)
    urlPart = answer[0]
    type = answer[1]
    j = 0
    cnt = 0
    last = ""
    while j==0:
        if last != urlPart[cnt]:
            page = "https://www.themoviedb.org/" + type + "/" + urlPart[cnt]
            j = checkDate(page, i)
            last = urlPart[cnt]
        cnt = cnt + 1
    print("la bonne page est : " + page)
    downloadImage(getImageURL(page), i)
