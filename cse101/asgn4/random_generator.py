import random

actors = []
with open("cleaned_movielist.txt", 'r') as movie_list:
    for line, cast in enumerate(movie_list.readlines()):
        actor_list=cast.split()
        for i in range(1,len(actor_list)):
            actors.append(actor_list[i])

with open("random.txt",'w') as output:
    for i in range(0,10):
        rand1=random.randint(0,len(actors)-1)
        rand2=random.randint(0,len(actors)-1)
        output.write(actors[rand1]+" "+ actors[rand2]+"\n")

