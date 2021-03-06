import re

file = open("../../Sources/data/bd.json", "r")
rsc = open("tempURL.txt", "r")
dest = open("destination.json", "w")

rsc_line = rsc.readline()
i = 0;
for line in file:
    m = re.match(".\"Year\".", line)
    if(m):
        dest.write(line.rstrip('\n')[:-1] + ",\n")
        link = re.sub('[0-9]{1,3}: ','', rsc_line)
        print(link)
        dest.write("    \"Url\": \"" + link.rstrip('\n') + "\",\n")
        rsc_line = rsc.readline()
        dest.write("    \"Cover\": \"img/covers/" + str(i) + ".jpg\"\n")
        i = i+1
    else:
        dest.write(line)

file.close()
rsc.close()
dest.close()
