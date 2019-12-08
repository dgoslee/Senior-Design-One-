from subprocess import call
file = open('Node1.txt', 'r')
text = file.read().strip()
file.close
speech= text
call(["espeak",speech])
