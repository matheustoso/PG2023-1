import cv2 as cv
import numpy as np

dog = cv.imread('dog.jpg')
#Path absoluto necessário para macOS
# dog = cv.imread('/Users/matheustoso/Unisinos/2023:1/Processamento_Gráfico/Repo/PG2023-1/entregas/lists/list 4/dog.jpg')

corModificadora = [255, 0, 100]

for i in range(dog.shape[0]): #percorre linhas
	for j in range(dog.shape[1]): #percorre colunas
		B = dog.item(i,j,0) | corModificadora[0]
		G = dog.item(i,j,1) | corModificadora[1]
		R = dog.item(i,j,2) | corModificadora[2]
		dog.itemset((i,j,0),B) # canal B
		dog.itemset((i,j,1),G) # canal G
		dog.itemset((i,j,2),R) # canal R
		
# Média aritmética        
cv.imshow('dog',dog)

cv.waitKey(0)
cv.destroyAllWindows()