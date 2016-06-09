from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import math

def histograma(imagen):
	ajuste = 0
	minimo_valor = np.min(imagen)
	if minimo_valor < 0:
		ajuste = minimo_valor
		rango = np.max(imagen).astype(np.int64) - minimo_valor
		ajuste_dtype = np.promote_types(np.min_scalar_type(rango),np.min_scalar_type(minimo_valor))
		if imagen.dtype != ajuste_dtype:
			imagen = imagen.astype(ajuste_dtype)
		imagen = imagen - ajuste
	hist = np.bincount(imagen.ravel())
	valores_centrales = np.arange(len(hist)) + ajuste
	idx = np.nonzero(hist)[0][0]
	return hist[idx:], valores_centrales[idx:]

def otsu(imagen):
	if(imagen.dtype!='int'):
		imagen=(imagen*255).astype(int)
	try:
		hist, valorcentral = histograma(imagen.ravel())
		hist = hist.astype(float)
		valor1 = np.cumsum(hist)
		valor2 = np.cumsum(hist[::-1])[::-1]
		media1 = np.cumsum(hist * valorcentral) / valor1
		media2 = (np.cumsum((hist * valorcentral)[::-1]) / valor2[::-1])[::-1]
		varianza = valor1[:-1] * valor2[1:] * (media1[:-1] - media2[1:]) ** 2
		idx = np.argmax(varianza)
		return valorcentral[:-1][idx]
	except Exception, e:
		print e
		return 50	

def binariza(imagen,umbral):
	bz = (imagen<=umbral)*1
	return bz

def escala_grises(image):
    pic = image.load()
    arr=np.zeros((image.size[1],image.size[0]));
    for i in range(image.size[0]):
        for j in range(image.size[1]):
            (R, G, B) = pic[i,j]
            intensity = int((R+G+B)/3)
            R = G = B = intensity
            arr[j][i] = intensity
    return arr

def perimetro(imagen):
	perimetro=0.0
	for i in range(1,imagen.shape[1]-1):
		for j in range(1,imagen.shape[0]-1):
			if(imagen[j][i]==1):
				if(((imagen[j-1][i]==0)or(imagen[j][i-1]==0)) or (imagen[j-1][i-1]==0)):
					if(((imagen[j+1][i]==0)or(imagen[j][i+1]==0))or (imagen[j+1][i+1]==0)):
						perimetro=perimetro+1.0;
	return perimetro

def clasifica(de):
	datos=np.array([0.08746169794270002,0.597911274614,0.2915913482526667])-de
	clase=np.argmin(datos)
	if(clase==0):
		print "Esto es un arbol"
	if(clase==1):
		print "Esto es un perro"
	if(clase==2):
		print "Esto es un telefono"

plt.figure()

I =  Image.open("tp.jpg")
plt.subplot(2,2,1)
plt.imshow(I)  

a=escala_grises(I)
#Image.fromarray(a.astype(np.uint8)).show

plt.subplot(2,2,2)
plt.imshow(Image.fromarray(a))  

plt.subplot(2,2,3)
h=histograma(a.astype(int))
plt.plot(h[1], h[0],'b')

plt.subplot(2,2,4)
ot=otsu(a.astype(int))
bi=binariza(a.astype(int),ot)
bi.astype(int)
print "valor otsu:",ot
plt.imshow(Image.fromarray(bi*255))  

area=np.bincount(bi.ravel())[-1]
area=area.astype(float)
print "area: ", area
per=perimetro(bi)
print "perimetro: ", per
compasidad= (4*math.pi)*(area/(per*per))
print "compasidad:", compasidad
clasifica(compasidad)
plt.show()	

