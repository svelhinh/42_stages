i = 5
from subprocess import call;a='i = %d%cfrom subprocess import call;a=%r;i=(i,i-1)[__file__!="Sully.py"];j=str(i);print(a%%(i,10,a),file=open("Sully_"+j+".py","w"),end="");call(["python3", "Sully_"+j+".py"])if i else 0';i=(i,i-1)[__file__!="Sully.py"];j=str(i);print(a%(i,10,a),file=open("Sully_"+j+".py","w"),end="");call(["python3", "Sully_"+j+".py"])if i else 0