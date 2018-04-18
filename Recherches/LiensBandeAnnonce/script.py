import requests
import regex
import simplejson as json

#load the json file
with open('../ReadBD/bd.json') as bd:
    config = json.load(bd)

# opening txt file
file = open("tempURL.txt", "w")

# generate the URL from the title
def youtubeSearch(query):
    with requests.session() as c:
        url = 'https://www.youtube.com/results?search_query='
        query = query + " bande annonce"
        print(query)
        request = ""
        for letter in query:
            if letter == " ":
                request = request + "+"
            elif letter == "&":
                request = request + "%26"
            else:
                request = request + letter
        url = url + request
        urllink = requests.get(url)
        print(urllink.url)
        return urllink.url


# main
i = 0
while i < 100:
    html_content = requests.get(youtubeSearch(config[i]["Title"])).text
    search_result = regex.findall(r'href=\"\/watch\?v=(.{11})', html_content)
    print (search_result[0])
    print("https://www.youtube.com/watch?v=" + search_result[0])
    file.write(str(i+1) + ": " + "https://www.youtube.com/watch\?v=" + search_result[0] + "\n")
    i = i + 1

file.close()
