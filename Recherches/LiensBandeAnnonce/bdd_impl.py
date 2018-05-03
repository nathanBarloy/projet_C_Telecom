import re

file = open("../../Sources/data/bd.json", "r")
rsc = open("liensYouTube.txt", "r")
dest = open("destination.json", "w")

rsc_line = rsc.readline()
for line in file:
    m = re.match(".\"Year\".", line)
    if(m):
        dest.write(line.rstrip('\n')[:-1] + ",\n")
        link = re.sub('[0-9]{1,3}: https', 'https', rsc_line)
        dest.write("  \"Url\": \"" + link.rstrip('\n') + "\"\n")
        rsc_line = rsc.readline()
    else:
        dest.write(line)

file.close()
rsc.close()
dest.close()
