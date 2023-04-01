# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import os;
import json;
file=open("geometrico.data","w");
with open("foto.json") as archivo:
    datos = json.load(archivo);
file.write(str(datos["_draw_"][2]["points"][2][0])+" "+str(datos["_draw_"][2]["points"][2][1])+"\n")
n = datos["_subgraph_cnt"]
file.write(str(n)+"\n")
aristas = 0
for i in range(n):
    aristas+=len(datos["objects"][i]["nodes"])
    cosa = ""
    for a in range(4):
        cosa+=str(datos["objects"][n+i]["_draw_"][1]['rect'][a]);
        cosa+=" "
    file.write(cosa+"\n")

file.write(str(aristas)+"\n")
for i in range(aristas):
    file.write(str(len(datos["edges"][i]["_draw_"][1])))
    for a in range (len(datos["edges"][i]["_draw_"][1]["points"])):
        file.write(str(datos["edges"][i]["_draw_"][1]["points"][a][0])+" "+str(datos["edges"][i]["_draw_"][1]["points"][a][1]))
    file.write("\n")

file.close()